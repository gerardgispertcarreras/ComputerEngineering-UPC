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

void MyGLWidget::updateAnimation()
{
	makeCurrent();
    ++rotationDiscoBall;
	if (focusBool[4]) apagarFocus();
	else encendreFocus();
	glUniform1iv (focusBoolLoc, 5, &focusBool[0]);
	update();
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  carregaShaders();
  
  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersDiscoBall();
  creaBuffersTerraIParets();

  iniEscena();
  iniCamera();
  iniLlum();
  rotationDiscoBall = rotationDancers = 0;

  timer = new QTimer(this);
    
    // Conectar la señal timeout del timer al slot updateAnimation
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    
    // Configurar el intervalo de tiempo para actualizar la animación (por ejemplo, cada 16 ms)
    timer->setInterval(100);
}

void MyGLWidget::carregaShaders()
{
  LL4GLWidget::carregaShaders();
  NormalMatrixLoc = glGetUniformLocation (program->programId(), "NormalMatrix");
  focusColLoc = glGetUniformLocation (program->programId(), "focusCol");
  focusPosLoc = glGetUniformLocation (program->programId(), "focusPos");
  focusBoolLoc = glGetUniformLocation (program->programId(), "focusBool");
}

void MyGLWidget::iniLlum() {
	focusCol[0] = glm::vec3(0.4, 0.4, 0.4);
	focusCol[1] = glm::vec3(0.4, 0., 0.);
	focusCol[2] = glm::vec3(0., 0.4, 0.);
	focusCol[3] = glm::vec3(0., 0., 0.4);
	focusCol[4] = glm::vec3(0.4, 0.4, 0.);
	focusPos[0] = glm::vec3(5.0, 10.0, 5.0);
	glUniform3fv (focusColLoc, 5, &focusCol[0][0]);
	glUniform3fv (focusPosLoc, 5, &focusPos[0][0]);
	glUniform1iv (focusBoolLoc, 5, &focusBool[0]);
}

void MyGLWidget::normalMatrixTransform() {
	NormalMatrix = glm::inverseTranspose(glm::mat3(View * TG));
	glUniformMatrix3fv (NormalMatrixLoc, 1, GL_FALSE, &NormalMatrix[0][0]);
}

void MyGLWidget::paintGL () 
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  normalMatrixTransform();
  glDrawArrays(GL_TRIANGLES, 0, 30);
  
  // MORTY
  glBindVertexArray (VAO_Morty);
  modelTransformMorty ();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);
  
  // FANTASMA
  glBindVertexArray (VAO_Fantasma);
  modelTransformFantasma (1.0f);
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);
  modelTransformFantasma (9.0f);
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);

  // DISCO BALL
  glBindVertexArray (VAO_DiscoBall);
  modelTransformDiscoBall ();
  
  glDrawArrays(GL_TRIANGLES, 0, discoBall.faces().size()*3);
  
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformTerra ()
{
  TG = glm::mat4(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformMorty ()
{
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5.0,0,5));
  TG = glm::rotate(TG, float(M_PI)*rotationDancers/2, glm::vec3(0., 1., 0.));
  TG = glm::scale(TG, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG = glm::translate(TG, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  normalMatrixTransform();
}

void MyGLWidget::modelTransformFantasma (float posX)
{
  TG = glm::translate(glm::mat4(1.0f), glm::vec3(posX,0.5,5));
  TG = glm::rotate(TG, float(M_PI)*rotationDancers/2, glm::vec3(0., 1., 0.));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  normalMatrixTransform();
}

void MyGLWidget::modelTransformDiscoBall ()
{
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,5,5));
  TG = glm::rotate(TG, float(M_PI)*rotationDiscoBall/18, glm::vec3(0., 1., 0.));
  TG = glm::scale(TG, glm::vec3(escalaDiscoBall, escalaDiscoBall, escalaDiscoBall));
  TG = glm::translate(TG, -centreBaseDiscoBall);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
  normalMatrixTransform();
  updateFocus();
}

void MyGLWidget::updateFocus() {
	focusPos[1] = glm::vec3(View * TG * glm::vec4(1.2, 0., 0., 1.));
	focusPos[2] = glm::vec3(View * TG * glm::vec4(-1.2, 0., 0., 1.));
	focusPos[3] = glm::vec3(View * TG * glm::vec4(0., 0., 1.2, 1.));
	focusPos[4] = glm::vec3(View * TG * glm::vec4(0., 0., -1.2, 1.));
	glUniform3fv (focusPosLoc, 5, &focusPos[0][0]);
}

void MyGLWidget::apagarFocus() {
	int i = 1;
	for (bool apagat = false; not apagat; ++i) {
		if (focusBool[i] == 1) {
			focusBool[i] = 0;
			apagat = true;
		}
	}
	glUniform1iv (focusBoolLoc, 5, &focusBool[0]);
}

void MyGLWidget::encendreFocus() {
	int i = 1;
	for (bool ences = false; not ences; ++i) {
		if (focusBool[i] == 0) {
			focusBool[i] = 1;
			ences = true;
		}
	}
	glUniform1iv (focusBoolLoc, 5, &focusBool[0]);
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
  case Qt::Key_A: {
      ++rotationDancers;
    break;
	}
  case Qt::Key_D: {
      --rotationDancers;
    break;
	}
  case Qt::Key_E: {
	  if (focusBool[0] == 1)
      	focusBool[0] = 0;
	  else focusBool[0] = 1;
	  glUniform1iv (focusBoolLoc, 5, &focusBool[0]);
    break;
	}
  case Qt::Key_B: {
      if (focusBool[4]) apagarFocus();
	  else encendreFocus();
    break;
	}	
  case Qt::Key_R: {
      ++rotationDiscoBall;
    break;
	}
  case Qt::Key_S: {
      if (timer->isActive()) {
    // El timer está corriendo
    	timer->stop();
	  } else {
    // El timer está detenido
        timer->start();
	  }
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}
