#include"Chunk.h"

Chunk::Chunk(int x, int y)
{

	for (int y = 0; y < 33; y++)
	{
		for (int x = 0; x < 33; x++)
		{
			terrainVertices[(getVert(x, y) * 3) + 0] = x * unit;
			terrainVertices[(getVert(x, y) * 3) + 1] = 0.0f;
			terrainVertices[(getVert(x, y) * 3) + 2] = y * unit;
		}
	}

	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			terrainIndices[(getFace(x, y) * 6) + 0] = getVert(x,y);
			terrainIndices[(getFace(x, y) * 6) + 1] = getVert(x + 1, y);
			terrainIndices[(getFace(x, y) * 6) + 2] = getVert(x, y + 1);
			terrainIndices[(getFace(x, y) * 6) + 3] = getVert(x + 1, y + 1);
			terrainIndices[(getFace(x, y) * 6) + 4] = getVert(x + 1, y);
			terrainIndices[(getFace(x, y) * 6) + 5] = getVert(x, y + 1);
		}
	}


	for (int i = 0; i < (16*33*33); i++)
	{
		currentTerrainData[i] = 0.0f;
	}
	SaveChunk(0, 0, 1, "TerrainHeightData.txt");

	
	Chunk::shader.LoadShader("Terrain.vert", "Terrain.geom", "Terrain.frag");

	VAO.Bind();

	VBO VBO(terrainVertices, sizeof(terrainVertices));
	EBO EBO(terrainIndices, sizeof(terrainIndices));

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	//glUniform1iv(glGetUniformLocation(shader.ID, "heightData"), 65*65*16, currentTerrainData);
	//glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	VBO.Delete();
	EBO.Delete();
}

void Chunk::Draw(Camera& camera)
{
	shader.Activate();
	// Exports the camera Position to the Fragment Shader for specular lighting
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Export the camMatrix to the Vertex Shader of the pyramid
	camera.Matrix(shader, "camMatrix");
	// Binds textures so that they appear in the rendering
	// Bind the VAO so OpenGL knows to use it
	VAO.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(terrainIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

int Chunk::getVert(int x, int y)
{
	return (x + (y * 32));
}
int Chunk::getFace(int x, int y)
{
	return (x + (y * 32));
}

void Chunk::Delete()
{
	shader.Delete();
	VAO.Delete();

}

void Chunk::SaveChunk(int x, int y, int chunk, std::string file)
{
	std::fstream f;

	std::string data;
	std::string line;
	bool found = false;
	long linepos = 0;

	f.open(file);

	while (std::getline(f, line) && !found)
	{
		if (line == "chunk" + std::to_string(x) + "_" + std::to_string(y))
		{
			found = true;
			for (int i = 0; i < (33 * 33); i++)
			{
				//data += std::to_string(v[i]) + " ";
				data += std::to_string(int(currentTerrainData[(chunk * 33 * 33) + i] * 100)) + " ";
			}

			
		}
		linepos += line.length() + 2;
	}
	f.close();
	f.open(file);
	f.seekp(linepos);
	f << data;
	f.close();


	if (!found) {

		f.open(file, std::ios::app);

		for (int i = 0; i < (33 * 33); i++)
		{
			//data += std::to_string(v[i]) + " ";
			data += std::to_string(int(currentTerrainData[(chunk * 33 * 33) + i] * 100)) + " ";
		}

		f << "chunk" + std::to_string(x) + "_" + std::to_string(y) << std::endl;
		f << data << std::endl;

		f.close();
	}
}

void Chunk::LoadChunk(int x, int y, int chunk, std::string file)
{
	std::ifstream f;
	std::string line;
	bool found = false;
	f.open(file);


	if (f.is_open())
	{
		while (std::getline(f, line) && !found)
		{
			if (line == "chunk" + std::to_string(x) + "_" + std::to_string(y)) {
				found = true;
			}
		}
	}
	std::istringstream iss(line);
	for (int i =0; i < (33 * 33);i++)
	{
		int val;
		iss >> val;
		currentTerrainData[(chunk * 33 * 33) + i] = (val / 100.0f);
	}
	f.close();
}