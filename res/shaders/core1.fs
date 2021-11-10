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
	

	// 第一次作业
	color = ourColor;
};