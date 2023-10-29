#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  menjat = false;
  scl = 1;
  angle = 0;
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersQuadrat();
  creaBuffersCavall();
}


void MyGLWidget::modelTransformQuadrat(glm::vec3 posicio)
{
  glm::mat4 TG(1.0f);
  TG = glm::rotate(TG, (float(M_PI)/2) * angle, glm::vec3 (0.,0.,1.0));
  TG = glm::translate(TG,posicio*scl);
  TG = glm::scale(TG, glm::vec3(0.25*scl, 0.25*scl, 0.));
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCavall(glm::vec3 posicio)
{
  glm::mat4 TG(1.0f);
  TG = glm::rotate(TG, float(M_PI) *angle / 2, glm::vec3 (0.,0.,1.0));
  TG = glm::translate(TG,posicio*scl);
  TG = glm::rotate(TG, float(M_PI) / 2, glm::vec3 (0.,0.,1.0));
  TG = glm::scale(TG, glm::vec3 (0.08*scl,0.08*scl,0.));
  TG = glm::translate(TG,glm::vec3(-1.25,-0.8, 0.));
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]); 
}


void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer


  // Pintem el tauler
  glBindVertexArray(VAOQuadrat);
  
  for (int i = 1; i <= 16; i += 2)
  {
	for (int j = 1; j <= 16; j += 2)
	{
		if ((i + j) % 4 == 2)
			glUniform3fv(colorLoc, 1, &negreTauler[0]);
		else
			glUniform3fv(colorLoc, 1, &blancTauler[0]);
		modelTransformQuadrat(glm::vec3(0.125*j - 1, 0.125*i - 1 ,0.0));
  		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
  }
  glBindVertexArray(0);

  /* Pintem un quadrat
  glBindVertexArray(VAOQuadrat);
  modelTransformQuadrat(glm::vec3(-0.5,-0.5,0.0));
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  */
  
  // Pintem un cavall
  glBindVertexArray(VAOCavall);
  if (not menjat)
  {
  modelTransformCavall(glm::vec3(0.125,0.125, 0.));
  glUniform3fv(colorLoc, 1, &negre[0]);
  glDrawArrays(GL_TRIANGLES, 0, 45);
  modelTransformCavall(glm::vec3(-0.125,-0.375, 0.));
  glUniform3fv(colorLoc, 1, &blanc[0]);
  glDrawArrays(GL_TRIANGLES, 0, 45);
  glBindVertexArray(0);
  }
  else
  {
	modelTransformCavall(glm::vec3(0.125,0.125, 0.));
  	glUniform3fv(colorLoc, 1, &blanc[0]);
  	glDrawArrays(GL_TRIANGLES, 0, 45);
  }
  
  // Desactivem el VAO
  glBindVertexArray(0);

}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S:
		if(scl < 2.)
			scl += 0.1;
    	break;
    case Qt::Key_D:
		if(scl > 0.1)
			scl -= 0.1;
    	break;
    case Qt::Key_E:
		angle += (1./90);
    	break;
    case Qt::Key_R: 
		angle -= (1./90);
    	break;		
    case Qt::Key_C:
		menjat = not menjat;
    	break;
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffersQuadrat ()
{
  glm::vec3 Vertices[6];  // vèrtexs amb X, Y i Z
  
  // minX = -0.5
  // maxX = 0.5
  // minY = -0.5
  // maxY = 0.5
  
  Vertices[0] = glm::vec3(-0.5, -0.5, 0);
  Vertices[1] = glm::vec3( 0.5, -0.5, 0);
  Vertices[2] = glm::vec3( 0.5, 0.5, 0);
  Vertices[3] = glm::vec3( 0.5, 0.5, 0);
  Vertices[4] = glm::vec3( -0.5, 0.5, 0);
  Vertices[5] = glm::vec3( -0.5, -0.5, 0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar el quadrat
  glGenVertexArrays(1, &VAOQuadrat);
  glBindVertexArray(VAOQuadrat);

  // Creació del buffer amb les posicions dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}


void MyGLWidget::creaBuffersCavall()
{
  // minX = 0.1
  // maxX = 2.6
  // minY = 0.1
  // maxY = 1.6

  glm::vec3 Vertices[45];  // vèrtexs amb X, Y i Z  
  Vertices[ 0] =  glm::vec3(0.1, 0.3, 0.0);
  Vertices[ 1] =  glm::vec3(0.1, 1.6, 0.0);
  Vertices[ 2] =  glm::vec3(0.3, 0.7, 0.0);
  Vertices[ 3] =  glm::vec3(0.3, 0.7, 0.0);
  Vertices[ 4] =  glm::vec3(0.1, 1.6, 0.0);
  Vertices[ 5] =  glm::vec3(0.3, 1.2, 0.0);
  Vertices[ 6] =  glm::vec3(0.8, 0.4, 0.0);
  Vertices[ 7] =  glm::vec3(0.3, 0.7, 0.0);
  Vertices[ 8] =  glm::vec3(0.8, 0.7, 0.0);
  Vertices[ 9] =  glm::vec3(0.8, 0.7, 0.0);
  Vertices[10] =  glm::vec3(0.3, 0.7, 0.0);
  Vertices[11] =  glm::vec3(0.8, 1.2, 0.0);
  Vertices[12] =  glm::vec3(0.8, 1.2, 0.0);
  Vertices[13] =  glm::vec3(0.3, 0.7, 0.0);  
  Vertices[14] =  glm::vec3(0.3, 1.2, 0.0);
  Vertices[15] =  glm::vec3(0.8, 1.2, 0.0);  
  Vertices[16] =  glm::vec3(0.3, 1.2, 0.0);   
  Vertices[17] =  glm::vec3(0.8, 1.5, 0.0);
  Vertices[18] =  glm::vec3(1.2, 0.7, 0.0);
  Vertices[19] =  glm::vec3(0.8, 0.4, 0.0);
  Vertices[20] =  glm::vec3(1.3, 1.7, 0.0);
  Vertices[21] =  glm::vec3(1.3, 1.7, 0.0);  
  Vertices[22] =  glm::vec3(0.8, 0.4, 0.0);
  Vertices[23] =  glm::vec3(0.8, 1.5, 0.0);   
  Vertices[24] =  glm::vec3(1.2, 0.7, 0.0);    
  Vertices[25] =  glm::vec3(1.3, 1.7, 0.0); 
  Vertices[26] =  glm::vec3(1.6, 1.0, 0.0);  
  Vertices[27] =  glm::vec3(1.6, 1.0, 0.0); 
  Vertices[28] =  glm::vec3(1.3, 1.7, 0.0);  
  Vertices[29] =  glm::vec3(2.0, 1.7, 0.0);
  Vertices[30] =  glm::vec3(1.6, 1.0, 0.0);  
  Vertices[31] =  glm::vec3(2.0, 1.7, 0.0);
  Vertices[32] =  glm::vec3(2.2, 1.0, 0.0); 
  Vertices[33] =  glm::vec3(1.6, 1.0, 0.0);  
  Vertices[34] =  glm::vec3(2.2, 1.0, 0.0);
  Vertices[35] =  glm::vec3(2.2, 0.7, 0.0);  
  Vertices[36] =  glm::vec3(2.2, 0.7, 0.0);   
  Vertices[37] =  glm::vec3(2.2, 1.0, 0.0);
  Vertices[38] =  glm::vec3(2.6, 0.6, 0.0);     
  Vertices[39] =  glm::vec3(1.6, 1.0, 0.0);
  Vertices[40] =  glm::vec3(2.2, 0.7, 0.0);       
  Vertices[41] =  glm::vec3(1.4, 0.1, 0.0);
  Vertices[42] =  glm::vec3(1.4, 0.1, 0.0);
  Vertices[43] =  glm::vec3(1.3, 0.4, 0.0);     
  Vertices[44] =  glm::vec3(1.6, 0.6, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar el cavall
  glGenVertexArrays(1, &VAOCavall);
  glBindVertexArray(VAOCavall);

  // Creació del buffer amb les posicions dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");

  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetUniformLocation (program->programId(), "color");
  
  // Obtenim els identificadors dels uniforms
  TGLoc = glGetUniformLocation(program->programId(), "TG");
}

