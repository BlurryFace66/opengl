#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include<iostream>

using namespace std;

int main2()
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);   //��Ϊ��������������ͼ��opengl��y�᷽�����෴��
	unsigned char *data = stbi_load("pic.jpg",&width,&height,&nrChannels,0);

	for (size_t i = 0; i < 50; i++)
	{
		cout << (int)data[i] << endl;
	}

	stbi_image_free(data);

	while (true)
	{

	}

	return 0;
}