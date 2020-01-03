#version 330 core

out float FragColor;
 
in vec2 vTexCoords; 
  
uniform sampler2D u_TextureSlot; 

void main() {
    vec2 texelSize = 1.0 / vec2(textureSize(u_TextureSlot, 0));
    float color = 0.0;
    for (int x = -2; x < 2; ++x) 
    {
        for (int y = -2; y < 2; ++y) 
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            color += texture(u_TextureSlot, vTexCoords + offset).r;
        }
    }
    FragColor = color / 16.0;
}  