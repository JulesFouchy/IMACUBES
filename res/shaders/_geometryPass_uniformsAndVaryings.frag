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

struct LightingProperties{
	float Specular_strength;
	float Shininess;
};

//? const int DEFINE_ME_nbOfMaterials = 1;
uniform MaterialParameters params[DEFINE_ME_nbOfMaterials];
uniform LightingProperties lightingProperties[DEFINE_ME_nbOfMaterials];