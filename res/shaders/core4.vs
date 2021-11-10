#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 ourColor;
layout(location = 2) in vec3 normal;

out vec3 vertexColor;
out vec2 ourTextCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
void main()
{
	// 第四次作业
	vertexColor = ourColor;
	gl_Position = projection * view * transform * vec4(position,1.0f);
	FragPos = vec3(transform*vec4(position,1.0f));
	Normal = mat3(transpose(inverse(transform)))*normal;
}
