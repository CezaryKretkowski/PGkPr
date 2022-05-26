#version 330
in vec2 textureCord;

out vec4 color;

uniform sampler2D SamplerTexture;

void main(){
    color=texture(SamplerTexture,textureCord);   
}