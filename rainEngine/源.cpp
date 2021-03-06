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
#include"LightPoint.h"
#include"LightSpot.h"
#include"Mesh.h"
#include"Model.h"

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

//后面的glVertexAttribPointer要跟这个顺序一直，先传位置，再Normal，最后UV
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

//EBO会用上
GLuint indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};
#pragma endregion

#pragma region Camera Declare
//初始化照相机类
//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));  //照相机位置，照相机目标，照相机UP轴
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

#pragma endregion

#pragma region Light Declare
LightDirectional lightD(glm::vec3(10.0f , 1.0f , - 5.0f),glm::vec3(glm::radians(45.0f) , glm::radians(45.0f), glm::radians(45.0f)),
	glm::vec3(2.0f, 2.0f, 2.0f));
//R,G,B三个照亮中间
LightPoint lightP0(glm::vec3(-3.0f, -2.0f, 0), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 0.0, 0));
LightPoint lightP1(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0, 1.0f, 0));
LightPoint lightP2(glm::vec3(0, 0, 2.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0, 0, 1.0f));
//照亮远处两个方块
LightPoint lightP3(glm::vec3(0.0f, 0.0f, -12.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 0.0f, 1.0f));
//聚光灯照亮底面
LightSpot lightS(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(glm::radians(-90.0f), 0, 0),
	glm::vec3(2.0f, 2.0f, 2.0f));
#pragma endregion

#pragma region Input Declare

float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

#pragma endregion

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);

int main(int argc,char* argv[])
{
	std::string exePath = argv[0];
	//std::cout << exePath.substr(0, exePath.find_last_of('\\')) << std::endl;
	#pragma region Open A Window
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//创建GLFW Window
		GLFWwindow* window = glfwCreateWindow(800, 600, "rainEngine", nullptr, nullptr);

		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();  //停止glfw
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
		//glEnable(GL_CULL_FACE);   //OPENGL会自动把正面、背面都画了，所以要手动开启背面剔除
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
		Mesh cube(vertices);
		Model model(exePath.substr(0, exePath.find_last_of('\\'))+"\\model\\girl.obj");

		//unsigned int VAO;
		//glGenVertexArrays(1, &VAO);
		//glBindVertexArray(VAO);
		//
		//unsigned int VBO;
		//glGenBuffers(1, &VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//
		//unsigned int EBO;
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//先绑定EBO然后用glBufferData把索引复制到缓冲里
		//
		//// 位置属性
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		//glEnableVertexAttribArray(0);
		////光照属性
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);
		//// UV属性
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(2);		

#pragma endregion

	#pragma region Init and Load Textures

		//材质A
		//unsigned int TexBufferA;
		//TexBufferA = LoadImageToGPU("pic.jpg",GL_RGB,GL_RGB,0);

		//材质B
		//unsigned int TexBufferB;
		//TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);
	#pragma endregion

	#pragma region Transform

		//矩阵计算
		//glm::mat4 trans=glm::mat4(1.0f);

		//先缩放、再旋转，最后位移
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));   //该版本glm接收的是弧度，所以需要glm::radians转一下
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

	//主循环
	while (!glfwWindowShouldClose(window))  //在我们每次循环的开始前检查一次GLFW是否被要求退出
	{
		//输入处理
		processInput(window);

		//清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	


		//照相机位置变化后，viewMatrix也要变
		viewMat = camera.GetViewMatrix();

		for (GLuint i = 0; i < 1; i++)
		{
			//设置 model matrix
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			//可以在这里设置MVP（因为正常游戏引擎里模型是变动的）

			//设置materials的shader参数
			testShader->use();

			//设置materials的texture参数
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			//glActiveTexture(GL_TEXTURE0+1);    //或者写GL_TEXTURE1也行
			//glBindTexture(GL_TEXTURE_2D, myMaterial->specular);

			//设置materials的uniform参数
			//glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture1"), 0);
			//glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture2"), 3);   //有0~15号槽位可以用
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(testShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(testShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			
			//平行光
			glUniform3f(glGetUniformLocation(testShader->ID, "lightD.pos"), lightD.position.x, lightD.position.y, lightD.position.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightD.color"), lightD.color.x,lightD.color.y,lightD.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightD.dirToLight"), lightD.direction.x,lightD.direction.y,lightD.direction.z);

			//点光源
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP0.color"), lightP0.color.x,lightP0.color.y,lightP0.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP0.dirToLight"), lightP0.direction.x,lightP0.direction.y,lightP0.direction.z);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			glUniform3f(glGetUniformLocation(testShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP1.quadratic"), lightP1.quadratic);
			
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP2.quadratic"), lightP2.quadratic);
			
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightP3.quadratic"), lightP3.quadratic);

			//聚光灯
			glUniform1f(glGetUniformLocation(testShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightS.color"), lightS.color.x,lightS.color.y,lightS.color.z);
			glUniform3f(glGetUniformLocation(testShader->ID, "lightS.dirToLight"), lightS.direction.x,lightS.direction.y,lightS.direction.z);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(testShader->ID, "lightS.quadratic"), lightS.quadratic);

			//照相机
			glUniform3f(glGetUniformLocation(testShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
	

			//设置模型
			//glBindVertexArray(VAO);

			//Drawcall
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			cube.Draw(myMaterial->shader);
		}
		//glBindVertexArray(0);

		glfwSwapBuffers(window);   //交换颜色缓冲,前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。
		glfwPollEvents();  //检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）
		camera.UpdateCameraPos();
	}
	glfwTerminate();  ////停止glfw
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
		camera.speedZ = 0.005f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -0.005f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedX = -0.005f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedX = 0.005f;
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
	glActiveTexture(GL_TEXTURE0+textureSlot);  //以0为基准加上偏移量就可以切换到对应槽位
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);   //因为这个库读出来的贴图和opengl的y轴方向是相反的
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