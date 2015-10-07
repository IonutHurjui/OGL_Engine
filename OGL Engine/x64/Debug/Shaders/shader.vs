#version 450 core


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 1) in vec3 color2;
layout (location = 2) in vec2 texCoord2;

out vec2 TexCoord;
out vec2 TexCoord2;

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position =projection * view * model * vec4(position, 1.0f);
	
	TexCoord= vec2(1.0f - texCoord.x, texCoord.y);
	TexCoord2= vec2((1.0f - texCoord2.x)*6, texCoord2.y * 3);
}
