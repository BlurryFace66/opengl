#include<iostream>

using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"Camera.h"
#include"Material.h"
#include"LightDirectional.h"

#pragma region Model Data

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

//�����glVertexAttribPointerҪ�����˳��һֱ���ȴ�λ�ã���Normal�����UV
float vertices[] = {
	// Positions          // Normals           // Texture Coords
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

//EBO������
GLuint indices[] = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};
#pragma endregion

#pragma region Camera Declare
//��ʼ���������
//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));  //�����λ�ã������Ŀ�꣬�����UP��
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

#pragma endregion

#pragma region Light Declare
LightDirectional light = LightDirectional(glm::vec3(10.0f , 10.0f , - 5.0f),glm::vec3(glm::radians(45.0f) , glm::radians(45.0f), 0),
	glm::vec3(10.0f, 0.0f, 0.0f));

#pragma endregion

#pragma region Input Declare

float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

#pragma endregion

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);

int main()
{
	#pragma region Open A Window
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//����GLFW Window
		GLFWwindow* window = glfwCreateWindow(800, 600, "rainEngine", nullptr, nullptr);

		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();  //ֹͣglfw
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);

		//Init GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			return -1;
		}

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		//glEnable(GL_CULL_FACE);   //OPENGL���Զ������桢���涼���ˣ�����Ҫ�ֶ����������޳�
		//glCullFace(GL_BACK);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_DEPTH_TEST);

	#pragma endregion

	#pragma region Init Shader Program

		Shader* testShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion

	#pragma region Init Material

			Material* myMaterial = new Material(testShader,
				LoadImageToGPU("container2.png",GL_RGBA, GL_RGBA, Shader::DIFFUSE),
				LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
				glm::vec3(0.0f, 0.0f, 1.0f),
				32.0f);

	#pragma endregion

	#pragma region Init and Load Models to VAO,VBO

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//unsigned int EBO;
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//�Ȱ�EBOȻ����glBufferData���������Ƶ�������

		// λ������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		//��������
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		// UV����
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);		

#pragma endregion

	#pragma region Init and Load Textures

		//����A
		//unsigned int TexBufferA;
		//TexBufferA = LoadImageToGPU("pic.jpg",GL_RGB,GL_RGB,0);

		//����B
		//unsigned int TexBufferB;
		//TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);
	#pragma endregion

	#pragma region Transform

		//�������
		//glm::mat4 trans=glm::mat4(1.0f);

		//�����š�����ת�����λ��
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));   //�ð汾glm���յ��ǻ��ȣ�������Ҫglm::radiansתһ��
		//trans = glm::translate(trans, glm::vec3(-1.0f, 0, 0));
	#pragma endregion

	#pragma region Prepare MVP matrices

		glm::mat4 modelMat = glm::mat4(1.0f);
		//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
		glm::mat4 viewMat = glm::mat4(1.0f);
		//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
		//viewMat = camera.GetViewMatrix();
		glm::mat4 projMat = glm::mat4(1.0f);
		projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	#pragma endregion

	//��ѭ��
	while (!glfwWindowShouldClose(window))  //������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		//���봦��
		processInput(window);

		//����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	


		//�����λ�ñ仯��viewMatrixҲҪ��
		viewMat = camera.GetViewMatrix();

		for (GLuint i = 0; i < 10; i++)
		{
			//���� model matrix
			glm::mat4 modelMat2=glm::mat4(1.0f);
			modelMat2 = glm::translate(modelMat2, cubePositions[i]);

			//��������������MVP����Ϊ������Ϸ������ģ���Ǳ䶯�ģ�

			//����materials��shader����
			testShader->use();

			//����materials��texture����
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0+1);    //����дGL_TEXTURE1Ҳ��
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);

			//����materials��uniform����
			//glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture1"), 0);
			//glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture2"), 3);   //��0~15�Ų�λ������
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(testShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(testShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			//glUniform3f(glGetUniformLocation(testShader->ID, "lightPos"), light.direction.x, light.direction.y, light.direction.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightColor"), light.color.x,light.color.y,light.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightDir"), light.direction.x,light.direction.y,light.direction.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
	

			//����ģ��
			glBindVertexArray(VAO);

			//Drawcall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glBindVertexArray(0);

		glfwSwapBuffers(window);   //������ɫ����,ǰ���屣�������������ͼ����������Ļ����ʾ�������еĵ���Ⱦָ����ں󻺳��ϻ��ơ������е���Ⱦָ��ִ����Ϻ����ǽ���(Swap)ǰ����ͺ󻺳壬����ͼ����������Գ�����֮ǰ�ᵽ�Ĳ���ʵ�о������ˡ�
		glfwPollEvents();  //�����û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		camera.UpdateCameraPos();
	}
	glfwTerminate();  ////ֹͣglfw
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.speedZ = 0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -0.01f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 0.01f;
	}
	else
	{
		camera.speedZ = 0.0f;
		camera.speedX = 0.0f;
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;
	//cout << deltaX << endl;
	camera.ProcessMouseMovement(deltaX,deltaY);
}

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat,GLenum format,int textureSlot)
{
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0+textureSlot);  //��0Ϊ��׼����ƫ�����Ϳ����л�����Ӧ��λ
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);   //��Ϊ��������������ͼ��opengl��y�᷽�����෴��
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannel, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image failed";
	}
	stbi_image_free(data);

	return TexBuffer;
}