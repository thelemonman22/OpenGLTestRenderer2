#include "ViewController.h"
#include "GLFW/glfw3.h"
#include <iostream>

ViewController::ViewController(GLFWwindow* window)
{
	wind = window;
	position = glm::vec3(0, 0, 5);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFoV = 45.0f;
	speed = 3.0f; // 3 units / second
	mouseSpeed = 0.003f;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwGetWindowSize(wind, &windowLength, &windowHeight);
	glfwSetInputMode(wind, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::mat4 ViewController::computeMatricesFromInputs() {

	/*
		TODO: Set so that the camera can go upside down
	*/

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(wind, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(wind, windowLength / 2, windowHeight / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(windowLength / 2 - xpos);
	verticalAngle += mouseSpeed * float(windowHeight / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(wind, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(wind, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(wind, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(wind, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	// Strage up
	if (glfwGetKey(wind, GLFW_KEY_E) == GLFW_PRESS) {
		position += up * deltaTime * speed;
	}
	//Strafe down
	if (glfwGetKey(wind, GLFW_KEY_Q) == GLFW_PRESS) {
		position -= up * deltaTime * speed;
	}
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
	return MVP;
}