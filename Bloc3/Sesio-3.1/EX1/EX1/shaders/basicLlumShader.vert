#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform mat4 posF;
uniform mat4 colF;

// Valors per als components que necessitem del focus de llum
vec3 colorFocus = vec3(0.8, 0.8, 0.8);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocus = vec3(1, 0, 1);  // en SCA

out vec3 fcolor;

vec3 Ambient() {
    return llumAmbient * matamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)        //L es la posicion del foco
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme especular!
    // Assumim que els vectors estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), matshin);
    return (matspec * colFocus * shine); 
}

void main()
{	
    //a,b (vec4) ---- a = b*xyz (a -> vec3)
    //fcolor = matdiff;
    //fcolor = Ambient() * Difus() + Espercular() 
    //vec3 NormSCO()  --> 
    mat3 NormalMatrix = inverse(transpose(mat3(view * TG))); //te da Normal matrix
    vec3 NormSCO = NormalMatrix * normal;
    NormSCO = normalize(NormSCO);
    
    vec4 vertexSCO = view * TG * vec4 (vertex, 1.0);
    vec4 pfSCO = view * vec4(posFocus,1.0);        //tenemos el posFocus en SCO
    vec3 L = normalize((pfSCO-vertexSCO).xyz);
    fcolor = Ambient() + Difus(NormSCO,L,colorFocus) + Especular(NormSCO, L, vertexSCO, colorFocus);
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
