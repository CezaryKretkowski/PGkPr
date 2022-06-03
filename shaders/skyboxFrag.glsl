#version 330 
in vec3 textureCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 clr;

uniform samplerCube skyBox;
uniform float ambientStrength = 0.9;
uniform vec3 lightColor=vec3(1.0,1.0,1.0); 
uniform vec3 lightPos=vec3(0.0,4.0,0.0); 
uniform bool lightSwich;
uniform vec3 viewPos;
uniform float specluarStreinght;
uniform int specluarArea;

void main(){
    vec4 tx=texture(skyBox,textureCord);
    vec3 ambient=ambientStrength*lightColor;
    
    vec3 norm=normalize(Normals);
    vec3 lightDir=normalize(lightPos-FragPos);
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=diff*lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specluarArea);
    vec3 specular = specluarStreinght * spec * lightColor;  



    vec3 result=vec3(1.0,1.0,1.0);
    result=(ambient+diffuse+specular);
    vec4 finalResult=vec4(1.0,1.0,1.0,1.0);
    if(lightSwich)
        finalResult=vec4(result,1.0)*tx;
    else
        finalResult=tx;

    clr=finalResult;
}
