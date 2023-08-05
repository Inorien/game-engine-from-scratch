#include "texture.h"

#include <cstdio>
#include <exception>
#include <string>

GLuint loadBMP(const char* path) {
	auto* file { fopen(path, "rb") };
	if (!file) {
		const auto message{"Failed to read file at :" + std::string(path)};
		throw std::exception{message.c_str()};
	}
	
	unsigned char header[54];
	if (fread(header, 1, 54, file) != 54) {
		const auto message{ "File is invalid or corrupted: " + std::string(path)};
		throw std::exception{message.c_str()};
	}
	if (header[0] != 'B' || header[1] != 'M') {
		const auto message{ "File is invalid or corrupted: " + std::string(path) };
		throw std::exception{message.c_str()};
	}

	auto bits{ *reinterpret_cast<int*>(&header[0x1C]) };
	if (bits != 24) {
		const auto message{ "File is not a 24bit BMP: " + std::string(path)
			+ " is " + std::to_string(bits) + "bit"};
		throw std::exception{message.c_str()};
	}

	auto size   { *reinterpret_cast<int*>(&header[0x22]) };
	const auto width  { *reinterpret_cast<int*>(&header[0x12]) };
	const auto height { *reinterpret_cast<int*>(&header[0x16]) };

	if (size == 0)    size = width * height * 3;

	auto* data{ new unsigned char[size] };
	fread(data, 1, size, file);
	fclose(file);


	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}
