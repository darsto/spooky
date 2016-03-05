uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

attribute vec2 inPosition;

void main()
{
	gl_Position = projectionMatrix*modelViewMatrix*vec4(inPosition, 0.0, 1.0);
}