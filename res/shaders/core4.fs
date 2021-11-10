#version 330 core
out vec4 color;
in vec3 vertexColor;
in vec2 ourTextCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float time;
uniform vec4 ourColor;
uniform sampler2D texture0;
uniform vec3 LightPos;
uniform vec3 ViewPos;

struct Material{
	float diffuse;
	float specular;
};

uniform Material material;

void main()
{
	// 第四次作业
	vec3 lightDirection = normalize(LightPos-FragPos);
	vec3 viewDirection = normalize(ViewPos-FragPos);
	vec3 norm = normalize(Normal);
	//ambient
	vec3 ambient = 0.2f * vertexColor;
	//diffuse
	 float diff = material.diffuse * max(dot(norm,lightDirection),0.0f);
	 vec3 diffuse = diff * vertexColor;
	//specular
	 vec3 halfAngle = normalize(viewDirection + lightDirection);
	 float spec = material.specular * pow(max(dot(norm,halfAngle),0.0f),64.0f);
	 vec3 specular = spec * vertexColor;
	 color = vec4(ambient + diffuse + specular, 1.0f);

};