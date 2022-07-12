// MyGLWidget.h
#include "BL2GLWidget.h"
#include "../Model/model.h"

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
    void creaBuffers();
    void initializeGL(); 

    Model Homer;
    GLuint VAO_Homer;
    
    GLuint projLoc, viewLoc;
};
