#version 150 core

in vec3 position;
in vec2 texcoord;

//out vec3 Color;
out vec2 Texcoord;

uniform mat4 mvp;

void main()
{
    //Color = color;
    Texcoord = texcoord;
    gl_Position = mvp * vec4(position, 1.0);
}