#pragma once

#include "vertexBufferObject.h"
#include <SOIL.h>
// #include "shaders.h"

// #define NUMTERRAINSHADERS 3

/****************************************************************************************

Class:		CMultiLayeredHeightmap

Purpose:	Wraps FreeType heightmap loading and rendering, also allowing
			to use multiple layers of textures with transitions between them.

****************************************************************************************/

class CMultiLayeredHeightmap
{
public:
	// static bool LoadTerrainShaderProgram();
	// static void ReleaseTerrainShaderProgram();

	bool LoadHeightMapFromImage(std::string sImagePath);
	void ReleaseHeightmap();

	// void RenderHeightmap();

	void SetRenderSize(float fQuadSize, float fHeight);
	void SetRenderSize(float fRenderX, float fHeight, float fRenderZ);

	int GetNumHeightmapRows();
	int GetNumHeightmapCols();

	// static CShaderProgram* GetShaderProgram();

	CMultiLayeredHeightmap();

	GLuint uiVAO;
	glm::vec3 vRenderScale;
private:

	bool bLoaded;
	bool bShaderProgramLoaded;
	int iRows;
	int iCols;



	CVertexBufferObject vboHeightmapData;
	CVertexBufferObject vboHeightmapIndices;

	// static CShaderProgram spTerrain;
	// static CShader shTerrainShaders[NUMTERRAINSHADERS];
};