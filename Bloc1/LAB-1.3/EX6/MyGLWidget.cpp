
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat) Con que color tiene que pintar la ventana
  carregaShaders();     
  creaBuffers();                                                                        //
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  modelTransform1();                                                                //
  glViewport (0, 0, ample/2, alt/2);
  // Activem l'Array a pintar 
  glBindVertexArray(VAO1);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(VAO2);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  modelTransform2();   
  glViewport (ample/2, alt/2, ample/2, alt/2);
  // Activem l'Array a pintar
  glBindVertexArray(VAO1);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(VAO2);
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
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

/*Casa
  Vertices[0] = glm::vec3(-0.5, -1.0, 0.0);
  Vertices[1] = glm::vec3(0.5, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.5, 0.0, 0.0);

  Vertices[3] = glm::vec3(-0.5, -1.0, 0.0);
  Vertices[4] = glm::vec3(-0.5, 0.0, 0.0);
  Vertices[5] = glm::vec3(0.5, 0.0, 0.0);

  Vertices[6] =  glm::vec3(-0.5, 0.0, 0.0);
  Vertices[7] = glm::vec3(0.0, 1.0, 0.0);
  Vertices[8] = glm::vec3(0.5, 0.0, 0.0);
*/

void MyGLWidget::creaBuffers ()
{

  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z                  //libreria glm
  Vertices[0] =  glm::vec3(-0.5, 0.0, 0.0);
  Vertices[1] = glm::vec3(0.0, 1.0, 0.0);
  Vertices[2] = glm::vec3(0.5, 0.0, 0.0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar                    //VAO (indentificador)
  glGenVertexArrays(1, &VAO1);                                                      //Creame un VAO
  glBindVertexArray(VAO1);                                                          //Activame el VAO

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);                                                           //Crear un buffer de datos (VBO) asociado al VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);                                              //Activamos al VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);                    //Como tiene que leer los bytes, (de tres en tres),  ULT empieza por la zero, PENULT-Saltame un byte
  glEnableVertexAttribArray(vertexLoc);


  glm::vec3 Vertices1[3];  // Tres vèrtexs amb X, Y i Z                  //libreria glm
  Vertices1[0] =  glm::vec3(-0.5, -0.2, 0.0);
  Vertices1[1] = glm::vec3(0.0, -1.0, 0.0);
  Vertices1[2] = glm::vec3(0.5, -0.2, 0.0);

  glGenVertexArrays(1, &VAO2);                                                      //Creame un VAO
  glBindVertexArray(VAO2);                                                          //Activame el VAO

  // Creació del buffer amb les dades dels vèrtexs
  glGenBuffers(1, &VBO1);                                                           //Crear un buffer de datos (VBO) asociado al VAO
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);                                              //Activamos al VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);                    //Como tiene que leer los bytes, (de tres en tres),  ULT empieza por la zero, PENULT-Saltame un byte
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::keyPressEvent (QKeyEvent *e) {
    makeCurrent ();                                     //Necesario para repintar
    switch ( e->key() ) {
        case Qt::Key_P :
            angle += M_PI/6;
            break;
        default: e->ignore (); // propagar al pare
    }
    update ();                                          //Necesario para repintar
}

void MyGLWidget::modelTransform1() {
    glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
    
    TG = glm::rotate (TG, angle, glm::vec3 (0.0, 0.0, 1.0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransform2() {
    glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
    
    TG = glm::rotate (TG, -angle, glm::vec3 (0.0, 0.0, 1.0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
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
  transLoc = glGetUniformLocation (program->programId(), "TG");

}
