#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__
#include <iosfwd>
#include<vector>
unsigned int loadTexture(char const *path);
unsigned int TextureFromFile(const char *path, const std::string &directory);
unsigned int loadCubemap(std::vector<std::string> &faces);
#endif // __TEXTURE_LOADER_H__