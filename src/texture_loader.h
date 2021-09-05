#ifndef TEXTURE_LOADER_H_
#define TEXTURE_LOADER_H_
#include <iosfwd>
#include <string>
#include <vector>

unsigned int load_texture(std::string_view path);
unsigned int texture_from_file(std::string filename, const std::string &directory);
unsigned int load_cubemap(std::vector<std::string> &faces);

#endif // TEXTURE_LOADER_H_
