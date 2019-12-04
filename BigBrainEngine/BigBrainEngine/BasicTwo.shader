#shader vertex
#version 330 core

//In from CPU
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;
uniform float gScale;
uniform mat4 MVP;

//Vertex shader
out vec3 fragmentColor;
out vec2 uv;
void main()
{
	fragmentColor = vertexColor;
	uv = vertexUV;
	gl_Position = MVP * vec4(Position, 1.0);
}

//Fragment shader
#shader fragment
#version 330 core

uniform sampler2D myTextureSampler;
in vec2 uv;
in vec3 fragmentColor;
out vec4 FragColor;

void main()
{
	//Tex = texture(myTextureSampler, uv).rgba;
	//FragColor = Tex * fragmentColor;
	//FragColor = texture(myTextureSampler, uv).rgba;
	//FragColor = texture(myTextureSampler, uv).rgba * vec4(FragColor);
	//FragColor = vec4(fragmentColor, 1.0);
	FragColor = vec4(uv.x, uv.y, 0.0, 1.0);

}