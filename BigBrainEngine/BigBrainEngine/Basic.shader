#shader vertex
#version 330 core

layout(location = 0) in vec3 Position; 
layout(location = 1) in vec3 vertexColor;
uniform float gScale;
uniform mat4 MVP;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;
out vec2 uv;
out vec3 fragmentColor;
void main()
{
	Texcoord = texcoord;
	fragmentColor = vertexColor;
	gl_Position = MVP * vec4(Position, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor; 
in vec4 gl_FragCoord;
in vec2 uv;
in vec3 fragmentColor;
uniform vec2 iResolution;
uniform vec3 triColour;
uniform float iTime;
out vec3 color;
void main()
{
	//vec2 uv = gl_FragCoord / iResolution.xy;
	//vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0, 2, 4));

	FragColor = vec4(fragmentColor, 1.0);
}