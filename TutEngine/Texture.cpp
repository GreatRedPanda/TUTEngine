#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(int width, int height, GLenum format, GLenum wrapMode, GLenum filterMode, GLenum type)
{
 
    glGenTextures(1, &id); 
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
   

}

//unsigned int* Texture::GetID()
//{
//    return _id;
//}
