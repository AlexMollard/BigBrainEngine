#shader vertex
#version 330 core

layout(location = 0) in vec4 Position; 
uniform float gScale;

void main()
{
	gl_Position = vec4(gScale * Position.x / 2.0, gScale * Position.y / 2.0, Position.z, 1.0);
}


#shader fragment
#version 330 core

out vec4 FragColor; 
uniform vec3 triColour;

void main()
{
	FragColor = vec4(triColour,1.0);
}