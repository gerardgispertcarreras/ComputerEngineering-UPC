#ifndef OBJECTE_H
#define OBJECTE_H
#include "MyGLWidget.h"

class Objecte{
	public:
		GLuint VAO;
		GLuint VBO[2];
		Model model;
		glm::mat4 TG;
		GLuint n_faces;
		GLuint n_vertex;
		glm::vec3 vertex;
		glm::vec3 colors;
		Objecte();
		~Objecte();
		void modelTransform();
	private:
};
#endif