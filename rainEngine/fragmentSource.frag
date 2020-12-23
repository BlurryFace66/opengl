#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;
void main()
{
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 reflectVec=reflect(-lightDir,Normal);
	vec3 cameraVec=normalize(cameraPos-FragPos);

	float specularAmount=pow(max(dot(reflectVec,cameraVec),0),32);  //��Ϊ�߹�ֵ��һ��0~1֮���ֵ������32�η����˥��
	vec3 specular=specularAmount*lightColor;

	vec3 diffuse=max(dot(lightDir,Normal),0)*lightColor;   //Ҫ��֤diffuse������ֵ
   //FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);//���������ֵ��0.0�����᷵�ص�һ�����룻�����1.0���᷵�صڶ�������ֵ��0.2�᷵��80%�ĵ�һ��������ɫ��20%�ĵڶ���������ɫ����������������Ļ��ɫ��
   //FragColor=vec4(objColor*ambientColor,1.0)*mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
   FragColor=vec4(objColor*(diffuse+ambientColor+specular),1.0);
}