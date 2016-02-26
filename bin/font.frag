varying vec2 texCoord;

uniform sampler2D gSampler;

uniform vec4 colorMod;

void main()
{
	gl_FragColor = texture2D(gSampler, texCoord) * colorMod;
}