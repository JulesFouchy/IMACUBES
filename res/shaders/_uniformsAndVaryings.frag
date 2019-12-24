//? #version 330 core
//? struct MaterialParameters{ float empty; };
// To learn more about these funny comments, see https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

in vec3 vObjectPos; 
in vec3 vWorldPos;
flat in int vMaterialIndex;

uniform MaterialParameters params[16];