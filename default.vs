#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 ourTexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
    ourColor = color;

    // swap the y-axis since most images have the top y-axis inversed with OpenGL's.
    ourTexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}