#version 330 core

in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;
in vec4 fvertexPosition;
in vec3 vertexNormalSCO;
out vec4 FragColor;

uniform mat3 NormalMatrix;
uniform vec3 posFocusSCO;
uniform vec3 colorFocus;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * fmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), fmatshin);
    return (fmatspec * colFocus * shine); 
}

void main()
{
	vec3 fvertexNormalSCO = normalize(vertexNormalSCO);

	vec3 ambient = Ambient();

	vec3 L = normalize(posFocusSCO - fvertexPosition.xyz);
    vec3 difus = Difus(fvertexNormalSCO, L, colorFocus);

    vec3 especular = Especular(fvertexNormalSCO, L, fvertexPosition, colorFocus);

	vec3 fcolor = ambient + difus + especular;
	FragColor = vec4(fcolor, 1.);
}
