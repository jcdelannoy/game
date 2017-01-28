#version 330 core
layout (location = 0) in vec4 vertex; // vec2 position : vec2 texture coordinates
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	TexCoords = vertex.zw;
	gl_Position = projection * model * vec4(vertex.x, vertex.y, 0.0f, 1.0f);
}
