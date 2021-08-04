#include <vector>

class cubeLayout
{

public:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textures;
    cubeLayout();
    unsigned long verticesSize;
    unsigned long normalsSize;
    unsigned long texSize;
};
