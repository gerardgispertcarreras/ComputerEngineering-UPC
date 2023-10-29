// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"
#include <vector>

enum camType {
	perspective,
	orthogonal
};

struct Objecte{
	GLuint VAO;
	GLuint VBO[2];
	Model model;
	glm::mat4 TG;
	GLfloat xmin, xmax, ymin, ymax, zmin, zmax;
};

struct capsaContenidora{
	glm::vec3 Pmin;
	glm::vec3 Pmax;
	glm::vec3 centre;
	GLfloat radi;
	GLfloat dist;
	GLfloat alfaini;
};

struct Camera{
	glm::vec3 OBS;
	glm::vec3 VRP;
	glm::vec3 UP;
	GLfloat ra;
	GLfloat zN;
	GLfloat zF;
	GLfloat FOV;
	GLfloat psi;
	GLfloat theta;
	GLfloat left, right, bottom, top, mida;
	camType type;
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
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	void projectTransform();
	void iniCamera();
	void viewTransform();
	void modelTransformPatricio();
	void modelTransformTerra();
	void calcularCapsaContenidora();
	void resizeGL(int w, int h);
	void calcularCapsaPatricio();
	void calculateWindow();
	void calcularFOV();

  private:
    int printOglError(const char file[], int line, const char func[]);

	Objecte Patricio;
	Objecte Terra;
	Camera Cam;
	capsaContenidora cpCont;

	GLuint projLoc;
	GLuint viewLoc;
	GLint rot;
	GLint xant, yant;
	GLfloat angleX, angleY;
};
