#version 330
in vec2 uvTexture;


out vec4 color;

uniform sampler2D text;
uniform float alpha;

void main(){
	vec4 buff=texture(text,uvTexture);
	if(buff.a<0.1)
	    discard;
	color=vec4(buff.r*(1-alpha),buff.g*(1-alpha),buff.b*(1-alpha),buff.a*alpha);
}