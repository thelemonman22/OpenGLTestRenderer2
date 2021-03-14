#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

glm::mat4 myMatrix;
glm::vec4 myVector;

glm::vec4 transformedVector = myMatrix * myVector;
