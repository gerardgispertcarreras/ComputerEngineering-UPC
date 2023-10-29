// MyGLWidget.h
#include "BL3GLWidget.h"
#include "glm/gtc/matrix_inverse.hpp"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
	virtual void carregaShaders();
	virtual void initializeGL();
	virtual void paintGL();
	virtual void iniLlum();
	GLuint NormalMatrixLoc, posFocusLoc, colorFocusLoc;
	glm::vec3 colorFocus = glm::vec3(0.8, 0.8, 0.8);
	glm::vec3 posFocus;
	bool fescena = true;

  private:
    int printOglError(const char file[], int line, const char func[]);
	void normalTransform();
};
