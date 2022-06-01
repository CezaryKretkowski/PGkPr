#version 330 core
in vec2 textureCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 color;

uniform sampler2D SamplerTexture;
uniform float ambientStrength = 0.1;
uniform vec3 lightColor=vec3(1.0,1.0,1.0);
uniform vec3 lightPos=vec3(0.0,4.0,0.0); 
uniform bool lightSwich;
uniform vec3 viewPos;

void main(){
    
    vec3 norm=normalize(Normals);
    vec3 lightDir=normalize(lightPos-FragPos);
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=diff*lightColor;

    vec3 ambient=ambientStrength*lightColor;
    vec4 material =texture(SamplerTexture,textureCord);   

    vec3 result=vec3(1.0,1.0,1.0);
    result=(ambient+diffuse);
    vec4 finalResult=vec4(1.0,1.0,1.0,1.0);
    if(lightSwich==true){
        finalResult=vec4(result,1.0)*material;
    }
    else
    {
        finalResult=material;
    }
    color=finalResult;
}