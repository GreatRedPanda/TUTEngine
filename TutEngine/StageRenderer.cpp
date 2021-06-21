#include "StageRenderer.h"
#include <iostream>

StageRenderer::StageRenderer()
{
}

StageRenderer::StageRenderer(int width, int height)
{
    _width = width;
    _height = height;
    framebuffer = &fb;
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
     bufferTexture =   Texture(_width, _height, GL_RGB, GL_CLAMP, GL_LINEAR, GL_UNSIGNED_BYTE);
    // glDrawBuffer(GL_NONE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferTexture.getTextureBinding(), 0);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    
    

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);



    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //// texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);



}

void StageRenderer::Render(const Camera& camera, GLsizei viewportWidth, GLsizei viewportheight)
{
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
    glClearColor(0.3, 1.0, 0.6, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, viewportWidth, viewportheight);
  //  
   vec3 position = vec3(0, 0, 0);
   vec3 front = vec3(0, 0, 1);
   // mat4 model = glm::mat4(1.0f);
   // model = glm::translate(model, position);
    Camera camTemp = camera;
     mat4 camPr = camTemp.getProjection();
     mat4 view = camTemp.getView();
//    glm::mat4 view = glm::lookAt(position, position + front, vec3(0,1,0));
     glBindVertexArray(VAO);
     for (unsigned int i = 0; i < 10; i++)
     {
         // calculate the model matrix for each object and pass it to shader before drawing
         glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
         model = glm::translate(model, cubePositions[i]);
     //    float angle = 20.0f * i;
       //  model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
         glUseProgram(shaderProgram);
         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1,GL_FALSE, glm::value_ptr(model));
         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(camPr));
        // ourShader.setMat4("model", model);

         glDrawArrays(GL_TRIANGLES, 0, 36);
     }
     GLint numPoint = 4;
     GLfloat points[4][3] = { {-4.0f, 0.0f,0.0f},
         {-6.0f, 4.0f,0.0f},
         {6.0f, -4.0f,0.0f},
         {4.0f, 0.0f,0.0f} };

   
     glMap1f(GL_MAP1_VERTEX_3, 0.0f, 100.0f, 3, numPoint, &points[0][0]);
     glEnable(GL_MAP1_VERTEX_3);
     glBegin(GL_LINE_STRIP);
     for (size_t i = 0; i < 100; i++)
     {
         
         glEvalCoord1f((GLfloat)i);

     }
     glEnd();
     glPointSize(15.0f);
     glBegin(GL_POINTS);
     for (size_t i = 0; i < numPoint; i++)
     {
         glVertex3fv(points[i]);
     }
     glEnd();
    // glBegin(GL_TRIANGLES);
    //vec4 pos1 = camPr * view* model * vec4(0, 0, -20, 1.0); // в рамках камеры
    //vec4 pos2 = camPr * view * model * vec4(0, 10, 20, 1.0); // в рамках камеры
    //vec4 pos3 = camPr * view * model * vec4(5, 10, 20, 1.0); // в рамках камеры
    //glVertex3f(pos1.x, pos1.y, pos1.z);
    //glVertex3f(pos2.x, pos2.y, pos2.z);
    //glVertex3f(pos3.x, pos3.y, pos3.z);
    //glEnd();
}
