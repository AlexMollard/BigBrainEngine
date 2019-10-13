#shader vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
uniform float gScale;
uniform mat4 MVP;
out vec2 uv;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	uv = vertexUV;
}


#shader fragment
#version 330 core

out vec4 FragColor;
in vec4 gl_FragCoord;
in vec2 uv;

uniform sampler2D myTextureSampler;
uniform vec2 iResolution;
uniform vec3 triColour;
uniform float iTime;

void main()
{
	FragColor = texture(myTextureSampler, uv).rgba;
}