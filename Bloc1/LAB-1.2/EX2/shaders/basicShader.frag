#version 330 core

out vec4 FragColor;

void main() {
    if(gl_FragCoord.x < 354.){
        if(gl_FragCoord.y < 354.)
            FragColor = vec4(1, 1, 0, 1);           //Quadrat groc baix a la esq
        else FragColor = vec4(1, 0, 0, 1);          //Quadrat vermell dalt a la esq
    }
    else {
        if(gl_FragCoord.y > 354.)
            FragColor = vec4(0, 0, 1, 1);           //Quadrat blau dalt a la dre
        else FragColor = vec4(0, 1, 0, 1);          //Quadrat verd baix a la dre
    }
    if(mod(gl_FragCoord.y,30) < 5) discard;
}

