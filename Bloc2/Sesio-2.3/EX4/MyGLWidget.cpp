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

void MyGLWidget::initializeGL(){
    BL2GLWidget::initializeGL();
    glEnable(GL_DEPTH_TEST);
    calcul_capsaPatricio();
    calcul_punts();
}

void MyGLWidget::creaBuffers() {
  Patricio.load("./Patricio.obj");

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Patricio);
  glBindVertexArray(VAO_Patricio);

  GLuint VBO_Patricio[2];
  glGenBuffers(2, VBO_Patricio);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Patricio.faces().size()*3*3, Patricio.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Patricio.faces().size()*3*3, Patricio.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glm::vec3 posicio[6] = {
	glm::vec3(2.5, 0, 2.5),
	glm::vec3(2.5, 0, -2.5),
	glm::vec3(-2.5, 0, -2.5),
	glm::vec3(2.5, 0, 2.5),
	glm::vec3(-2.5, 0, -2.5),
	glm::vec3(-2.5, 0, 2.5)
  }; 
  glm::vec3 color[6] = {
	glm::vec3(1,0,0),
	glm::vec3(1,0,0),
	glm::vec3(1,0,0),
    glm::vec3(1,0,0),
    glm::vec3(1,0,0),
    glm::vec3(1,0,0),
  };

  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
} 

void MyGLWidget::carregaShaders() { // declarem-lo també en MyGLWidget.h
    BL2GLWidget::carregaShaders(); // cridem primer al mètode de BL2GLWidget
    projLoc = glGetUniformLocation (program->programId(), "proj");
    viewLoc = glGetUniformLocation (program->programId(), "view");
}

void MyGLWidget::calcul_capsaPatricio() {
  xmin = xmax = Patricio.vertices()[0];
  ymin = ymax = Patricio.vertices()[1];
  zmin = zmax = Patricio.vertices()[2];
  for (unsigned int i = 0; i < Patricio.vertices().size(); i+=3)
  {
    if (Patricio.vertices()[i+0] < xmin)
      xmin = Patricio.vertices()[i+0];
    if (Patricio.vertices()[i+0] > xmax)
      xmax = Patricio.vertices()[i+0];
    if (Patricio.vertices()[i+1] < ymin)
      ymin = Patricio.vertices()[i+1];
    if (Patricio.vertices()[i+1] > ymax)
      ymax = Patricio.vertices()[i+1];
    if (Patricio.vertices()[i+2] < zmin)
      zmin = Patricio.vertices()[i+2];
    if (Patricio.vertices()[i+2] > zmax)
      zmax = Patricio.vertices()[i+2];
  }
}

void MyGLWidget::calcul_punts(){
  xbase_capsa = xcentre_capsa = (xmax+xmin)/2.0;
  ycentre_capsa = (ymax+ymin)/2.0;
  ybase_capsa = ymin;
  zbase_capsa = zcentre_capsa = (zmax+zmin)/2.0;

  R = sqrt((xmax-xcentre_capsa)*(xmax-xcentre_capsa) + (ymax-ycentre_capsa)*(ymax-ycentre_capsa) + (zmax-zcentre_capsa)*(zmax-zcentre_capsa));
  d = 2*R;
  fov = float(2*sin(R/d));
  znear = d-R;
  zfar = d+R;
  rav = 1.0;
  left = bottom = -R;
  right = top = R;
  girPsi = 0.0;
  girTheta = 0.0;
}

void MyGLWidget::resizeGL (int w, int h) 
{
  if(boolprespective) {
    if(float(w)/float(h) < 1) {
      fov = float(2*atan(tan(sin(R/d))/rav));
    }
    rav = float(w)/float(h);

  }
  else {
    if(float(w)/float(h) > 1) {
      left = -(float(w)/float(h)) * R;
      right = (float(w)/float(h)) * R;
      bottom = -R;
      top = R;
    }
    else if(float(w)/float(h) < 1) {
      left = -R;
      right = R;
      bottom = -R/(float(w)/float(h));
      top = R/(float(w)/float(h));

    }
  }
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

/*
void MyGLWidget::modelTransform_Patricio(){
    glm::mat4 transform (1.0f);
    transform = glm::rotate (transform, angleGir, glm::vec3 (0.0, 1.0, 0.0));  
    transform = glm::scale(transform, glm::vec3(4.0/(ymax-ymin)));
    transform = glm::translate(transform, glm::vec3(-xbase_capsa,-ybase_capsa,-zbase_capsa));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}  */

void MyGLWidget::modelTransform_Patricio1(){
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(2,0,2));
    transform = glm::rotate (transform, angleGir, glm::vec3 (0.0, 1.0, 0.0));  
    transform = glm::scale(transform, glm::vec3(1.0/(ymax-ymin)));
    transform = glm::translate(transform, glm::vec3(-xbase_capsa,-ybase_capsa,-zbase_capsa));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform_Patricio2(){
    glm::mat4 transform (1.0f);
    transform = glm::rotate (transform, float(angleGir+M_PI/2), glm::vec3 (0.0, 1.0, 0.0));  
    transform = glm::scale(transform, glm::vec3(1.0/(ymax-ymin)));
    transform = glm::translate(transform, glm::vec3(-xbase_capsa,-ybase_capsa,-zbase_capsa));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);

}

