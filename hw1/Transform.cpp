// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include <string>

// Please implement the following functions:

void Transform::log(mat3 r){
	for (int i = 0; i < 3; i++) {
		std::cout << "col " << i << "("
		<< r[i].x << " " << r[i].y << " " << r[i].z
		<< ")\n";
	}
	std::cout << "\n\n\n";
};

int Transform::epsilon(int i, int j, int k){
	// https://en.wikipedia.org/wiki/Levi-Civita_symbol
	if(i == j || j == k || i == k){
		return 0;
	}
	// all different
	else if(i == 0 && j == 1 && k == 2){
		return 1;
	}
	else if(i == 0 && j == 2 && k == 1){
		return -1;
	}
	else if(i == 1 && j == 0 && k == 2){
		return -1;
	}
	else if(i == 1 && j == 2 && k == 0){
		return 1;
	}
	else if(i == 2 && j == 0 && k == 1){
		return 1;
	}
	else {
		return -1;
	}
}

mat3 Transform::rodriguez0(float degrees, const vec3& axis){
	mat3 m = mat3();
	const float _cos = cos(degrees*pi/180);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			m[i][j] = axis[i]*axis[j];
		}
	}
	return (1 - _cos)*m;
}

mat3 Transform::rodriguez1(float degrees, const vec3& axis){
	const float _cos = cos(degrees*pi/180);
	return _cos*mat3(); // identity matrix
}

mat3 Transform::rodriguez2(float degrees, const vec3& axis){
	const float _sin = sin(degrees*pi/180);
	mat3 m = mat3();
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			m[i][j] = 0;
			for(int k = 0; k < 3; k++){
				m[i][j] += Transform::epsilon(i, j, k)*axis[k];
			}
		}
	}
	return _sin*m;
}

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// a_ij = (1 - cos)a_i a_j + cos delta_i_j + sin epsilon(j,i,k)a_k
	return Transform::rodriguez0(degrees, axis) + Transform::rodriguez1(degrees, axis) + Transform::rodriguez2(degrees, axis);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
  return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
