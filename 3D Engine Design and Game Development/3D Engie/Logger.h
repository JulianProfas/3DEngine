#ifndef ENGIE_LOGGER_H
#define ENGIE_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

class Logger
{
public:
	Logger(std::string logFile);
	~Logger();
	static Logger* GetInstance();
	void Write(std::string message);
private:
	static Logger* instance;
	std::ofstream logFile;
};


#endif