void MyGLWidget::modelTransform_Patricio3(){
    glm::mat4 transform (1.0f);
    transform = glm::translate(transform, glm::vec3(-2,0,-2));
    transform = glm::rotate (transform, float(angleGir+M_PI), glm::vec3 (0.0, 1.0, 0.0));  
    transform = glm::scale(transform, glm::vec3(1.0/(ymax-ymin)));
    transform = glm::translate(transform, glm::vec3(-xbase_capsa,-ybase_capsa,-zbase_capsa));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);

}

void MyGLWidget::modelTransform_Terra(){
    glm::mat4 transform (1.0f);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform() {
    // glm::perspective (FOV en radians, ra window, znear, zfar)
    glm::mat4 Proj(1.0f);
    if(boolprespective) Proj = glm::perspective (fov, rav, znear, zfar);   
    else Proj = glm::ortho (left, right, bottom, top, znear, zfar);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform() {
    // glm::lookAt (OBS, VRP, UP)
    glm::mat4 View(1.0f);
    //View = glm::lookAt (glm::vec3(xobs,yobs,d), glm::vec3(0,2,0), glm::vec3(xup,yup,zup));
    View = glm::translate(View, glm::vec3(0.0, 0.0, -d));
  	View = glm::rotate(View, girTheta, glm::vec3(1.0, 0.0, 0.0));
	  View = glm::rotate(View, -girPsi, glm::vec3(0.0, 1.0, 0.0));    
    View = glm::translate(View, glm::vec3(-0,-2,-0));       //VM= VM*Translate(-VRP.x,-VRP.y,-VRP.z)
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::ini_camera(){
    projectTransform();
    viewTransform();    
}

void MyGLWidget::paintGL() {
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  // Esborrem el frame-buffer juntament amb la profunditat
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ini_camera();
  glBindVertexArray(VAO_Patricio); // Activem el VAO per a pintar el patricio 
  modelTransform_Patricio1();  // Carreguem la transformació de model
  glDrawArrays (GL_TRIANGLES, 0, Patricio.faces().size()*3);
  modelTransform_Patricio2();  // Carreguem la transformació de model
  glDrawArrays (GL_TRIANGLES, 0, Patricio.faces().size()*3);
  modelTransform_Patricio3();  // Carreguem la transformació de model
  glDrawArrays (GL_TRIANGLES, 0, Patricio.faces().size()*3);



  modelTransform_Terra();
  glBindVertexArray(VAO_Terra);
  // pintem
  glDrawArrays (GL_TRIANGLES, 0, 6);

  glBindVertexArray (0);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala -= 0.05;
      break;
    }
    case Qt::Key_R: { 
      angleGir += M_PI/4;
      break;
    }
    case Qt::Key_O: {         //Canviar de prespectiva
      if(boolprespective) boolprespective = 0.0;
      else boolprespective = 1.0;
      break;
    }
    case Qt::Key_Z: {         //Zoom-in
      if(boolprespective) fov -= 0.01;
      else {
        left += 0.05;
        bottom += 0.05;
        right -= 0.05;
        top -= 0.05; 
      }
      break;
    }
    case Qt::Key_X: {         //Zoom-out
      if(boolprespective) fov += 0.01;
      else {
        left -= 0.05;
        bottom -= 0.05;
        right += 0.05;
        top += 0.05;
      }
      break;
    }




    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent (QMouseEvent *e) {
  makeCurrent();
	
	if(e->x() > x_ant) girPsi -= 0.05;
	else if(e->x() < x_ant) girPsi += 0.05;
	
	if(e->y() > y_ant) girTheta += 0.05;
	else if(e->y() < y_ant) girTheta -= 0.05;
	
	x_ant = e->x();
	y_ant = e->y();
	update();
}




