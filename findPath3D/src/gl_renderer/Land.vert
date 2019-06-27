uniform float intensity;

varying float _diffuseReflection; //Intensity of reflected light, that will be passed to frag shader

struct lightSource
{
  vec4 direction;
};
lightSource light0 = lightSource( vec4( 0.0, 0.0, 5.0, 0.0) );
 
void main(void) 
{
	vec3 normalDirection = normalize( vec3( gl_NormalMatrix * gl_Normal ) );
	vec3 lightDirection = normalize( vec3( light0.direction) );
	_diffuseReflection = max( 0.0, dot(normalDirection, lightDirection) * intensity );
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 
}