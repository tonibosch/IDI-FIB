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
    void calcul_punts();

    virtual void resizeGL (int width, int height);

    virtual void keyPressEvent (QKeyEvent *event);
    float angleGir = 0;

    Model Homer;
    GLuint VAO_Homer;
    GLuint VAO_Terra;
    GLuint projLoc, viewLoc;

    float R, d, znear, zfar, fov, rav;
    float xmax = 2.0, ymax = 1.0, zmax = 2.0, xmin = -2.0, ymin = -1.0, zmin = -2.0, xcentre_capsa, ycentre_capsa, zcentre_capsa;           
    //Definim el punt màxim i miním de la capsa contenidora.  
    float xobs = 0.0, yobs = 0.0, zobs = 1.0, xvrp = 0.0, yvrp = 0.0, zvrp = 0.0, xup = 0.0, yup = 1.0, zup = 0.0;

};