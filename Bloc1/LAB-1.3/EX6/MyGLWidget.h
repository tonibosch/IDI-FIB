#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"

#include <QKeyEvent> 
#include "glm/gtc/matrix_transform.hpp"
#define GLM_FORCE_RADIANS

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();                               //Coge la geometria y shaders y se los manda a las GPU

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();                                    //Cada vez que sea necesario repintar la ventana,
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);             //Para cada vez que se redimensiona la ventana 

    virtual void keyPressEvent (QKeyEvent *e);

    void modelTransform1();

    void modelTransform2();


  private:
    void creaBuffers ();
    void carregaShaders ();
    
    // attribute locations
    GLuint vertexLoc;
    GLuint transLoc;
    float angle;
    
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1,VAO2;
    GLint ample, alt;
};
