#version 400

layout (location = 0) in vec3 vPosition;

uniform mat4 mModelViewProj;
uniform float pointSize;

out vec4 destinationColor;

void main() {
	gl_PointSize = pointSize;
	if(gl_frontFacing){
		destinationColor = vec4(0.0, 1,0, 0.0, 1.0);
	} else {
		destinationColor = vec4(1.0, 0,0, 0.0, 1.0);
	}
	gl_Position = mModelViewProj * vPosition;
}