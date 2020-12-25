#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec3 aNormal;    //这个传进来的location一定是连着的0123，不能跳数字
layout (location = 2) in vec2 aTexCoord;


//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec4 vertexColor;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
   //gl_Position = transform * vec4(aPos, 1.0f);
   gl_Position =projMat * viewMat * modelMat * vec4(aPos, 1.0f);
   FragPos=(modelMat*vec4(aPos.xyz,1.0)).xyz;
   Normal=mat3(transpose(inverse(modelMat)))*aNormal;  //modelmat的逆转置矩阵，如果直接是modelmat在不均比例拉伸时可能出现问题
   //vertexColor = vec4(aColor, 1.0);
   TexCoord=aTexCoord;
};