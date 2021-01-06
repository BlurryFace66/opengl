#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>   //������Ч
class Model
{
public:
	Model(std::string path);
	std::vector<Mesh> meshes;
	std::string directory;
private:
	void LoadModel(std::string path);
};

