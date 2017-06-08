// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include <string>

// Please implement the following functions:

inline void copyVec3(const vec3& src, vec3& dest){
	dest.x = src.x;
	dest.y = src.y;
	dest.z = src.z;
}

void Transform::log(mat3 r){
	for (int i = 0; i < 3; i++) {
		Transform::log(r[i]);
	}
	std::cout << "\n";
};

void Transform::log(mat4 r){
	for (int i = 0; i < 4; i++) {
		Transform::log(r[i]);
	}
	std::cout << "\n";
};

void Transform::log(vec3 v){
	std::cout << "("
	<< v.x << " " << v.y << " " << v.z
	<< ")\n";
};

void Transform::log(vec4 v){
	std::cout << "("
	<< v.x << " " << v.y << " " << v.z << " " << v.w
	<< ")\n";
};

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	const float _cos = cos(degrees*pi/180);
	const float _sin = sin(degrees*pi/180);
	const float _oneMinusCos = 1 - _cos;
	const mat3 id = mat3();
	// build column by column, mat3(col0, col1, col2)  where col_i is the image of the basis vector e_i
	return	_oneMinusCos*mat3(axis[0]*axis, axis[1]*axis, axis[2]*axis)
	+		_cos*mat3()
	+		_sin*mat3(glm::cross(axis, id[0]), glm::cross(axis, id[1]), glm::cross(axis, id[2]));
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// up doesn't change
	// eye is rotated using the rodriguez formula, the axis is 'up'
	vec3 newEye = Transform::rotate(degrees, up) * eye;
	std::cout << "eye was\n";
	Transform::log(eye);
	std::cout << "newEye is\n";
	Transform::log(newEye);
	copyVec3(newEye, eye);
	std::cout << "eye is\n";
	Transform::log(eye);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// axis is eye cross up and both are changed
	mat3 rot = Transform::rotate(degrees, glm::cross(eye, up));
	vec3 newEye = rot * eye;
	vec3 newUp = rot * up;
	copyVec3(newEye, eye);
	// up also changes in this one
	copyVec3(newUp, up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // centre is at the origin
  mat3 id = mat3();
  vec3 a = eye;
  vec3 b = up;
  vec3 w = glm::normalize(a);
  vec3 u = glm::normalize(glm::cross(b, w));
  vec3 v = glm::cross(w, u);
// apply a rotation such that 'x' goes to
  mat3 rot = glm::transpose(mat3(u, v, w));
  mat4 rotHomog = mat4(vec4(rot[0], 0), vec4(rot[1], 0), vec4(rot[2], 0), vec4(0, 0, 0, 1));
  mat4 transHomog = mat4(vec4(id[0], 0), vec4(id[1], 0), vec4(id[2], 0), vec4(-1.0f*eye, 1));
  return rotHomog*transHomog;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
