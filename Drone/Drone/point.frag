#version 330 core

in vec2 chTex; 
out vec4 outCol;

uniform sampler2D uTex; 
uniform bool isTurned;

void main()
{
	vec4 tex = texture(uTex, chTex);
	tex = mix(tex, vec4(0.0, 0.0, 0.0,	tex.a), 0.6);
	if(isTurned){
		tex = texture(uTex, chTex);
	}

	outCol = tex;
	
}