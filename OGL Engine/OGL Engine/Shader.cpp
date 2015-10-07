#include "Shader.h"

using namespace std;


Shader::Shader()
{
	
}


Shader::~Shader()
{
}


void Shader::Use() {
	glUseProgram(this->shaderProgram);
}

void Shader::compileShaders(){

	GLuint _vertexShader, _fragmentShader;

	const char* filePath = "Shaders/shader.vs";
	const char* filePath_2 = "Shaders/shader.fs";

	string vertex = loadShader(filePath);
	string fragment = loadShader(filePath_2);

	GLchar const *vertex_source = vertex.c_str();
	GLchar const *fragment_source = fragment.c_str();

	GLint const vertex_lenght = (GLint)vertex.size();
	GLint const fragment_lenght = (GLint)fragment.size();


	/* CREATE THE SHADERS & ID */
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// COMPILE VERTEX SHADER //
	glShaderSource(_vertexShader, 1, &vertex_source, &vertex_lenght);
	glCompileShader(_vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
		fatalError("SHADER::VERTEX::COMPILATION_FAILED\n");
		std::cout << infoLog << std::endl;
	}


	// COMPILE FRAGMENT SHADER //
	glShaderSource(_fragmentShader, 1, &fragment_source, &fragment_lenght);
	glCompileShader(_fragmentShader);

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(_fragmentShader, 512, NULL, infoLog);
		fatalError("SHADER::FRAGMENT::COMPILATION_FAILED\n");
		std::cout << infoLog << std::endl;
	}


	
	this->shaderProgram = glCreateProgram();
	/* ATTACH VERTEX AND FRAGMENT SHADERS TO PROGRAM ID */
	glAttachShader(this->shaderProgram, _vertexShader);
	glAttachShader(this->shaderProgram, _fragmentShader);
	glLinkProgram(this->shaderProgram);

	/* ERROR CHECKING */
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		fatalError("SHADER LINKING FAILED\n");
		cout << infoLog << endl;
	}

	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);

}

const string Shader::loadShader(const char* filePath) {

	ifstream shaderFile;
	string sourceCode, line,temp;
	temp = filePath;

	shaderFile.exceptions(ifstream::badbit);
	try{	
		shaderFile.open(filePath);
		stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		sourceCode = shaderStream.str();

		shaderFile.close();
	}
	catch(ifstream::failure e){
		fatalError("Failed to open: " + temp);
	}

	return sourceCode;
};
