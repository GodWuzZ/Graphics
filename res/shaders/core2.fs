#version 330 core
out vec4 color;
in vec3 vertexColor;
in vec2 ourTextCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float value;
uniform vec4 ourColor;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	// 第二次作业
	color = mix(texture(texture0,ourTextCoord),texture(texture1,ourTextCoord),value);
};