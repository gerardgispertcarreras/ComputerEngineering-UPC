#version 330 core

in vec3 vertex;
in vec3 color;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform vec3 filtre;

out vec3 fcolor;

void main() {
	if(filtre == vec3(0.,0.7,0.))
		fcolor = filtre;
	else
    	fcolor = color*filtre;
    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
