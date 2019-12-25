#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;
layout(location = 2) in int materialIndex;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec2 texCoord;
layout(location = 5) in int faceID;

out vec3 vObjectPos;
out vec3 vWorldPos;
flat out vec3 vNormal;
out vec2 vTexCoord;
flat out int vFaceID;
flat out int vMaterialIndex;

uniform mat4 u_projMat;
uniform mat4 u_viewMat;

void main() {
	vObjectPos = vertexPosition;
	vWorldPos = vertexPosition + cubePosition ; 
	vNormal = normal;
	vTexCoord = texCoord;
	vFaceID = faceID;
	vMaterialIndex = materialIndex;
	gl_Position = u_projMat * u_viewMat * vec4(vWorldPos, 1.0);

}