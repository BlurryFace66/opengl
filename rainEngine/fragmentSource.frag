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

out vec4 FragColor;
void main()
{
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 diffuse=dot(lightDir,Normal)*lightColor;
   //FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);//如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
   //FragColor=vec4(objColor*ambientColor,1.0)*mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
   FragColor=vec4(objColor*(diffuse+ambientColor),1.0);
}