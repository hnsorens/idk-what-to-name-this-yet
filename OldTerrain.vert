#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTex;


out vec3 Normal;
out vec2 texCoord;

out DATA
{
	vec2 texCoord;
    mat4 projection;
	vec3 currentPos;
} data_out;

uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
	gl_Position = model * vec4(aPos, 1.0f);
	data_out.texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	data_out.projection = camMatrix;
	data_out.currentPos = vec3(model * vec4(aPos, 1.0f));
}