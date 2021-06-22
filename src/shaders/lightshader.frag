#version 330 core
uniform vec3 FragOut;
out vec4 Color;

void main()
{
    Color = vec4(FragOut,1.0); // set all 4 vector values to 1.0
}