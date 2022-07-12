#include "NouGLWidget.h"

#include <iostream>

NouGLWidget::NouGLWidget(QWidget *parent) : MyGLWidget(parent) {
  grabKeyboard();
}

NouGLWidget::~NouGLWidget ()
{
}

void NouGLWidget::paintGL() {
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#endif

  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  //  glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //--------------------------------------------------------
  // Activem el VAO per a pintar el terra
  glBindVertexArray (VAO_Terra);  
  // pintem terra
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 12);

  //--------------------------------------------------------
  // Activem el VAO per a pintar el Patricio
  glBindVertexArray (VAO_Pat);
  // pintem el Patricio
  modelTransformPatricio();
  glDrawArrays(GL_TRIANGLES, 0, patModel.faces().size()*3);

  //--------------------------------------------------------
  modelTransformPatricio2();
  glDrawArrays(GL_TRIANGLES, 0, patModel.faces().size()*3);

  glBindVertexArray(0);
}

void NouGLWidget::iniCamera ()
{
  rav = 1.0;
  angleY = 0.0;       //
  angleX = M_PI/6;    //

  projectTransform();
  viewTransform();
}

void NouGLWidget::iniEscena ()
{
  MyGLWidget::iniEscena();
  centreEsc = glm::vec3 (4, 2, 4);
  radiEsc = 6;
}

void NouGLWidget::projectTransform ()
{
  float fov, zn, zf;
  glm::mat4 Proj;  // Matriu de projecció
  
  if(camIni) {
    fov = 2*asin(0.5);
    zn = radiEsc;
    zf = 3*radiEsc;
  }
  else {
    fov = float(M_PI/2.0);
    zn = 0.1;
    zf = 3*radiEsc;
  }
  Proj = glm::perspective(fov, rav, zn, zf);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void NouGLWidget::viewTransform ()
{
  // Matriu de posició i orientació
  if(camIni) {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);
  }
  else {
    View = glm::lookAt(glm::vec3(posPat2X,posPat2Y,posPat2Z), glm::vec3(posPat2X,posPat2Y,0) ,glm::vec3(0,1,0));
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void NouGLWidget::modelTransformPatricio()
{
  // Codi per a la TG necessària
  glm::mat4 patTG = glm::mat4(1.0f);
  patTG = glm::translate(patTG, glm::vec3(2.0,0.0,1.0));
  patTG = glm::rotate(patTG, float(90*M_PI/180), glm::vec3(0,1,0));
  patTG = glm::scale(patTG, glm::vec3(escalaPat*2, escalaPat*2, escalaPat*2));
  patTG = glm::translate(patTG, -centreBasePat);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &patTG[0][0]);
}

void NouGLWidget::modelTransformPatricio2()
{
  // Codi per a la TG necessària
  glm::mat4 patTG = glm::mat4(1.0f);
  patTG = glm::translate(patTG, glm::vec3(posPat2X,0.0,posPat2Z));
  patTG = glm::rotate(patTG, float(M_PI), glm::vec3(0,1,0));
  patTG = glm::scale(patTG, glm::vec3(escalaPat*3, escalaPat*3, escalaPat*3));
  patTG = glm::translate(patTG, -centreBasePat);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &patTG[0][0]);
}

void NouGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  MyGLWidget::initializeGL();
  colorFocusC = glm::vec3(0.0,0.0,0.0);
  glUniform3fv(posFocusLoc, 1, &colorFocusC[0]);
  movX = 0.0;
  movZ = 0.0;
  camIni = true;
  posPat2X = 4.0;
  posPat2Y = 3.5;
  posPat2Z = 6.0;
}

void NouGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: {
      if(posPat2Z != 8) posPat2Z += 0.5;
      break;
    }
    case Qt::Key_W: {
      if(posPat2Z != 0) posPat2Z -= 0.5;
      break;
    }
    case Qt::Key_A: {
      if(posPat2X != 0) posPat2X -= 0.5;
      break;
    }
    case Qt::Key_D: {
      if(posPat2X != 8)posPat2X += 0.5;
      break;
    }
    case Qt::Key_C: {
      camIni = !camIni;
      viewTransform();
      projectTransform();
      break;
    }
    default: {
      MyGLWidget::keyPressEvent(event);
      break;
    }
  }
  update();
}

  
