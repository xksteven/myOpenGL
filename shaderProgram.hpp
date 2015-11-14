#ifndef _SHADER_PROGRAM_
#define _SHADER_PROGRAM_

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

using namespace std;

class ShaderProgram {
	public:
		ShaderProgram();
		ShaderProgram(const char * vertex_file_path, const char * fragment_file_path);
		virtual ~ShaderProgram();
		void loadVertexShader(const char * vertex_file_path);
		void loadFragmentShader(const char * fragment_file_path);
		void loadGeometryShader(const char * geometry_file_path);
		void loadShaders(const char * vertex_file_path, const char * fragment_file_path);
		void loadShaders(const char * vertex_file_path, const char * fragment_file_path, const char * geometry_file_path);
		void linkProgram();

	// protected:
		std::string vertexShaderCode;
		std::string fragmentShaderCode;
		std::string geometryShaderCode;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;
		GLuint geometryShaderID;
		GLuint programID;
		bool vertexShaderCompiled;
		bool fragmentShaderCompiled;
		bool geometryShaderCompiled;
};

#endif //!_SHADER_PROGRAM_
