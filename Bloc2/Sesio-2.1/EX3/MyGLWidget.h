// MyGLWidget.h
#include "BL2GLWidget.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);

    void projectTransform();
    void carregaShaders();
    void paintGL();
    void modelTransform();
    void viewTransform();
    void ini_camera();
    
    GLuint projLoc, viewLoc;
};
