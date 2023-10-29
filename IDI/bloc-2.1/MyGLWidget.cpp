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

//Inicialitza el model.
void MyGLWidget::initializeGL ()
{
  initializeOpenGLFunctions(); //Inici funcions OpenGL
  glClearColor(0.5, 0.7, 1.0, 1.0); //Color de fons
  carregaShaders(); //Carregar els shaders
  creaBuffers(); //Crear els buffers
  ini_camera(); //Inici camera
  escala = 1.0f; //Valor d'escalat
  Homer.TG = glm::mat4(1.0f); //TG identitat als objectes
  Terra.TG = glm::mat4(1.0f);
  glEnable(GL_DEPTH_TEST); //Perque funcioni el z-buffer
}

//Carrega els shaders i localitza tots els in i uniform.
void MyGLWidget::carregaShaders()
{
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation (program->programId(), "proj");
	viewLoc = glGetUniformLocation (program->programId(), "view");
}

//Crea els buffers.
void MyGLWidget::creaBuffers(){
	//Homer
	Homer.model.load("/home/gerdy/Desktop/IDI/models/HomerProves.obj"); //Carrega el model
	glGenVertexArrays(1, &Homer.VAO); //Genera el VAO
	glBindVertexArray(Homer.VAO); //Activa el VAO
	glGenBuffers(2, Homer.VBO); //Genera 2 VBO
	glBindBuffer(GL_ARRAY_BUFFER, Homer.VBO[0]); //Activa el primer VBO (vertex)
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Homer.model.faces().size()*3*3, Homer.model.VBO_vertices(), GL_STATIC_DRAW); //Inclou els vertexs al VBO
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Localitzacio on enviar el VBO al VS
	glEnableVertexAttribArray(vertexLoc);
	glBindBuffer(GL_ARRAY_BUFFER, Homer.VBO[1]); //Activa el segon VBO (color)
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Homer.model.faces().size()*3*3, Homer.model.VBO_matdiff(), GL_STATIC_DRAW); //Inclou els colors al VBO
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Localitzacio on enviar el VBO al VS
	glEnableVertexAttribArray(colorLoc);

	//Terra
	glm::vec3 Terra_vertex[6]= { //Vertexs
		glm::vec3(2., -1., 2.),
		glm::vec3(2., -1., -2.),
		glm::vec3(-2., -1., 2.),
		glm::vec3(-2., -1., -2.),
		glm::vec3(-2., -1., 2.),
		glm::vec3(2., -1., -2.)
	};
	glm::vec3 Terra_color[6]= { //Colors
		glm::vec3(1., 0., 0.),
		glm::vec3(1., 1., 0.),
		glm::vec3(1., 1., 0.),
		glm::vec3(1., 0., 0.),
		glm::vec3(1., 1., 0.),
		glm::vec3(1., 1., 0.)
	};
	glGenVertexArrays(1, &Terra.VAO); //Genera VAO
	glBindVertexArray(Terra.VAO); //Activa el VAO
	glGenBuffers(2, Terra.VBO); //Genera 2 VBO
	glBindBuffer(GL_ARRAY_BUFFER, Terra.VBO[0]); //Activa el primer VBO (vertex)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Terra_vertex), Terra_vertex, GL_STATIC_DRAW); //Inclou els vertexs al VBO
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Localitzacio on enviar el VBO al VS
	glEnableVertexAttribArray(vertexLoc);
	glBindBuffer(GL_ARRAY_BUFFER, Terra.VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Terra_color), Terra_color, GL_STATIC_DRAW); //Inclou els colors al VBO
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Localitzacio on enviar el VBO al VS
	glEnableVertexAttribArray(colorLoc);

	glBindVertexArray (0); //Desactivar VAO
}

//Inicialitza la camera
void MyGLWidget::ini_camera ()
{
	Cam.OBS = glm::vec3(0,0,1);
	Cam.VRP = glm::vec3(0,0,0);
	Cam.UP = glm::vec3(0,1,0);
	Cam.ra = 1;
	Cam.zN = 0.4;
	Cam.zF = 3;
	Cam.FOV = M_PI/2;
}

//Envia la proj mat al VS
void MyGLWidget::projectTransform()
{
    Cam.Proj = glm::perspective(Cam.FOV, Cam.ra, Cam.zN, Cam.zF);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Cam.Proj[0][0]);
}

//Envia la view mat al VS
void MyGLWidget::viewTransform()
{
    Cam.View = glm::lookAt(Cam.OBS, Cam.VRP, Cam.UP);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &Cam.View[0][0]);
}

//TG del Terra
void MyGLWidget::modelTransformTerra () 
{
  glm::mat4 TG2 = glm::scale(Terra.TG, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG2[0][0]);
}

//TG del Homer
void MyGLWidget::modelTransformHomer () 
{
  glm::mat4 TG2 = glm::scale(Homer.TG, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG2[0][0]);
}

//Pinta l'escena.
void MyGLWidget::paintGL () 
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Esborra el frame-buffer

	//Camera
	projectTransform(); //Prepara la project matrix
	viewTransform(); //Prepara la view matrix

	//Homer
	modelTransformHomer(); //Carrega la transformacio del Homer
	glBindVertexArray (Homer.VAO); //Activar VAO Homer
	glDrawArrays(GL_TRIANGLES, 0, Homer.model.faces().size()*3); //Pintar

	//Terra
	modelTransformTerra(); //Carrega la transformacio del Terra
	glBindVertexArray (Terra.VAO); //Activa el VAO Terra
	glDrawArrays(GL_TRIANGLES, 0, 6); //Pintar

	glBindVertexArray (0); //Desactivar el VAO
}

//Interaccio amb el teclat
void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    }
	case Qt::Key_R: { // escalar a més petit
	  Homer.TG = glm::rotate(Homer.TG, float(M_PI)/4, glm::vec3(0.,1.,0.));
      break;
    }
    default: event->ignore(); break;
  }
  update();
}
