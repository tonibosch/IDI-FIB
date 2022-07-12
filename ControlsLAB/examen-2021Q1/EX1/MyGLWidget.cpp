// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  //Pintem el Patricio
  if(pintar_nomes_patr){
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  else {
    // Pintem el cub
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.0*2.0, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    modelTransformCub (2.0*2.5,  float(2.0*M_PI/3));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    modelTransformCub (2.0*3.0, float(2.0*2.0*M_PI/3));
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angle+despHorari, glm::vec3(0.,1.,0.));
  TG = glm::translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = glm::scale(TG, glm::vec3 (escala, escala, escala));
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    //Mètode que has de modificar
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, MovPatr+despHorari, glm::vec3(0.,1.,0.));
  TG = glm::translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = glm::rotate(TG, float(2.0*-M_PI/4), glm::vec3(1.,0.,0.));
  TG = glm::scale(TG, glm::vec3 (2.0*escala, 2.0*escala, 2.0*escala));
  TG = glm::translate(TG, -centreBasePat);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    //Mètode que has de modificar
{
  if (!camPlanta) {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
    View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);
  }
  else {
    View = glm::lookAt(glm::vec3(0,2*radiEsc,0), glm::vec3(0,0,0) ,glm::vec3(1,0,0));
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  if (!camPlanta)
    Proj = glm::perspective(fov, ra, zn, zf);
  else {
    Proj = glm::ortho(-radiEsc,radiEsc,-radiEsc,radiEsc,radiEsc, 3*radiEsc);
  }
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}


void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      if(pintar_nomes_patr) pintar_nomes_patr = false;
      else pintar_nomes_patr = true;
    break;
	}
  case Qt::Key_1: {
    MovPatr = 0;
    modelTransformPatricio();
    break;
	}
  case Qt::Key_2: {
    MovPatr = 2.0*(M_PI/3.0);
    modelTransformPatricio();
    break;
	}
  case Qt::Key_3: {
    MovPatr = 2.0*2.0*(M_PI/3.0);
    modelTransformPatricio();
    break;
	}
  case Qt::Key_F: {
      if(llum_blanca) {
          llum_blanca = false;
          colFoc = glm::vec3(1.0, 1.0, 0.0);
          enviaColFocus();
      }
      else {
          llum_blanca = true;
          colFoc = glm::vec3(1.0, 1.0, 1.0);
          enviaColFocus();
      }
    break;
	}
  case Qt::Key_C: {
      camPlanta = !camPlanta;
      projectTransform();
      viewTransform();  
    break;
	}
  case Qt::Key_Right: {
      despHorari += 2.0*(M_PI/3.0);
      paintGL();
    break;
	}
  case Qt::Key_Left: {
      despHorari -= 2.0*(M_PI/3.0);
      paintGL();
    break;
	}
  case Qt::Key_R: {
      initializeGL();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::initializeGL (){
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  iniEscena ();
  iniCamera ();
  pintar_nomes_patr = false;
  llum_blanca = true;
  MovPatr = 0;
  despHorari = 0;
}

