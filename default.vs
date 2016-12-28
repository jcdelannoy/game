#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 ourTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // swap the y-axis since most images have the top y-axis inversed with OpenGL's.
    ourTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}