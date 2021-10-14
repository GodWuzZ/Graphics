#include<iostream>

//GLEW
#define GLEW_STATIC
#include<GL/glew.h>

//GLFW
#include<GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

const GLint WIDTH = 800, HEIGHT = 600;
void KeyCallback(GLFWwindow* window, int key, int scnacode, int action, int mode);
bool keys[1024];

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LEZ", nullptr, nullptr);
	// next two lines are for mac retina display
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);


	if (nullptr == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");
	

	GLfloat vertices[] = {
		//position             //color
		-0.5f,-0.5f,-0.5f,     1.0f,0.0f,0.0f,
		0.5f,-0.5f,-0.5f,      1.0f,0.0f,0.0f,
		0.5f,0.5f,-0.5f,       1.0f,0.0f,0.0f,
		0.5f,0.5f,-0.5f,       1.0f,0.0f,0.0f,
		-0.5f,0.5f,-0.5f,      1.0f,0.0f,0.0f,
		-0.5f,-0.5f,-0.5f,     1.0f,0.0f,0.0f,

		-0.5f,-0.5f,0.5f,      0.0f,1.0f,0.0f,
		0.5f,-0.5f,0.5f,       0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,        0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,        0.0f,1.0f,0.0f,
		-0.5f,0.5f,0.5f,       0.0f,1.0f,0.0f,
		-0.5f,-0.5f,0.5f,      0.0f,1.0f,0.0f,

		-0.5f,0.5f,0.5f,       0.0f,0.0f,1.0f,
		-0.5f,0.5f,-0.5f,      0.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,     0.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,     0.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,      0.0f,0.0f,1.0f,
		-0.5f,0.5f,0.5f,       0.0f,0.0f,1.0f,

		0.5f,0.5f,0.5f,        1.0f,1.0f,0.0f,
		0.5f,0.5f,-0.5f,       1.0f,1.0f,0.0f,
		0.5f,-0.5f,-0.5f,      1.0f,1.0f,0.0f,
		0.5f,-0.5f,-0.5f,      1.0f,1.0f,0.0f,
		0.5f,-0.5f,0.5f,       1.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,        1.0f,1.0f,0.0f,

		-0.5f,-0.5f,-0.5f,     1.0f,0.0f,1.0f,
		0.5f,-0.5f,-0.5f,      1.0f,0.0f,1.0f,
		0.5f,-0.5f,0.5f,       1.0f,0.0f,1.0f,
		0.5f,-0.5f,0.5f,       1.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,      1.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,     1.0f,0.0f,1.0f,

		-0.5f,0.5f,-0.5f,      0.0f,1.0f,1.0f,
		0.5f,0.5f,-0.5f,       0.0f,1.0f,1.0f,
		0.5f,0.5f,0.5f,        0.0f,1.0f,1.0f,
		0.5f,0.5f,0.5f,        0.0f,1.0f,1.0f,
		-0.5f,0.5f,0.5f,       0.0f,1.0f,1.0f,
		-0.5f,0.5f,-0.5f,      0.0f,1.0f,1.0f,
	};

	// the data should be transfered to the memory on Graphics Card
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// connect the VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// transfer the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// set the attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		printf("%f\n",time);
		//float colorValue = sin(time) / 2.0f + 0.5f;//设置颜色值范围0--1
		//int vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");//获取uniform的位置索引
		//// glUniform4f(vertexColorLocation, colorValue, 0.0f, 0.0f, 1.0f);//红-黑-红渐变色
		//if((int)time%2==0)// 红-绿交替出现
		//	glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
		//else
		//	glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*glUseProgram(shaderProgram);*/
		ourShader.Use();
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -2.0f));
		transform = glm::rotate(transform, glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		GLuint transLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight,
			0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1f(glGetUniformLocation(ourShader.Program, "time"), time);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	return 0;

	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) {
				keys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				keys[key] = false;
			}
		}
	}