#version 330 
in vec3 textureCord;

out vec4 clr;

uniform samplerCube skyBox;

void main(){
    vec4 tx=texture(skyBox,textureCord);
    clr=tx;
}
