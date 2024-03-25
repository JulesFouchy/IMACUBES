#version 330 core

in vec3  vPosInObject;
out vec4 fColor;

void main()
{
    vec3  color;
    float nbBands = 2;
    float t       = vPosInObject.x + vPosInObject.y + vPosInObject.z + 1.5;
    t *= nbBands;
    if (mod(t, 1.) < 0.5)
        color = vec3(0.2);
    else
        color = vec3(0.8);
    fColor = vec4(color, 1.0);
}