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
	float diffIntensity=max(dot(light.dirToLight,uNormal),0);    //ƽ�й�û�з��򣬲���Ҫ���
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular pow(max(dit(R,Cam),0),shininess)
	vec3 R =normalize(reflect(-light.dirToLight,uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess);  //�߹�����������λ�øı䣬�����Ƿ��������������ĵ��
	vec3 specColor=specIntensity*light.color*texture(material.specular,TexCoord).rgb;
	
	vec3 result=diffColor;
	return result;
}
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera)
{
	//attenuation
	float dist = length(light.pos - FragPos);   //���Դ��˥��
	float attenuation = 1.0f / (light.constant + light.linear*dist +light.quadratic*(dist*dist));

	//diffuse
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation;   //ƬԪ����Դ�ľ������Ϸ���
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R =normalize(reflect(-normalize(light.pos-FragPos),uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*attenuation;  //�߹�����������λ�øı䣬�����Ƿ��������������ĵ��
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
	float diffIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0)*attenuation*spotRatio;   //ƬԪ����Դ�ľ������Ϸ���
	vec3 diffColor=diffIntensity*light.color*texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 R =normalize(reflect(-normalize(light.pos-FragPos),uNormal));
	float specIntensity=pow(max(dot(R,dirToCamera),0),material.shininess)*attenuation*spotRatio;  //�߹�����������λ�øı䣬�����Ƿ��������������ĵ��
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

	///float dist = length(lightPos - FragPos);   //���Դ��˥��
	//float attenuation = 1.0f / (lightP.constant + lightP.linear*dist +lightP.quadratic*(dist*dist));
   //
	//vec3 lightDir=normalize(lightPos-FragPos);
	//vec3 reflectVec=reflect(-lightDir,Normal);
	//vec3 cameraVec=normalize(cameraPos-FragPos);
   //
	////���淴����ͼֻ��Ҫdiffuse��ͼ��һ��ͨ�����ɣ������Ǻڰ�ɫ
	////specular  ��������ͼ�׵ĵط���1��1��1�����Է��������䣬�ڵĵط���0��0��0����������0�����������淴��
	//float specularAmount=pow(max(dot(reflectVec,cameraVec),0),material.shininess);  //��Ϊ�߹�ֵ��һ��0~1֮���ֵ������32�η����˥��
	//vec3 specular=texture( material.specular , TexCoord ).rgb* specularAmount*lightColor;
   //
	////diffuse
	//vec3 diffuse=texture( material.diffuse , TexCoord ).rgb * max(dot(lightDir,Normal),0) *lightColor;   //Ҫ��֤diffuse������ֵ
	////vec3 diffuse=texture(material.diffuse,TexCoord).rgb;
   //
	////ambient
	//vec3 ambient=texture( material.diffuse , TexCoord ).rgb * ambientColor;
   ///FragColor = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);//���������ֵ��0.0�����᷵�ص�һ�����룻�����1.0���᷵�صڶ�������ֵ��0.2�᷵��80%�ĵ�һ��������ɫ��20%�ĵڶ���������ɫ����������������Ļ��ɫ��
   ///FragColor=vec4(objColor*ambientColor,1.0)*mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),0.2);
   //
   //float cosTheta=dot(normalize(FragPos-lightPos),-1*lightDirUniform);
	//float spotRatio;
   //
   //f(cosTheta>lightS.cosPhyInner)
   //  
	//	//inside
	//	spotRatio=1.0;
   //
   //lse if(cosTheta>lightS.cosPhyOutter){
	//	//middle
	//	spotRatio=1.0-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner);
   //
   //lse
   //
	//	//outside
	//		spotRatio=0.0;
   //
   //	FragColor=vec4(objColor*(ambient+(diffuse+specular)*spotRatio),1.0);
}