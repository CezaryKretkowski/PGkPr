#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 noramals;
layout (location = 2) in vec2 uvs;

out vec3 textureCord;

uniform mat4 VP;

void main(){
    textureCord=vec3(pos.x,pos.y,-pos.z);
    gl_Position = VP * vec4(pos, 1.0);
}