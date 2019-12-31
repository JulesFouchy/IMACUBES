#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;
layout(location = 2) in int materialIndex;
layout(location = 3) in vec3 normal;
layout(location = 4) in vec2 texCoord;
layout(location = 5) in int faceID;

out vec3 vPosInObject;
out vec3 vPosInWorld;
flat out vec3 vNormal;
out vec2 vTexCoord;
flat out int vFaceID;
flat out int vMaterialIndex;

uniform mat4 u_ProjMat;
uniform mat4 u_ViewMat;
uniform vec3 u_CamPosInWorld;
out vec3 vCamPosInWorld;

void main() {
	vPosInObject = vertexPosition;
	vPosInWorld = vertexPosition + cubePosition ; 
	vNormal = normal;
	vTexCoord = texCoord;
	vFaceID = faceID;
	vMaterialIndex = materialIndex;
	vCamPosInWorld = u_CamPosInWorld;
	gl_Position = u_ProjMat * u_ViewMat * vec4(vPosInWorld, 1.0);

}