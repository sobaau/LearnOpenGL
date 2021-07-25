#ifndef TEXTURE_LOADER_H_
#define TEXTURE_LOADER_H_

#include <iosfwd>
#include<vector>
unsigned int loadTexture(char const *path);
unsigned int TextureFromFile(const char *path, const std::string &directory);
unsigned int loadCubemap(std::vector<std::string> &faces);

#endif // TEXTURE_LOADER_H_