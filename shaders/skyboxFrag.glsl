#version 330 
in vec3 textureCord;

out vec4 clr;

uniform samplerCube skyBox;
uniform float ambientStrength = 0.9;
uniform vec3 lightColor=vec3(1.0,1.0,1.0); 

void main(){
    vec4 tx=texture(skyBox,textureCord);
    vec3 ambient=ambientStrength*lightColor;
    clr=vec4(ambient,1.0)*tx;
}
