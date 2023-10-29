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
	escala = 1.0f; //Valor d'escalat
	rot = 0; //Variable de rotacions
	Cam.type = perspective; //Càmera amb inicialització a perspective
	cpCont.Pmin = glm::vec3(-2.5, 0., -2.5);
	cpCont.Pmax = glm::vec3(2.5, 4., 2.5);
	calcularCapsaPatricio(); //Calcular la capsa del Patricio
	calcularCapsaContenidora(); //Calcular capsa contenidora
	iniCamera(); //Inicialitza els paràmetres de la càmera
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
	//Patricio
	Patricio.model.load("/home/gerdy/Desktop/IDI/models/Patricio.obj"); //Carrega el model
	glGenVertexArrays(1, &Patricio.VAO); //Genera el VAO
	glBindVertexArray(Patricio.VAO); //Activa el VAO
	glGenBuffers(2, Patricio.VBO); //Genera 2 VBO
	glBindBuffer(GL_ARRAY_BUFFER, Patricio.VBO[0]); //Activa el primer VBO (vertex)
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Patricio.model.faces().size()*3*3, Patricio.model.VBO_vertices(), GL_STATIC_DRAW); //Inclou els vertexs al VBO
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Localitzacio on enviar el VBO al VS
	glEnableVertexAttribArray(vertexLoc);
	glBindBuffer(GL_ARRAY_BUFFER, Patricio.VBO[1]); //Activa el segon VBO (color)
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Patricio.model.faces().size()*3*3, Patricio.model.VBO_matdiff(), GL_STATIC_DRAW); //Inclou els colors al VBO
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0); //Localitzacio on enviar el VBO al VS
	glEnableVertexAttribArray(colorLoc);

	//Terra
	glm::vec3 Terra_vertex[6]= { //Vertexs
		glm::vec3(2.5, 0., 2.5),
		glm::vec3(2.5, 0., -2.5),
		glm::vec3(-2.5, 0., 2.5),
		glm::vec3(-2.5, 0., -2.5),
		glm::vec3(-2.5, 0., 2.5),
		glm::vec3(2.5, 0., -2.5)
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

//Guarda en l'Objecte les seves coordenades màximes i mínimes.
void MyGLWidget::calcularCapsaPatricio(){
	std::vector<double> vertex = Patricio.model.vertices(); //Vector de cada coordenada dels vèrtex del model
	Patricio.xmin = Patricio.xmax = vertex[0]; //Init de les variables
	Patricio.ymin = Patricio.ymax = vertex[1];
	Patricio.zmin = Patricio.zmax = vertex[2];
	for (long unsigned int i = 3; i < vertex.size(); i+=3){ //Bucle per cada vèrtex on comproba les coordenades
		if (Patricio.xmin > vertex[i]) Patricio.xmin = vertex[i];
		else if (Patricio.xmax < vertex[i]) Patricio.xmax = vertex[i];
		if (Patricio.ymin > vertex[i+1]) Patricio.ymin = vertex[i+1];
		else if (Patricio.ymax < vertex[i+1]) Patricio.ymax = vertex[i+1];
		if (Patricio.zmin > vertex[i+2]) Patricio.zmin = vertex[i+2];
		else if (Patricio.zmax < vertex[i+2]) Patricio.zmax = vertex[i+2];
	}
}

//Calcula els atributs de la capsa contenidora.
void MyGLWidget::calcularCapsaContenidora(){
	cpCont.centre = (cpCont.Pmax+cpCont.Pmin)/2.f; //Centre de la capsa i esfera
	cpCont.radi = distance(cpCont.centre, cpCont.Pmax); //Radi de l'esfera englobant
	cpCont.dist = 2.*cpCont.radi; //Distància VRP-OBS
	cpCont.alfaini = asin(cpCont.radi/cpCont.dist); //Angle des de OBS fins el límit de visió
}

//Inicialitza la camera
void MyGLWidget::iniCamera ()
{
	Cam.VRP = cpCont.centre;
	Cam.OBS = Cam.VRP + cpCont.dist*glm::vec3(0., 0., 1.);
	Cam.UP = glm::vec3(0,1,0);
	Cam.zN = cpCont.dist-cpCont.radi;
	Cam.zF = cpCont.dist+cpCont.radi;
	Cam.ra = 1.0f;
	Cam.FOV = 2.*cpCont.alfaini;
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

	//Patricio
	modelTransformPatricio(); //Carrega la transformacio del Patricio
	glBindVertexArray (Patricio.VAO); //Activar VAO Patricio
	glDrawArrays(GL_TRIANGLES, 0, Patricio.model.faces().size()*3); //Pintar

	//Terra
	modelTransformTerra(); //Carrega la transformacio del Terra
	glBindVertexArray (Terra.VAO); //Activa el VAO Terra
	glDrawArrays(GL_TRIANGLES, 0, 6); //Pintar

	glBindVertexArray (0); //Desactivar el VAO
}

//Envia la proj mat al VS
void MyGLWidget::projectTransform()
{
	if (Cam.type == perspective)
    	Cam.Proj = glm::perspective(Cam.FOV, Cam.ra, Cam.zN, Cam.zF);
	else if (Cam.type == orthogonal){
		if (Cam.ra >= 1)
			Cam.Proj = glm::ortho(- cpCont.radi*Cam.ra, + cpCont.radi*Cam.ra, -cpCont.radi, +cpCont.radi, Cam.zN, Cam.zF);
		else
			Cam.Proj = glm::ortho(- cpCont.radi, + cpCont.radi, -cpCont.radi/Cam.ra, +cpCont.radi/Cam.ra, Cam.zN, Cam.zF);
	}
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Cam.Proj[0][0]);
}

