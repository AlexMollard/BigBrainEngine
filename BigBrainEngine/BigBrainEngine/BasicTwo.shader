#shader vertex
#version 330 core

//In from CPU
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 vertexColor;
//layout(location = 2) in vec2 vertexUV;
uniform float gScale;
uniform mat4 MVP;
uniform vec3 colourUniform;
in vec2 texcoord;

//Vertex shader
out vec3 fragmentColor;
out vec2 Texcoord;
void main()
{
	fragmentColor = vertexColor;
	//Texcoord = vertexUV;
	gl_Position = MVP * vec4(Position, 1.0);
}

//Fragment shader
#shader fragment
#version 330 core

uniform sampler2D myTextureSampler;
in vec2 Texcoord;
in vec3 fragmentColor;
out vec4 FragColor;

void main()
{
	//FragColor = texture(myTextureSampler, Texcoord).rgba + vec4(fragmentColor, 1.0);
	//FragColor = texture(myTextureSampler, Texcoord).rgba;
	FragColor = vec4(fragmentColor, 1.0);
	//FragColor = vec4(fragmentColor, 1.0);
}