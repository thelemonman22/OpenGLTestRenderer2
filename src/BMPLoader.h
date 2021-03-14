#pragma once

class BMPLoader {
private:
	unsigned char header[54]; //Each BMP file begins by a 54-byte header
	unsigned int dataPos; //Position in the file where the data actual begins
	unsigned int width, height;
	unsigned int imageSize; // width * height * 3
	unsigned char* data; //Actual RGB data

	unsigned int m_TextureID;
public:
	BMPLoader(const char* imagepath);
	unsigned int getTextureID();

private:
	//Attempts to read file and store in data. Retun 0 if unsuccessful
	bool readFile(const char* imagepath);

};