//? #version 330 core
//? struct MaterialParameters{ float empty; };
// To learn more about these funny comments, see https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

in vec3 vPosInObject; 
in vec3 vPosInWorld;
flat in vec3 vNormal;
in vec2 vTexCoord;
flat in int vFaceID;
flat in int vMaterialIndex;
in vec3 vCamPosInWorld;

uniform MaterialParameters params[16];