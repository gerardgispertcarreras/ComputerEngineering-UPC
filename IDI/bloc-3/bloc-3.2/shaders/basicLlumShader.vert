#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;
uniform mat3 NormalMatrix;
uniform vec3 posFocusSCO;
uniform vec3 colorFocus;

// Valors per als components que necessitem del focus de llum

out vec3 fmatamb;
out vec3 fmatdiff;
out vec3 fmatspec;
out float fmatshin;
out vec4 fvertexPosition;
out vec3 vertexNormalSCO;

void main()
{	
	fmatamb = matamb;
	fmatdiff = matdiff;
	fmatspec = matspec;
	fmatshin = matshin;

	fvertexPosition = view * TG * vec4(vertex, 1.0);
    vertexNormalSCO = NormalMatrix * normal;

    gl_Position = proj * fvertexPosition;
}
