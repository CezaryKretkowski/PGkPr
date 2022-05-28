#version 330 core
in vec2 textureCord;

out vec4 color;

uniform sampler2D SamplerTexture;
uniform float ambientStrength = 0.1;
uniform vec3 lightColor=vec3(1.0,1.0,1.0); 

void main(){
    
    vec3 ambient=ambientStrength*lightColor;
    vec4 material =texture(SamplerTexture,textureCord);   
    color=vec4(ambient*material.xyz,1.0);
}