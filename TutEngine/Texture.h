#pragma once
#include <glm.hpp>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Texture
{
	
	unsigned int id;
	
public:
	Texture();
	Texture(int width, int height, GLenum format, GLenum wrapMode, GLenum filterMode,GLenum type   );
	
	unsigned int getTextureBinding() { return this->id; }
	//unsigned int* GetID();
	//GLuint* _id;
};

