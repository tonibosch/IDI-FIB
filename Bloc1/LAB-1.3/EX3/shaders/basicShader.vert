#version 330 core

in vec3 vertex;    
uniform float val;  
uniform mat4 TG;               

void main()  {
    //gl_Position = vec4 (vertex*val, 1.0);     
    gl_Position = TG * vec4 (vertex*val, 1.0);              
}
