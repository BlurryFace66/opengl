#include "Model.h"

Model::Model(std::string path)
{
	LoadModel(path);
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_CalcTangentSpace); //ȫת�������Σ�UV��ת
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	//����0��/֮��������ַ�
	directory = path.substr(0, path.find_last_of('\\'));
	std::cout << directory << std::endl;
}