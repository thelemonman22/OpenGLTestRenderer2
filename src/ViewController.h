#pragma once
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


class ViewController {
private:
	GLFWwindow* wind;

	glm::vec3 position;
	float horizontalAngle;
	float verticalAngle;
	float initialFoV;

	float speed;
	float mouseSpeed;
	double xpos, ypos;

public:
	ViewController(GLFWwindow* window);
	glm::mat4 computeMatricesFromInputs();

};