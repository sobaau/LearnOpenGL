#include <vector>

class CubeSquared
{

public:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textures;
    CubeSquared();
    unsigned long verticesSize;
    unsigned long normalsSize;
    unsigned long texSize;
};
