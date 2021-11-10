#include<iostream>
#include<math.h>

//GLEW
#define GLEW_STATIC
#define PI acos(-1)
#include<GL/glew.h>

//GLFW
#include<GLFW/glfw3.h>

#include "Shader.h"
#include "Moon.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

const GLint WIDTH = 800, HEIGHT = 600;
void KeyCallback(GLFWwindow* window, int key, int scnacode, int action, int mode);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
bool keys[1024];
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool firstMouse = true;


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
	// glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader = Shader("res/shaders/core3.vs", "res/shaders/core3.fs");
	Shader moonShader = Shader("res/shaders/moon.vs", "res/shaders/moon.fs");

	Moon moonModel = Moon();


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

	glm::vec3 moonPos = glm::vec3(0.0f, 0.0f, 1.5f);

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		DoMovement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)screenWidth / (float)screenHeight,
			0.1f, 100.0f);

		moonPos = glm::rotate(moonPos, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 transform = glm::mat4(1.0f);  
		transform = glm::translate(transform, moonPos);
		transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0, 1.0, 1.0));
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
		moonShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(moonShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(glGetUniformLocation(moonShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(moonShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		moonModel.Draw(moonShader);

		
		ourShader.Use();
		transform = glm::mat4(1.0f);
		// transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -2.0f));
		transform = glm::rotate(transform, glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()), glm::vec3(sin(23.5*PI/180), cos(23.5*PI/180), 0.0f));
		transform = glm::rotate(transform, glm::radians(-23.5f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		GLuint transLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
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
	
void DoMovement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	/*if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}*/
}
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	
}
void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	
	lastX = xPos;
	lastY = yPos;
	
	camera.ProcessMouseMovement(xOffset, yOffset);
}
	
