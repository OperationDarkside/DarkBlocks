#version 150 core

//in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texMine;

void main()
{
    outColor = mix(texture(texKitten, Texcoord), texture(texMine, Texcoord), 0.5);
}