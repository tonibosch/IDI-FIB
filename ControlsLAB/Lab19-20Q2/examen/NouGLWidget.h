#include "MyGLWidget.h"

class NouGLWidget : public MyGLWidget
{
 Q_OBJECT
	   
 public:
  NouGLWidget (QWidget *parent=NULL);
  ~NouGLWidget ();

 public slots:

 signals:

 protected:
  void paintGL ();
  void iniCamera ();
  void iniEscena ();
  void viewTransform ();
  void projectTransform ();
  void modelTransformPatricio();
  void modelTransformPatricio2();
  void initializeGL();
  
  // keyPressEvent - Es cridat quan es prem una tecla
  void keyPressEvent (QKeyEvent *event);
  
 private:
    glm::vec3 colorFocusC;
    float movX, movZ;
    bool camIni;
    float posPat2X, posPat2Y, posPat2Z;

};
