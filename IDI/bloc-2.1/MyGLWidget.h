// MyGLWidget.h
#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include "BL2GLWidget.h"
#include "model.h"


struct Objecte{
	GLuint VAO;
	GLuint VBO[2];
	Model model;
	glm::mat4 TG;
};

struct Camera{
	glm::vec3 OBS;
	glm::vec3 VRP;
	glm::vec3 UP;
	GLfloat ra;
	GLfloat zN;
	GLfloat zF;
	GLfloat FOV;
	glm::mat4 Proj;
	glm::mat4 View;
};

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();
  
  protected:
    virtual void carregaShaders();
	virtual void paintGL();
	virtual void initializeGL();
	virtual void creaBuffers();
	virtual void keyPressEvent(QKeyEvent *event);
	void projectTransform();
	void ini_camera();
	void viewTransform();
	void modelTransformHomer();
	void modelTransformTerra();

  private:
    int printOglError(const char file[], int line, const char func[]);

	Objecte Homer;
	Objecte Terra;
	Camera Cam;

	GLuint projLoc;
	GLuint viewLoc;
};
#endif