#version 330 core

//----------------------------------------------------------------------------------------
//----------- All user-defined shaders must give their list of parameters here -----------
//----------------------------------------------------------------------------------------

struct MaterialParameters{
	vec3 color; // default  0 0.5 1
	float borderLength; // default 0.1 min 0 max 0.3
	float borderRampEnd; // default 0.5 min 0 max 0.5
};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

#include "_uniformsAndVaryings.frag"
// Check the above-included file to know all the informations available (including position in World and Object spaces etc.)

//----------------------------------------------------------------------------------------
//----------- All user-defined shaders must fill in the 'albedo' function ----------------
//----------------------------------------------------------------------------------------

float ramp(float d){
	MaterialParameters u_ = params[vMaterialIndex];
	return 1.-smoothstep(u_.borderRampEnd - u_.borderLength,u_.borderRampEnd, d);
}

vec3 albedo(){
	MaterialParameters u_ = params[vMaterialIndex];
	float x = ramp(abs(vObjectPos.x));
	float y = ramp(abs(vObjectPos.y));
	float z = ramp(abs(vObjectPos.z));
	float t = min(min(max(x,y), max(x,z)), max(y,z)) ;
	vec3 color = u_.color * t;
	return color;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

#include "_main.frag"