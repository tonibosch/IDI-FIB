// MyGLWidget.h
#include "BL2GLWidget.h"
#include "./Model/model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    void initializeGL();
    void creaBuffers();
    void carregaShaders();
    void modelTransform_Homer();
    void modelTransform_Terra();
    void ini_camera();
    void projectTransform();
    void viewTransform();
    void paintGL();

    virtual void keyPressEvent (QKeyEvent *event);
    float angleGir = 0;

    Model Homer;
    GLuint VAO_Homer;
    GLuint VAO_Terra;
    GLuint projLoc, viewLoc;
};
