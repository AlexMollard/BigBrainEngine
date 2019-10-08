#shader vertex
#version 330 core

layout(location = 0) in vec3 Position;
uniform float gScale;
uniform mat4 MVP;
out vec2 uv;

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor;
in vec2 gl_FragCoord;
in vec2 uv;

uniform vec2 iResolution;
uniform vec3 triColour;
uniform float iTime;

void main()
{
	FragColor = vec4(1.0, 2.0, 0.0, 1.0);
}