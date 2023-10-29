TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm /home/gerdy/Desktop/IDI/Model

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp \
		/home/gerdy/Desktop/IDI/Model/model.cpp \
