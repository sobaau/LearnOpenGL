#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__
#include <glad/glad.h>
#include <iostream>
unsigned int loadTexture(char const *path);
unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
unsigned int loadCubemap(std::vector<std::string> &faces);
#endif // __TEXTURE_LOADER_H__