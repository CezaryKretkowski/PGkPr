#version 330 core
in vec2 uvTexture;


out vec4 color;

uniform sampler2D text;
uniform float alpha=1.0;

void main(){
	vec4 buff=texture(text,uvTexture);
	if(buff.a<0.1)
	   discard;
	color=vec4(buff.r,buff.g,buff.b,buff.a*alpha);
	//color=vec4(1.0,1.0,1.0,1.0);
}