#pragma once
#ifndef IOMANAGER_H
#define IOMANAGER_H


#include <vector>
#include <fstream>


class IOManager	{

public:
	static bool realFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

};


#endif