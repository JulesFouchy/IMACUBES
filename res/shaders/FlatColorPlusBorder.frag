#version 330 core

//----------------------------------------------------------------------------------------
//----------- All user-defined shaders must give their list of parameters here -----------
//----------------------------------------------------------------------------------------

struct MaterialParameters {
    vec3  color;         // default  0 0.5 1
    vec3  borderColor;   // default  0 0 0
    float borderLength;  // default 0.1 min 0 max 0.3
    float borderRampEnd; // default 0.5 min 0 max 0.5
    float k;             // default 0 min 0 max 2
    float K;             // default 0 min 0 max 6
};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

#include "_geometryPass_uniformsAndVaryings.frag"
// Check the above-included file to know all the informations available (including position in World and Object spaces etc.)

//----------------------------------------------------------------------------------------
//----------- All user-defined shaders must fill in the 'albedo' function ----------------
//----------------------------------------------------------------------------------------

float ramp(float d)
{
    MaterialParameters u_ = params[vMaterialIndex];
    return 1. - smoothstep(u_.borderRampEnd - u_.borderLength, u_.borderRampEnd, d);
}

#include "_smoothMax.frag"
#include "_smoothMin.frag"

vec3 albedo()
{
    MaterialParameters u_    = params[vMaterialIndex];
    float              x     = ramp(abs(vPosInObject.x));
    float              y     = ramp(abs(vPosInObject.y));
    float              z     = ramp(abs(vPosInObject.z));
    float              t     = smin(smin(smax(x, y, u_.K), smax(x, z, u_.K), u_.k), smax(y, z, u_.K), u_.k);
    vec3               color = u_.color * t + u_.borderColor * (1. - t);
    return color;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

#include "_geometryPass_main.frag"