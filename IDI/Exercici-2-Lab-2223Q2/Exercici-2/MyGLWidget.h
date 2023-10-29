#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
	virtual void RickTransform();
	virtual void VideoCameraTransform ();
	virtual void MortyTransform ();
	virtual void paintGL ();
	virtual void iniEscena();
	virtual void iniCamera();
	virtual void viewTransform ();
	virtual void viewTransform2 ();
	virtual void projectTransform2 ();
	virtual glm::vec3 calcularVRP();
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void carregaShaders();
	virtual void resizeGL (int w, int h);

  private:

  
    int printOglError(const char file[], int line, const char func[]);
    
	GLfloat psi, theta;
	glm::vec3 Pmin, Pmax;
	GLfloat dist, alfaini;
	GLfloat rotCam;
	bool minicam = false;
	bool invisible = false;
	GLuint filtreLoc;
};
