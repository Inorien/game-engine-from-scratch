#include "shader.h"
#include "camera.h"


Shader::~Shader() {
	glDeleteProgram(programID);
}

Shader::Shader(const std::string& vertex, const std::string& fragment) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint result{ GL_FALSE };
	int infoLogLength;

	std::cout << "Compiling shaders" << std::endl;
	const char* vertexSrcPtr{ vertex.c_str() };
	glShaderSource(vertexShaderID, 1, &vertexSrcPtr, nullptr);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, errorMsg.data());
		std::cout << errorMsg.data() << std::endl;
	}

	const char* fragmentSrcPtr{ fragment.c_str() };
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
	programID = glCreateProgram();
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


	glUseProgram(programID);

	vertexAttribID = glGetUniformLocation(programID, "vertex");
	uvAttribID = glGetUniformLocation(programID, "uv");
	matrixID = glGetUniformLocation(programID, "matrix");
	textureID = glGetUniformLocation(programID, "texSampler");

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &uvBuffer);

}

Shader Shader::fromFile(const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexPath, std::ios::in);
	if (vertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentPath, std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}

	return { vertexShaderCode, fragmentShaderCode };
}

void Shader::render(const RenderData& renderData) const {
	if (renderData.vertices.empty()) {
		return; //nothing to do!
	}

	glUseProgram(programID);

	const auto mvp{ camera->getProjection() * camera->getView() * renderData.matrix };

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderData.texture);
	glUniform1i(textureID, 0);

	auto* const vertexData{ const_cast<float*>(renderData.vertices.data()) };
	auto* const uvData{ const_cast<float*>(renderData.uvCoords.data()) };

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, renderData.vertices.size() * sizeof(float), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, renderData.uvCoords.size() * sizeof(float), uvData, GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr);

	glDrawElements(GL_TRIANGLES, renderData.indices.size(), GL_UNSIGNED_INT, renderData.indices.data());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
