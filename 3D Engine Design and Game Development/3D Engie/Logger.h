#ifndef ENGIE_LOGGER_H
#define ENGIE_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

class Logger
{
public:
	static Logger* GetInstance();
	void Write(std::string message);
private:
	Logger(std::string logFile);
	~Logger();
	static Logger* instance;
	std::ofstream logFile;
};


#endif