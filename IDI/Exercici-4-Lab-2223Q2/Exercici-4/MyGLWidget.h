// MyGLWidget.h
#include "LL4GLWidget.h"
#include "glm/gtc/matrix_inverse.hpp"
#include <QTimer>

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();

  public slots:
    void updateAnimation();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
	virtual void initializeGL ();
	virtual void carregaShaders();
	virtual void iniLlum();
	virtual void normalMatrixTransform();
	virtual void paintGL ();
	virtual void modelTransformTerra ();
	virtual void modelTransformMorty ();
	virtual void modelTransformFantasma (float posX);
	virtual void modelTransformDiscoBall ();
	virtual void updateFocus();

	glm::mat3 NormalMatrix;
	glm::vec3 focusCol[5], focusPos[5];
	int focusBool[5] = {1, 1, 1, 1, 1};
	GLuint NormalMatrixLoc, focusColLoc, focusPosLoc, focusBoolLoc;
	glm::mat4 TG;

  private:
    int printOglError(const char file[], int line, const char func[]);
	void apagarFocus();
	void encendreFocus();
	int rotationDiscoBall, rotationDancers;
	QTimer *timer;
};
