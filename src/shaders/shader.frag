#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

vec2 Flip = TexCoord - 1.0;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, Flip), 0.2);
}