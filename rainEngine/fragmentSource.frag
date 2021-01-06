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
struct LightDirectional
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};
struct LightPoint
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
};
struct LightSpot
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
    float cosPhyInner;
    float cosPhyOutter;
};
uniform Material material;
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;

//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 cameraPos;

out vec4 FragColor;

vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera)
{
	//diffuse max(dot(L,N),0)
	float diffIntensity=max(dot(light.dirToLight,uNormal),0);    //平行光没有方向，不需要点乘
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular pow(max(dit(R,Cam),0),shininess)
	vec3 R =normalize(reflect(-light.dirToLight,uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess);  //高光会随着照相机位置改变，所以是反射光和照相机方向的点乘
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;
	
	vec3 result=diffColor;
	return result;
}
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera)
{
	//attenuation
	float dist = length(light.pos - FragPos);   //点光源会衰减
	float attenuation = 1.0f / (light.constant + light.linear*dist +light.quadratic*(dist*dist));

	//diffuse
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation;   //片元到光源的距离点乘上法线
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R =normalize(reflect(-normalize(light.pos-FragPos),uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*attenuation;  //高光会随着照相机位置改变，所以是反射光和照相机方向的点乘
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;

	vec3 result=diffColor+specColor;
	return result;
}
vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera)
{
	//attenuation
	float dist = length(light.pos - FragPos);   
	float attenuation = 1.0f / (light.constant + light.linear*dist +light.quadratic*(dist*dist));
	float cosTheta=dot(normalize(FragPos-light.pos),-1*light.dirToLight);
	float spotRatio;
   
    if(cosTheta>lightS.cosPhyInner)
	{
		//inside
		spotRatio=1.0;
	}	
	else if(cosTheta>lightS.cosPhyOutter){
		//middle
		spotRatio=1.0-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner);	
	}
	else
	{	
		//outside
		spotRatio=0.0;
	}

	//diffuse
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation*spotRatio;   //片元到光源的距离点乘上法线
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R =normalize(reflect(-normalize(light.pos-FragPos),uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*attenuation*spotRatio;  //高光会随着照相机位置改变，所以是反射光和照相机方向的点乘
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;

	vec3 result=diffColor+specColor;
	return result;
}
void main()
{

	vec3 finalResult=vec3(0,0,0);
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera=normalize(cameraPos-FragPos);

	finalResult+=CalcLightDirectional(lightD,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP0,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP1,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP2,uNormal,dirToCamera);
	finalResult+=CalcLightPoint(lightP3,uNormal,dirToCamera);
	finalResult+=CalcLightSpot(lightS,uNormal,dirToCamera);

	FragColor=vec4(finalResult,1.0);
	FragColor=vec4(1.0,1.0,1.0,1.0);
}