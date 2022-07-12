#version 330 core

in vec3 vertex;
in vec3 normal;

out vec3 sort_normal;    
out vec4 vertexSCO2;
out vec3 sort_matamb;
out vec3 sort_matdiff;
out vec3 sort_matspec;
out float sort_matshin;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocus;
uniform vec3 colorFocus;

// Valors per als components que necessitem del focus de llum
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

void main()
{	
  mat3 NormalMatrix = inverse(transpose(mat3(view * TG))); //te da Normal matrix
  vec3 NormSCO = NormalMatrix * normal;
  sort_normal = NormSCO;

  vec4 vertexSCO = view * TG * vec4 (vertex, 1.0);
  vertexSCO2 = vertexSCO;
  vec4 pfSCO = view * vec4(posFocus,1.0);

  sort_matamb = matamb;
  sort_matdiff = matdiff;
  sort_matspec = matspec;
  sort_matshin = matshin;

  gl_Position = proj * view * TG * vec4 (vertex, 1.0);

}
