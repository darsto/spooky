uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform float texPosX;
uniform float texPosY;

attribute vec2 inPosition;
attribute vec2 inCoord;

varying vec2 texCoord;

void main()
{
	gl_Position = projectionMatrix*modelViewMatrix*vec4(inPosition, 0.0, 1.0);
	texCoord = vec2( inCoord.x + texPosX, inCoord.y + texPosY );
}