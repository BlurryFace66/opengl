#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

Mesh::Mesh(float vertices[])
{
	this->vertices.resize(36);
	memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));  //把前面那36个顶点拷贝进来
	setupMesh();
}

void Mesh::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0);  //在绑定纹理之前先激活纹理单元
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.diffuse", 0);
		}
		else if (textures[i].type == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.specular", 1);

		}
	}
	//打算绘制一个物体的时候，要先把VAO绑定在希望绘制的物体之上,用完后再解绑供下次使用
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);  //最后一个参数是偏移量
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);  //最后一个参数是偏移量
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	//先绑定VAO 之后绑定和配置对应的VBO、EBO和属性指针，最后解绑VAO供之后使用
	glGenVertexArrays(1, &VAO);  //顶点数组对象
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);      //顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(),&vertices[0], GL_STATIC_DRAW);  //最后一个参数:希望显卡如何管理给定的数据

	//glGenBuffers(1, &EBO);     //索引缓冲对象
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);//先绑定EBO然后用glBufferData把索引复制到缓冲里

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);  //告诉OpenGL该如何解析顶点数据
	glEnableVertexAttribArray(0);
	//光照属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// UV属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);  // 解绑VAO供之后使用
}
