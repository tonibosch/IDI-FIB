#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

out vec4 FragColor;

const vec3 FocusC = vec3(0.0,0.0,0.0);
uniform vec3 colorC;

const vec3 FocusE = vec3(10.0,3.0,5.0);
uniform vec3 colorE;

uniform vec3 FocusP;
uniform vec3 colorP;

uniform mat4 TG2;



vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
  vec3 NormSCO = normalize(fnormal);

  //Camara
  vec4 posFSCOC = vec4(FocusC,1.0);
  vec3 LC = normalize(posFSCOC.xyz-fvertex);

  //Escena
  vec4 posFSCOE = View * vec4(FocusE,1.0);
  vec3 LE = normalize(posFSCOE.xyz-fvertex);

  //Patricio
  vec4 posFSCOP = View * TG2 * vec4(FocusP,1.0);
  vec3 LP = normalize(posFSCOP.xyz-fvertex);

  vec3 fcolor = Ambient() + Difus(NormSCO, LC, colorC) + Especular(NormSCO, LC, fvertex, colorC);
  fcolor += Difus(NormSCO, LE, colorE) + Especular(NormSCO, LE, fvertex, colorE);
  fcolor += Difus(NormSCO, LP, colorP) + Especular(NormSCO, LP, fvertex, colorP);
  FragColor = vec4(fcolor, 1);
}
