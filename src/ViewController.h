#pragma once
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


class ViewController {
private:
	GLFWwindow* wind;
	const float maxViewAngle;
	glm::vec3 position;
	float horizontalAngle;
	float verticalAngle;
	float initialFoV;
	float speed;
	float mouseSpeed;
	double xpos, ypos;

	int windowHeight, windowLength;


public:
	ViewController(GLFWwindow* window);
	glm::mat4 computeMatricesFromInputs();
	float getMouseSpeed();
	void setMouseSpeed(float newMouseSpeed);
	float getFoV();
	void setFoV(float newFoV);

};