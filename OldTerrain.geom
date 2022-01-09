#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 256) out;

out vec3 Normal;
out vec2 texCoord;
out vec3 crntPos;

in DATA
{
	vec2 texCoord;
    mat4 projection;
    vec3 currentPos;
} data_in[];


uniform float terrainHeight[25];


// Default main function
void main()
{
    int width = 4;
    int height = 4;
    float unit = 1.0f;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            
            gl_Position = data_in[0].projection * (gl_in[0].gl_Position + vec4(float(x*unit), terrainHeight[x + ((y+1) * 5)], float(y*unit),0.0f));
            Normal = -cross(normalize(vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position)), normalize(vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position)));
            texCoord = data_in[0].texCoord;
            crntPos = data_in[0].currentPos + vec3(float(x*unit), 0.0f, float(y*unit));
            EmitVertex();

            
            gl_Position = data_in[1].projection * (gl_in[1].gl_Position + vec4(float(x*unit), terrainHeight[x + (y * 5)], float(y*unit),0.0f));
            Normal = -cross(normalize(vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position)), normalize(vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position)));
            texCoord = data_in[1].texCoord;
            crntPos = data_in[1].currentPos + vec3(float(x*unit), 0.0f, float(y*unit));
            EmitVertex();

            
            gl_Position = data_in[2].projection * (gl_in[2].gl_Position + vec4(float(x*unit), terrainHeight[x + 1 + (y * 5)], float(y*unit),0.0f));
            Normal = -cross(normalize(vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position)), normalize(vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position)));
            texCoord = data_in[2].texCoord;
            crntPos = data_in[2].currentPos + vec3(float(x*unit), 0.0f, float(y*unit));
            EmitVertex();

            EndPrimitive(); 
            
            
            gl_Position = data_in[1].projection * (gl_in[1].gl_Position + vec4(float(x*unit), terrainHeight[x + 1 + ((y+1) * 5)], float(y*unit),0.0f) + vec4(unit, 0.0f, unit, 0.0f));
            Normal = -cross(normalize(vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position)), normalize(vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position)));
            texCoord = data_in[1].texCoord;
            crntPos = data_in[1].currentPos + vec3(float(x*unit), 0.0f, float(y*unit)) + vec3(unit, 0.0f, unit);
            EmitVertex();

            
            gl_Position = data_in[0].projection * (gl_in[0].gl_Position + vec4(float(x*unit), terrainHeight[x + ((y+1) * 5)], float(y*unit),0.0f));
            Normal = -cross(normalize(vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position)), normalize(vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position)));
            texCoord = data_in[0].texCoord;
            crntPos = data_in[0].currentPos + vec3(float(x*unit), 0.0f, float(y*unit));
            EmitVertex();

            
            gl_Position = data_in[2].projection * (gl_in[2].gl_Position + vec4(float(x*unit), terrainHeight[x + 1 + (y * 5)], float(y*unit),0.0f));
            Normal = -cross(normalize(vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position)), normalize(vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position)));
            texCoord = data_in[2].texCoord;
            crntPos = data_in[2].currentPos + vec3(float(x*unit), 0.0f, float(y*unit));
            EmitVertex();

            EndPrimitive();
        }
    }
 
}