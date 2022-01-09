#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<ios>
#include <istream>
#include <sstream>
#include <fstream>
#include <limits>

#include "shaderClass.h"
#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "Camera.h"
#include "VariableSaver.h"


class Chunk
{
public:
	Chunk(int x, int y);

	float unit = 0.1f;

	Shader shader;

	VAO VAO;

	GLfloat terrainVertices[33*33*3];
	GLuint terrainIndices[32*32*3*2];

	GLfloat currentTerrainData[16 * 33 * 33];

	void Draw(Camera& camera);

	int getVert(int x, int y);
	int getFace(int x, int y);

	void SaveChunk(int x, int y, int chunk, std::string file);

	void LoadChunk(int x, int y, int chunk, std::string file);

	void Delete();
	std::fstream& GotoLine(std::fstream& file, unsigned int num);

	
};

#endif
