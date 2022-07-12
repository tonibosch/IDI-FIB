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

void MyGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();

  iniEscena();
  iniCamera();

  colorCx = 0.9; colorCy = 0.0; colorCz = 0.9;
  colorEx = 0.9; colorEy = 0.9; colorEz = 0.9;
  colorPx = 0.9; colorPy = 0.9, colorPz = 0.2;

  colorFocusC = glm::vec3(colorCx, colorCy, colorCz);
  glUniform3fv(camLoc, 1, &colorFocusC[0]);

  colorFocusE = glm::vec3(colorEx, colorEy, colorEz);
  glUniform3fv(escLoc, 1, &colorFocusE[0]);

  colorFocusP = glm::vec3(colorPx, colorPy, colorPz);
  glUniform3fv(colorPLoc, 1, &colorFocusP[0]);

  posFocusP = glm::vec3(5.0, 3.0, 2.0);
  glUniform3fv(focusPLoc, 1, &posFocusP[0]);

  onFC = onFE = onFP = true;
}
void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_C: {
      if(onFC) {
        colorFocusC = glm::vec3(0.0, 0.0, 0.0);
        onFC = false;
      }
      else {
        colorFocusC = glm::vec3(colorCx, colorCy, colorCz);
        onFC = true;
      }
      glUniform3fv(camLoc, 1, &colorFocusC[0]);
    break;
	}
  case Qt::Key_E: {
      if(onFE) {
        colorFocusE = glm::vec3(0.0, 0.0, 0.0);
        onFE = false;
      }
      else {
        colorFocusE = glm::vec3(colorEx, colorEy, colorEz);
        onFE = true;
      }
      glUniform3fv(escLoc, 1, &colorFocusE[0]);
    break;
	}
  case Qt::Key_P: {
      if(onFP) {
        colorFocusP = glm::vec3(0.0, 0.0, 0.0);
        onFP = false;
      }
      else {
        colorFocusP = glm::vec3(colorPx, colorPy, colorPz);
        onFP = true;
      }
      glUniform3fv(colorPLoc, 1, &colorFocusP[0]);
    break;
	}
  case Qt::Key_Right: {
      angle += M_PI/6;
      modelTransformFocusPatricio();
    break;
	}
  case Qt::Key_Left: {
      angle -= M_PI/6;
      modelTransformFocusPatricio();
    break;
	}
  case Qt::Key_Q: {
    if(colorCx != 0.9) colorCx += 0.1;
    if(colorCz != 0.9) colorCz += 0.1;
    colorFocusC = glm::vec3(colorCx, colorCy, colorCz);
    if(colorEx != 0.9) colorEx += 0.1;
    if(colorEy != 0.9) colorEy += 0.1;
    if(colorEz != 0.9) colorEz += 0.1;
    colorFocusE = glm::vec3(colorEx, colorEy, colorEz);
    if(colorPx != 0.9) colorPx += 0.1;
    if(colorPy != 0.9) colorPy += 0.1;
    if(colorPz != 0.2) colorPz += 0.1;
    colorFocusP = glm::vec3(colorPx, colorPy, colorPz);
    glUniform3fv(camLoc, 1, &colorFocusC[0]);
    glUniform3fv(escLoc, 1, &colorFocusE[0]);
    glUniform3fv(colorPLoc, 1, &colorFocusP[0]);
    break;
	}
  case Qt::Key_A: {
    if(colorCx != 0.0) colorCx -= 0.1;
    if(colorCz != 0.0) colorCz -= 0.1;
    colorFocusC = glm::vec3(colorCx, colorCy, colorCz);
    if(colorEx != 0.0) colorEx -= 0.1;
    if(colorEy != 0.0) colorEy -= 0.1;
    if(colorEz != 0.0) colorEz -= 0.1;
    colorFocusE = glm::vec3(colorEx, colorEy, colorEz);
    if(colorPx != 0.0) colorPx -= 0.1;
    if(colorPy != 0.0) colorPy -= 0.1;
    if(colorPz != 0.0) colorPz -= 0.1;
    colorFocusP = glm::vec3(colorPx, colorPy, colorPz);
    glUniform3fv(camLoc, 1, &colorFocusC[0]);
    glUniform3fv(escLoc, 1, &colorFocusE[0]);
    glUniform3fv(colorPLoc, 1, &colorFocusP[0]);

  break;
	}
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicLlumShader.frag");
  vs.compileSourceFile("shaders/basicLlumShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "Proj");
  viewLoc = glGetUniformLocation (program->programId(), "View");

  camLoc = glGetUniformLocation(program->programId(), "colorC");
  escLoc = glGetUniformLocation (program->programId(), "colorE");

  focusPLoc = glGetUniformLocation(program->programId(), "FocusP");
  colorPLoc = glGetUniformLocation (program->programId(), "colorP");

  transFocusPLoc = glGetUniformLocation (program->programId(), "TG2");

}

void MyGLWidget::modelTransformPatricio ()
{
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG = glm::rotate(TG, angle, glm::vec3(0,1,0));
  TG = glm::translate(TG, glm::vec3(0,0,-3));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::translate(TG, -centreBasePatr);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformFocusPatricio() {
  TG2 = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG2 = glm::rotate(TG2,angle, glm::vec3(0,1,0)); 
  TG2 = glm::translate(TG2, glm::vec3(0,0,-3));
  TG2 = glm::translate(TG2, glm::vec3(-5,0,-2));
  
  glUniformMatrix4fv (transFocusPLoc, 1, GL_FALSE, &TG2[0][0]);
}



