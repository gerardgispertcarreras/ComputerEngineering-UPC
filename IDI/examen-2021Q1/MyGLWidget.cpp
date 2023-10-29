// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL ()
{
  ExamGLWidget::initializeGL ();
	iniPintat();
}

void MyGLWidget::iniPintat () {
	cubSeleccionat = 0;
	selecPaint = cubs;
	for (int i = 0; i < 3; ++i){
		posCub[i] = i;
	}
}
void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  if (selecPaint == patricio) {
		glBindVertexArray (VAO_Patr);
		modelTransformPatricio ();
		glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  // Pintem el cub
  else if (selecPaint == cubs) {
		glBindVertexArray(VAO_Cub);
		for (int i = 0; i < 3; ++i) {
		modelTransformCub (2.0+0.5*i, posCub[i]*2.0*M_PI/3.0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		}
  }
  
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angle, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, posCub[cubSeleccionat]*2.0f*float(M_PI)/3.0f, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = glm::rotate(TG, float(-M_PI)/2.0f, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::scale(TG, glm::vec3 (escala, escala, escala));
  TG = glm::translate(TG, -centreBasePat);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
		View = glm::lookAt(glm::vec3(0.,10.,0.), glm::vec3(0.,0.,0.), glm::vec3(1.,0.,0.));

    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 Proj;  // Matriu de projecció
		if (ra >= 1)
  		Proj = glm::ortho(-20.*ra, 20.*ra, -20., 20., 6., 11.);
		else
			Proj = glm::ortho(-20., 20., -20./ra, 20./ra, 6., 11.);
  	glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      if (selecPaint == patricio)
				selecPaint = cubs;
			else
				selecPaint = patricio;
    break;
	}
  case Qt::Key_1: {
      cubSeleccionat = 0;
			emit cub1();
    break;
	}
  case Qt::Key_2: {
      cubSeleccionat = 1;
			emit cub2();
    break;
	}
  case Qt::Key_3: {
      cubSeleccionat = 2;
			emit cub3();
    break;
	}
  case Qt::Key_F: {
      if (colFoc == glm::vec3(1,1,1))
				colFoc = glm::vec3(1,1,0);
			else
				colFoc = glm::vec3(1,1,1);
			enviaColFocus();
    break;
	}
  case Qt::Key_C: {
      camPlanta = not camPlanta;
			viewTransform();
			projectTransform();
			if (camPlanta)
				emit camera2();
			else
				emit camera1();
    break;
	}
  case Qt::Key_Right: {
      for (int i = 0; i < 3; ++i) {
				if (posCub[i] == 2)
					posCub[i] = 0;
				else
					++posCub[i];
			}
    break;
	}
  case Qt::Key_Left: {
      for (int i = 0; i < 3; ++i) {
				if (posCub[i] == 0)
					posCub[i] = 2;
				else
					--posCub[i];
			}
    break;
	}
  case Qt::Key_R: {
			iniCamera();
      iniPintat();
			colFoc = glm::vec3(1,1,1);
  		enviaColFocus();
			emit cub1();
			emit camera1();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::canviaCub1() {
	makeCurrent();
	cubSeleccionat = 0;
	update();
}

void MyGLWidget::canviaCub2() {
	makeCurrent();
	cubSeleccionat = 1;
	update();
}

void MyGLWidget::canviaCub3() {
	makeCurrent();
	cubSeleccionat = 2;
	update();
}

void MyGLWidget::canviaCamera1() {
	makeCurrent();
	camPlanta = false;
	viewTransform();
	projectTransform();
	update();
}

void MyGLWidget::canviaCamera2() {
	makeCurrent();
	camPlanta = true;
	viewTransform();
	projectTransform();
	update();
}
