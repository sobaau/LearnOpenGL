#ifndef TEXTURE_LOADER_H_
#define TEXTURE_LOADER_H_
#include <iosfwd>
#include <string>
#include <vector>

unsigned int loadTexture(std::string_view path);
unsigned int TextureFromFile(std::string filename, const std::string &directory);
unsigned int loadCubemap(std::vector<std::string> &faces);

#endif // TEXTURE_LOADER_H_