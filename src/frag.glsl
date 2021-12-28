#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
flat in int Layer;

uniform sampler2DArray texture;

void main()
{
    FragColor = texture(texture, vec3(TexCoord.xy, float(Layer)));
}