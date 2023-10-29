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
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();

  iniEscena();
  iniCamera();
}

void MyGLWidget::paintGL () 
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  iniLlum();
  // Activem el VAO per a pintar el terra 
  glBindVertexArray (VAO_Terra);

  modelTransformTerra ();
  normalTransform();
  // pintem el terra
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Patr);

  modelTransformPatricio ();
  normalTransform();
  // Pintem el Patricio
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders() {
	BL3GLWidget::carregaShaders();
	NormalMatrixLoc = glGetUniformLocation (program->programId(), "NormalMatrix");
	posFocusLoc = glGetUniformLocation (program->programId(), "posFocusSCO");
	colorFocusLoc = glGetUniformLocation (program->programId(), "colorFocus");
}

void MyGLWidget::iniLlum() {
	if (fescena) {
		posFocus = glm::vec3(View * glm::vec4(1., 1., 1., 1.));
	}
	else {
		posFocus = glm::vec3(0., 0., 0.);
	}
	glUniform3fv (colorFocusLoc, 1, &colorFocus[0]);
	glUniform3fv (posFocusLoc, 1, &posFocus[0]);
}

void MyGLWidget::normalTransform(){
	glm::mat3 NormalMatrix = glm::inverseTranspose(glm::mat3(View * TG));
	glUniformMatrix3fv (NormalMatrixLoc, 1, GL_FALSE, &NormalMatrix[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  	case Qt::Key_K: 
      posFocus.x -= 0.1;
      break;
	case Qt::Key_L: 
      posFocus.x += 0.1;
      break;
	case Qt::Key_F: 
      fescena = not fescena;
      break;
    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}

