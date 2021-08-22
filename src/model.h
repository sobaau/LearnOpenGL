#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"            // for Mesh, Texture
#include <assimp/material.h> // for aiMaterial (ptr only), aiTextureType
#include <fstream>           // for string
#include <vector>            // for vector
class Shader;
struct aiMesh;
struct aiNode;
struct aiScene;

class Model
{
public:
    // model data
    std::vector<Texture> texturesLoaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gamma;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    explicit Model(std::string const &path);

    // draws the model, and thus all its meshes
    void draw(Shader &shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void load_model(std::string const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void process_node(aiNode *node, const aiScene *scene);

    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string const &typeName);
};

#endif // MODEL_H_