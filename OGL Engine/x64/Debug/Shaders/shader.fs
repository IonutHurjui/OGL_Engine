#version 450 core

in vec2 TexCoord;
in vec2 TexCoord2;

out vec4 color;
out vec4 color2;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{

	color = texture2D(ourTexture0, TexCoord);
	color2 = texture2D(ourTexture1, TexCoord2);
}
