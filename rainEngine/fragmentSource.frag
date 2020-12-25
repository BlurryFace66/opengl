#version 330 core
//in vec4 vertexColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;


struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

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

	//specular
	float specularAmount=pow(max(dot(reflectVec,cameraVec),0),material.shininess);  //因为高光值是一个0~1之间的值，所以32次方后会衰减
	vec3 specular=material.specular * specularAmount*lightColor;

	//diffuse
	vec3 diffuse=texture( material.diffuse , TexCoord ).rgb * max(dot(lightDir,Normal),0) *lightColor;   //要保证diffuse都是正值
	//vec3 diffuse=texture(material.diffuse,TexCoord).rgb;

	//ambient
	vec3 ambient=texture( material.diffuse , TexCoord ).rgb * ambientColor;
   //FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);//如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
   //FragColor=vec4(objColor*ambientColor,1.0)*mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
   FragColor=vec4(objColor*(diffuse+ambientColor+specular),1.0);
}