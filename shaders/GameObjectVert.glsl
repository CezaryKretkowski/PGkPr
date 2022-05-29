#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normals;


out vec2 textureCord;
out vec3 Normals;
out vec3 FragPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(){
    textureCord=uvs;
    gl_Position = P*V*M * vec4(pos, 1.0);
    Normals=normals;
    FragPos=vec3(M*vec4(pos,1.0));
}