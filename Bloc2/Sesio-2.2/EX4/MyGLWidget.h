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
    void modelTransform_Patricio();
    void modelTransform_Terra();
    void ini_camera();
    void projectTransform();
    void viewTransform();
    void paintGL();
    void calcul_punts();
    void calcul_capsaPatricio();

    virtual void resizeGL (int width, int height);

    virtual void keyPressEvent (QKeyEvent *event);
    float angleGir = 0;

    Model Patricio;
    GLuint VAO_Patricio;
    GLuint VAO_Terra;
    GLuint projLoc, viewLoc;

    float R, d, znear, zfar, fov, rav;
    float xmax, ymax, zmax, xmin, ymin, zmin, xcentre_capsa, ycentre_capsa, zcentre_capsa, xbase_capsa, ybase_capsa, zbase_capsa;           
    //Definim el punt màxim i miním de la capsa contenidora.  
    float xobs = 0.0, yobs = 2.0,xup = 0.0, yup = 1.0, zup = 0.0;
};