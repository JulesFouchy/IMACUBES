//? #version 330 core
//? vec3 albedo() {return vec3(0.);}
// To learn more about these funny comments, see https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

void main() {
	gl_FragColor = vec4(albedo(),1.0);
}