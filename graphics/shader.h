#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "RenderData.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

inline GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if (vertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else {
		std::cerr << "Failed to open " << vertexFilePath << "." << std::endl;
		getchar();
		return 0;
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}

	GLint result{ GL_FALSE };
	int infoLogLength;

	std::cout << "Compiling shader: " << vertexFilePath << std::endl;
	const char* vertexSrcPtr{ vertexShaderCode.c_str() };
	glShaderSource(vertexShaderID, 1, &vertexSrcPtr, nullptr);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, errorMsg.data());
		std::cout << errorMsg.data() << std::endl;
	}

	std::cout << "Compiling shader: " << fragmentFilePath << std::endl;
	const char* fragmentSrcPtr{ fragmentShaderCode.c_str() };
	glShaderSource(fragmentShaderID, 1, &fragmentSrcPtr, nullptr);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr, errorMsg.data());
		std::cout << errorMsg.data() << std::endl;
	}

	std::cout << "Linking..." << std::endl;
	GLuint programID{ glCreateProgram() };
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, nullptr, errorMsg.data());
		std::cout << errorMsg.data() << std::endl;
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}


//YOUR ONE-STOP GATEWAY TO OPENGL HELL
class Shader {
public:

	Shader() = delete;
	~Shader();

	Shader(const std::string& vertex, const std::string& fragment);

	static Shader fromFile(const std::string& vertexPath, const std::string& fragmentPath);

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&&) = default;
	Shader& operator=(Shader&&) = default;

	//ideally we should never need this
	//auto getProgramID() const noexcept { return programID; }

	void render(const RenderData& renderData) const;

private:
	

	GLuint programID{0};

	GLuint vertexAttribID;
	GLuint uvAttribID;
	GLuint matrixID;
	GLuint textureID{0};

	GLuint vertexBuffer;
	GLuint uvBuffer;
};