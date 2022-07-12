// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra();    //Ex3
    virtual void initializeGL ();       //EX5

  private:
    int printOglError(const char file[], int line, const char func[]);
    void carregaShaders();        //EX5
    void iniFocus();
    GLuint posFLoc, colFLoc;      //EX5
    float focusX = 1.0;     //EX6
};
