#version 440 core

in vec2 vTexCoords;

uniform sampler2D u_TextureSlot;

void main() {
	const vec2 texelSize = 1.0 / textureSize(u_TextureSlot, 0);
    vec2 offsets[9] = vec2[](
        texelSize * vec2(-1, 1), // top-left
        texelSize * vec2( 0, 1), // top-center
        texelSize * vec2( 1, 1), // top-right
        texelSize * vec2(-1, 0),   // center-left
        texelSize * vec2( 0, 0),   // center-center
        texelSize * vec2( 1, 0),   // center-right
        texelSize * vec2(-1,-1), // bottom-left
        texelSize * vec2( 0,-1), // bottom-center
        texelSize * vec2( 1,-1)  // bottom-right    
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