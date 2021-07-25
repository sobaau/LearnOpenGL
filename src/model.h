#ifndef MODEL_H_
#define MODEL_H_


#include <fstream>            // for string
#include <vector>             // for vector
#include <assimp/material.h>  // for aiMaterial (ptr only), aiTextureType
#include "mesh.h"             // for Mesh, Texture
class Shader;
struct aiMesh;
struct aiNode;
struct aiScene;

class Model {
public:
    // model data 
    std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gamma;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    explicit Model(std::string const &path);

    // draws the model, and thus all its meshes
    void Draw(Shader &shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(std::string const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string const &typeName);
};


#endif // MODEL_H_