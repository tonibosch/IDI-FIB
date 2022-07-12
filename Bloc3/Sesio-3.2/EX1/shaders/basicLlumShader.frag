#version 330 core

in vec3 sort_normal;
in vec4 vertexSCO2;
in vec3 sort_matamb;
in vec3 sort_matdiff;
in vec3 sort_matspec;
in float sort_matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocus;
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
uniform vec3 colorFocus;

out vec4 FragColor;

vec3 Ambient() {
    return llumAmbient * sort_matamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)        //L es la posicion del foco
{
    // Fixeu-vos que SOLS es retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * sort_matdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Fixeu-vos que SOLS es retorna el terme especular!
    // Assumim que els vectors estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (sort_matshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), sort_matshin);
    return (sort_matspec * colFocus * shine); 
}

void main()
{	
    vec3 NormSCO = normalize(sort_normal);
    
    vec4 pfSCO = view * vec4(posFocus,1.0);        //tenemos el posFocus en SCO
	  vec3 L = pfSCO.xyz-vertexSCO2.xyz;
    L = normalize(L);
    
    vec3 fcolor = Ambient() + Difus(NormSCO,L,colorFocus) + Especular(NormSCO, L, vertexSCO2, colorFocus);
	FragColor = vec4(fcolor,1);	
}
