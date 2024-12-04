#version 330 core

in vec2 chTex; 
out vec4 outCol;

uniform sampler2D uTex; 

void main()
{
	vec4 tex = texture(uTex,chTex);
	if(tex.a < 0.1){
		discard;
	}
	tex.a = 0.4;

	outCol = tex;
}

