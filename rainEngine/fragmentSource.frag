#version 330 core
//in vec4 vertexColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;


struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;  
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

	//镜面反射贴图只需要diffuse贴图的一个通道即可，所以是黑白色
	//specular  镜反射贴图白的地方是1，1，1，所以发生镜反射，黑的地方是0，0，0乘起来还是0，不发生镜面反射
	float specularAmount=pow(max(dot(reflectVec,cameraVec),0),material.shininess);  //因为高光值是一个0~1之间的值，所以32次方后会衰减
	vec3 specular=texture( material.specular , TexCoord ).rgb* specularAmount*lightColor;

	//diffuse
	vec3 diffuse=texture( material.diffuse , TexCoord ).rgb * max(dot(lightDir,Normal),0) *lightColor;   //要保证diffuse都是正值
	//vec3 diffuse=texture(material.diffuse,TexCoord).rgb;

	//ambient
	vec3 ambient=texture( material.diffuse , TexCoord ).rgb * ambientColor;
   //FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);//如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
   //FragColor=vec4(objColor*ambientColor,1.0)*mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
   FragColor=vec4(objColor*(diffuse+ambientColor+specular),1.0);
}