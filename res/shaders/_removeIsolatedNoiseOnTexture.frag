#version 440 core

in vec2 vTexCoords;

uniform sampler2D u_TextureSlot;

uniform float inverseOffset;

void main() {
	const float offset = 1.0 / inverseOffset; 
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0),   // center-left
        vec2( 0.0,    0.0),   // center-center
        vec2( offset,  0.0),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    int count[6] = int[](0,0,0,0,0,0);
    vec3 possibleNormals[6] = vec3[](
        vec3(-1,0,0),
        vec3(1,0,0),
        vec3(0,-1,0),
        vec3(0,1,0),
        vec3(0,0,-1),
        vec3(0,0,1)
    );

    int maxCount = 0;
    int predominantNormalIndex = -1;

    for(int k = 0; k < 9; k++){
        for(int i = 0; i < 6; ++i){
            if(distance(possibleNormals[i], texture(u_TextureSlot, vTexCoords+offsets[k]).rgb) < 0.5){
                count[i] += 1;
            }
            if(count[i] > maxCount){
                maxCount = count[i];
                predominantNormalIndex = i;
            }
        }
    }

    vec3 color = possibleNormals[predominantNormalIndex];
	gl_FragColor = vec4(color, texture(u_TextureSlot, vTexCoords).a);
}