#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;

out vec3 vPosInObject;

uniform mat4 u_ProjMat;
uniform mat4 u_ViewMat;

void main()
{
    vPosInObject = vertexPosition;
    gl_Position  = u_ProjMat * u_ViewMat * vec4(vertexPosition + cubePosition, 1.0);
}