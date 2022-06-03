#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 noramals;
layout (location = 2) in vec2 uvs;

out vec3 textureCord;
out vec3 Normals;
out vec3 FragPos;

uniform mat4 VP;
uniform mat4 M;
void main(){
    textureCord=vec3(pos.x,pos.y,-pos.z);
    gl_Position = VP * vec4(pos, 1.0);
    Normals=mat3(transpose(inverse(M))) *  noramals;
    FragPos=vec3(M*vec4(pos,1.0));
}