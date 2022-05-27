#version 330 core
in vec2 textureCord;

out vec4 color;

uniform sampler2D SamplerTexture;

void main(){
    //vec4 material =texture(SamplerTexture,textureCord);   
    color=vec4(0.8,0.8,0.8,1.0);
}