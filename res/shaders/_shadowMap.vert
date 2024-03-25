#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;

uniform mat4 u_LightVPMatrix;

void main()
{
    gl_Position = u_LightVPMatrix * vec4(vertexPosition + cubePosition, 1.0);
}