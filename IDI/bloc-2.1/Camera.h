#ifndef CAMERA_H
#define CAMERA_H
#include "MyGLWidget.h"

class Camera{
	public:
		glm::vec3 OBS;
		glm::vec3 VRP;
		glm::vec3 UP;
		GLfloat ra;
		GLfloat zN;
		GLfloat zF;
		GLfloat FOV;
		glm::mat4 Proj;
		glm::mat4 View;

		Camera();
		~Camera();
		void ini_camera();
		void projectTransform();
		void viewTransform();
	private:
};
#endif