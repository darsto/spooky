#version 120

varying vec2 texCoord;

uniform sampler2D gSampler;

void main()
{
	gl_FragColor = texture2D(gSampler, texCoord);
}