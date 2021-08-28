#include <vector>

class CubeLayout
{
public:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textures;
    CubeLayout();
    unsigned long verticesSize;
    unsigned long normalsSize;
    unsigned long texSize;
};
