#version 330 core
out vec4 color;
in vec3 vertexColor;
in vec2 ourTextCoord;
uniform float time;
uniform vec4 ourColor;
uniform sampler2D texture0;
void main()
{
	// color = ourColor;
	// color = vec4(vertexColor,1.0f);
	color = texture(texture0,ourTextCoord);
};