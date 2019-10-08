#shader vertex
#version 330 core

layout(location = 0) in vec4 Position; 
uniform float gScale;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * Position;
}


#shader fragment
#version 330 core

out vec4 FragColor; 
in vec2 gl_FragCoord;

uniform vec2 iResolution;
uniform vec3 triColour;
uniform float iTime;

void main()
{
	vec2 uv = gl_FragCoord / iResolution.xy;
	vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0, 2, 4));

	FragColor = vec4(col,1.0);
}