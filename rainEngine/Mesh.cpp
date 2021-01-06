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
	memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));  //��ǰ����36�����㿽������
	setupMesh();
}

void Mesh::Draw(Shader * shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0);  //�ڰ�����֮ǰ�ȼ�������Ԫ
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
	//�������һ�������ʱ��Ҫ�Ȱ�VAO����ϣ�����Ƶ�����֮��,������ٽ���´�ʹ��
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);  //���һ��������ƫ����
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);  //���һ��������ƫ����
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
	//�Ȱ�VAO ֮��󶨺����ö�Ӧ��VBO��EBO������ָ�룬�����VAO��֮��ʹ��
	glGenVertexArrays(1, &VAO);  //�����������
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);      //���㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(),&vertices[0], GL_STATIC_DRAW);  //���һ������:ϣ���Կ���ι������������

	//glGenBuffers(1, &EBO);     //�����������
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);//�Ȱ�EBOȻ����glBufferData���������Ƶ�������

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);  //����OpenGL����ν�����������
	glEnableVertexAttribArray(0);
	//��������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// UV����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);  // ���VAO��֮��ʹ��
}
