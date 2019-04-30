#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct PointLight {
	glm::vec3 pos, ambient, diffuse, specular;
	float constant, linear, quadratic, theta;

	//void updatePos(glm::vec3 position) {
	//	pos = position;
	//}

	//void setColors(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) {
	//	ambient = amb;
	//	diffuse = diff;
	//	specular = spec;
	//}

	//void setFunc(float c, float l, float q) { //the coefficients for the attenuation distance calculation
	//	constant = c;
	//	linear = l;
	//	quadratic = q;
	//}
};

struct DirLight {
	glm::vec3 direction, ambient, diffuse, specular;
};