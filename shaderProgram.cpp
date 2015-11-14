// #include <stdio.h>
// #include <string>
// #include <vector>
// #include <iostream>
// #include <fstream>
// #include <algorithm>
// using namespace std;

// #include <stdlib.h>
// #include <string.h>

// #include <GL/glew.h>

#include "shaderProgram.hpp"

ShaderProgram::ShaderProgram() {
	this->vertexShaderID = NULL;
	this->fragmentShaderID = NULL;
	this->geometryShaderID = NULL;

	this->vertexShaderCode = "";
	this->fragmentShaderCode = "";
	this->geometryShaderCode = "";

	this->vertexShaderCompiled = false;
	this->fragmentShaderCompiled = false;
	this->geometryShaderCompiled = false;

	this->programID = NULL;
}

ShaderProgram::ShaderProgram(const char * vertex_file_path, const char * fragment_file_path) {
	this->vertexShaderID = NULL;
	this->fragmentShaderID = NULL;
	this->geometryShaderID = NULL;

	this->vertexShaderCode = "";
	this->fragmentShaderCode = "";
	this->geometryShaderCode = "";

	this->vertexShaderCompiled = false;
	this->fragmentShaderCompiled = false;
	this->geometryShaderCompiled = false;

	this->programID = NULL;

	this->loadShaders(vertex_file_path, fragment_file_path);
	this->linkProgram();
}

ShaderProgram::~ShaderProgram() {
	if (this->vertexShaderID) {
		glDetachShader(this->programID, this->vertexShaderID);
		glDeleteShader(this->vertexShaderID);

	}
	if (this->fragmentShaderID) {
		glDetachShader(this->programID, this->fragmentShaderID);
		glDeleteShader(this->fragmentShaderID);

	}
	if (this->geometryShaderID) {
		glDetachShader(this->programID, this->geometryShaderID);
		glDeleteShader(this->geometryShaderID);
	}
}

void ShaderProgram::loadVertexShader(const char * vertex_file_path) {
	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
	vertexShaderStream.clear();
	vertexShaderStream.seekg(0, ios::beg);
	if(vertexShaderStream.is_open()){
		std::string line = "";
		while(getline(vertexShaderStream, line)) {
			this->vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}else{
		printf("Unable to open file: %s\n", vertex_file_path);
		getchar();
		return;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	printf("Compiling shader : %s\n", vertex_file_path);
	char const * vertexSourcePointer = this->vertexShaderCode.c_str();
	glShaderSource(this->vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(this->vertexShaderID);

	glGetShaderiv(this->vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(this->vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(this->vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	} else {
		printf("Vertex shader compiled successfully\n");
		this->vertexShaderCompiled = true;
	}
}

void ShaderProgram::loadFragmentShader(const char * fragment_file_path) {
	this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
	fragmentShaderStream.clear();
	fragmentShaderStream.seekg(0, ios::beg);

	if(fragmentShaderStream.is_open()){
		std::string line = "";
		while(getline(fragmentShaderStream, line)) {
			this->fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}else{
		printf("Unable to open file: %s\n", fragment_file_path);
		getchar();
		return;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	printf("Compiling shader : %s\n", fragment_file_path);
	char const * fragmentSourcePointer = this->fragmentShaderCode.c_str();
	glShaderSource(this->fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(this->fragmentShaderID);

	glGetShaderiv(this->fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(this->fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(this->fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	} else {
		printf("Fragment shader compiled successfully\n");
		this->fragmentShaderCompiled = true;
	}
}

void ShaderProgram::loadGeometryShader(const char * geometry_file_path) {
	this->geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
	std::ifstream geometryShaderStream(geometry_file_path, std::ios::in);
	if(geometryShaderStream.is_open()){
		std::string line = "";
		while(getline(geometryShaderStream, line)) {
			this->geometryShaderCode += "\n" + line;
		}
		geometryShaderStream.close();
	}else{
		printf("Unable to open file: %s\n", geometry_file_path);
		getchar();
		return;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	printf("Compiling shader : %s\n", geometry_file_path);
	char const * geometrySourcePointer = this->geometryShaderCode.c_str();
	glShaderSource(this->geometryShaderID, 1, &geometrySourcePointer, NULL);
	glCompileShader(this->geometryShaderID);

	glGetShaderiv(this->geometryShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(this->geometryShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> geometryShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(this->geometryShaderID, infoLogLength, NULL, &geometryShaderErrorMessage[0]);
		printf("%s\n", &geometryShaderErrorMessage[0]);
	} else {
		printf("Geometry shader compiled successfully\n");
		this->geometryShaderCompiled = true;
	}
}

void ShaderProgram::loadShaders(const char * vertex_file_path, const char * fragment_file_path) {
	this->loadVertexShader(vertex_file_path);
	this->loadFragmentShader(fragment_file_path);
}

void ShaderProgram::loadShaders(const char * vertex_file_path, const char * fragment_file_path, const char * geometry_file_path) {
	this->loadVertexShader(vertex_file_path);
	this->loadVertexShader(fragment_file_path);
	this->loadGeometryShader(geometry_file_path);
}

void ShaderProgram::linkProgram() {
	printf("Linking program\n");
	this->programID = glCreateProgram();
	if (this->vertexShaderCompiled) {
		glAttachShader(this->programID, this->vertexShaderID);
	}
	if (this->fragmentShaderCompiled) {
		glAttachShader(this->programID, this->fragmentShaderID);
	}
	if (this->geometryShaderCompiled) {
		glAttachShader(this->programID, this->geometryShaderID);
	}

	glLinkProgram(this->programID);

	GLint result = GL_FALSE;
	int infoLogLength;

	glGetProgramiv(this->programID, GL_LINK_STATUS, &result);
	glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(this->programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}
}
