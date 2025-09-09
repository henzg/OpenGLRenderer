#version 330 corecube
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float TextureMix;

void main()
{
    vec4 TextureColor1 = texture(texture1, texCoord);
    vec4 TextureColor2 = texture(texture2, texCoord);
    FragColor = mix(TextureColor1, TextureColor2, TextureMix);
}
