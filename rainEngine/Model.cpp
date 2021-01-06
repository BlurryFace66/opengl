#include "Model.h"

Model::Model(std::string path)
{
	LoadModel(path);
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_CalcTangentSpace); //全转成三角形，UV翻转
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	//查找0到/之间的所有字符
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << directory << std::endl;
}