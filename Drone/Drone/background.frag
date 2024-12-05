#version 330 core

in vec2 chTex; 
out vec4 outCol;

uniform sampler2D uTex; 
uniform bool isMap;
void main()
{
	vec4 tex = texture(uTex, chTex);
	if(isMap){
		tex = mix(tex, vec4(0.0, 1.0, 0.0,	1), 0.1);
	}
	outCol = tex;
}