//Envia la view mat al VS
void MyGLWidget::viewTransform()
{
    Cam.View = glm::lookAt(Cam.OBS+glm::vec3(0,1,0), Cam.VRP, Cam.UP);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &Cam.View[0][0]);
}

//TG del Patricio
void MyGLWidget::modelTransformPatricio() 
{
	GLfloat alt = Patricio.ymax-Patricio.ymin; //Altura del Patricio
	Patricio.TG = glm::mat4(1.0f);
	Patricio.TG = glm::rotate(Patricio.TG, float(M_PI*rot)/4, glm::vec3(0.,1.,0.)); //Rotació
	Patricio.TG = glm::scale(Patricio.TG, glm::vec3(escala)); //Escalat
	Patricio.TG = glm::scale(Patricio.TG, glm::vec3(4./alt, 4./alt, 4./alt)); //Que tingui mida 4
	Patricio.TG = glm::translate(Patricio.TG, -glm::vec3((Patricio.xmax+Patricio.xmin)/2., Patricio.ymin, (Patricio.zmax+Patricio.zmin)/2.)); //Portar la base del Patricio a (0,0,0)
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &Patricio.TG[0][0]); //Linka la TG amb el localitzador que té el VS
}

//TG del Terra
void MyGLWidget::modelTransformTerra () 
{
	Terra.TG = glm::mat4(1.0f);
	glm::mat4 TG2 = glm::scale(Terra.TG, glm::vec3(escala)); //Escalat
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG2[0][0]);
}

//Resize del viewport
void MyGLWidget::resizeGL (int w, int h) 
{
	ample = w;
	alt = h;
	Cam.ra = float(ample)/alt;
	GLfloat alfa;
	if (Cam.ra >= 1)
		alfa = cpCont.alfaini;
	else
		alfa = atan(tan(cpCont.alfaini/Cam.ra));
	Cam.FOV = 2.*alfa;
}

//Interacció amb el teclat
void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
	makeCurrent();
	switch (event->key()) {
		case Qt::Key_S: { //Escalar a més gran
			escala += 0.05;
			break;
		}
		case Qt::Key_D: { //Escalar a més petit
			escala -= 0.05;
			break;
		}
		case Qt::Key_R: { //Rotar 45 graus
			rot += 1;
			break;
		}
		case Qt::Key_O: { //Canviar tipus de càmera.
			if (Cam.type == perspective)
				Cam.type = orthogonal;
			else if (Cam.type == orthogonal)
				Cam.type = perspective;
		break;
		}
		default: event->ignore(); break;
	}
	update();
}
