#include "Objecte.h"
#include <iostream>
#include <stdio.h>

//Constructora
Camera::Objecte()
{
	TG = glm::mat4 TG (1.0)
}

/*//Constructora
Camera::Camera(glm::vec3 OBS, glm::vec3 VRP, glm::vec3 UP, GLfloat ra, GLfloat zN, GLfloat zF, GLfloat FOV)
{
	
}*/

//Destructora
Objecte::~Objecte()
{}

void Objecte::modelTransform () 
{
  // Matriu de transformació de model
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}
