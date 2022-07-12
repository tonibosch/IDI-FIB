// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
  private:
    int printOglError(const char file[], int line, const char func[]);
    void carregaShaders();
    void initializeGL();
    void modelTransformPatricio();
    void modelTransformFocusPatricio();

    GLuint camLoc, escLoc, focusPLoc, colorPLoc, transFocusPLoc;
    glm::vec3 colorFocusC, colorFocusE, posFocusP, colorFocusP;

    float angle = 0;
    glm::mat4 TG2;
    bool onFC, onFE, onFP;
    float colorCx, colorCy, colorCz;
    float colorEx, colorEy, colorEz;
    float colorPx, colorPy, colorPz;

};
