#include "ExamGLWidget.h"

enum selec {patricio, cubs};

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT
	public slots:
		void canviaCub1();
		void canviaCub2();
		void canviaCub3();
		void canviaCamera1();
		void canviaCamera2();

	signals:
		void cub1();
		void cub2();
		void cub3();
		void camera1();
		void camera2();

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
		virtual void initializeGL ();
		virtual void iniPintat ();
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

	int cubSeleccionat;
	selec selecPaint;
	float posCub[3];

  private:
    int printOglError(const char file[], int line, const char func[]);
};
