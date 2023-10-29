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

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::paintGL ()
{
  glm::vec3 filtre;
  if (invisible)
	filtre = glm::vec3(0.,0.7,0.);
  else
    filtre = glm::vec3(1.,1.,1.);
  glUniform3fv(filtreLoc, 1, &filtre[0]);
  viewTransform();
  projectTransform();
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Rick
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

  if (invisible){
	  filtre = glm::vec3(1.,1.,1.);
	  glUniform3fv(filtreLoc, 1, &filtre[0]);
	}

  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  
  // VideoCamera
  glBindVertexArray (VAO_models[VIDEOCAMERA]);
  VideoCameraTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);  
  
  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // Paret
  ParetTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  if (minicam){
	if (invisible)
	  filtre = glm::vec3(0.,0.7,0.);
	else
	  filtre = glm::vec3(0.,1.,0.);
	glUniform3fv(filtreLoc, 1, &filtre[0]);
	glViewport (3*ample/4, 3*alt/4, ample/4, alt/4);
	viewTransform2();
	projectTransform2();

	// Rick
	glBindVertexArray (VAO_models[RICK]);
	RickTransform();
	glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

    if (invisible){
	  filtre = glm::vec3(0.,1.,0.);
	  glUniform3fv(filtreLoc, 1, &filtre[0]);
	}

	// Morty
	glBindVertexArray (VAO_models[MORTY]);
	MortyTransform();
	glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
	
	// VideoCamera
	glBindVertexArray (VAO_models[VIDEOCAMERA]);
	VideoCameraTransform();
	glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);  
	
	// Terra
	glBindVertexArray (VAO_Terra);
	identTransform();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// Paret
	ParetTransform();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray (0);
  }
}

void MyGLWidget::RickTransform ()
{
  glm::mat4 TG(1.0f);  
  TG = glm::translate(TG, glm::vec3(-2, 0, -2));
  TG = glm::rotate(TG, M_PIf, glm::vec3(0.,1.,0.));
  TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
  TG = glm::translate(TG, -centreBaseModels[RICK]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::VideoCameraTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(-4, 3, -4));
  TG = glm::rotate(TG, rotCam, glm::vec3(0.,1.,0.));
  TG = glm::rotate(TG, M_PIf/4.f, glm::vec3(1.,0.,0.));
  TG = glm::scale(TG, glm::vec3(escalaModels[VIDEOCAMERA]));
  TG = glm::translate(TG, -centreBaseModels[VIDEOCAMERA]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posMorty);
  TG = glm::rotate(TG, angleMorty, glm::vec3(0.,1.,0.));
  TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
  TG = glm::translate(TG, -centreBaseModels[MORTY]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::iniEscena()
{
	Pmin = glm::vec3(-4.,0.,-4.);
	Pmax = glm::vec3(4.,3.,4.);
  radiEscena = distance(Pmax,Pmin)/2.;
  centreEscena = (Pmax+Pmin)/2.f;
  dist = 2*radiEscena;
  alfaini = asin(radiEscena/dist);
}

void MyGLWidget::iniCamera(){

  obs = centreEscena + dist*glm::vec3(0.,0.,1.);
  vrp = centreEscena;
  up = glm::vec3(0, 1, 0);
  fov = alfaini*2.f;
  znear =  dist - radiEscena;
  zfar  = dist + radiEscena;
  psi = 0.;
  theta = M_PIf/4.;
  rotCam = M_PIf/4.f;
  viewTransform();
}

void MyGLWidget::viewTransform ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  View = glm::translate(View, -glm::vec3(0.,0.,dist));
  View = glm::rotate(View, theta, glm::vec3(1.,0.,0.));
  View = glm::rotate(View, -psi, glm::vec3(0.,1.,0.));
  View = glm::translate(View, -vrp);
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

glm::vec3 MyGLWidget::calcularVRP()
{
	return glm::vec3(-4.,3.,-4.)+glm::vec3(sin(rotCam)*4.f, -1*4.f, cos(rotCam)*4.f);
}

void MyGLWidget::viewTransform2 ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  View = glm::lookAt (glm::vec3(-4.,3.,-4.), calcularVRP(), glm::vec3(0,1,0));
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform2 ()
{
  glm::mat4 Proj(1.0f);
  Proj = glm::perspective (2.f*M_PIf/6.f, ra, 0.4f, distance(Pmin,Pmax));
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if (DoingInteractive == ROTATE)
  {
	theta += float((e->y()-yClick)*2*M_PI)/alt;
	psi -= float((e->x()-xClick)*2*M_PI)/ample;
	xClick = e->x();
	yClick = e->y();
	viewTransform();
  }
  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { 
      posMorty = posMorty + glm::vec3(0,0.0,0.1)*glm::vec3(cos(angleMorty)) + glm::vec3(0.1,0.0,0.)*glm::vec3(sin(angleMorty));
      break;
    }
    case Qt::Key_Down: {
	  posMorty = posMorty - glm::vec3(0,0.0,0.1)*glm::vec3(cos(angleMorty)) - glm::vec3(0.1,0.0,0.)*glm::vec3(sin(angleMorty));
      break;
    }
	case Qt::Key_Left: { 
      angleMorty += M_PI/4.f;    	
      break;
    }
    case Qt::Key_Right: {
	  angleMorty -= M_PI/4.f; 
      break;
    }
    case Qt::Key_Q: {
	  if (rotCam < M_PI/2)
      	rotCam += M_PI/90;    	
      break;
    }
	case Qt::Key_E: {
	  if (rotCam > 0.f)
      	rotCam -= M_PI/90;	
      break;
    }
	case Qt::Key_C: {
	  minicam = not minicam;
      break;
    }
	case Qt::Key_G: {
	  invisible = not invisible;
      break;
    }
	case Qt::Key_R: {
	  iniCamera();
	  invisible = false;
	  minicam = false;
	  rotCam = M_PI/4;
	  angleMorty = 0;
	  posMorty = glm::vec3(1,0,0);
      break;
    }
	default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::carregaShaders()
{
  LL2GLWidget::carregaShaders();
  filtreLoc  = glGetUniformLocation (program->programId(), "filtre");
}

void MyGLWidget::resizeGL (int w, int h) 
{
  ample = w;
  alt = h;
  ra = float(ample)/float(alt);
  if (ra < 1){
	fov = 2*atan(tan(alfaini)/ra);
  }
  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  projectTransform();
}
