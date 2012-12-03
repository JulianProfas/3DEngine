#include "Logger.h"

Logger* Logger::instance = NULL;

/*	
	Constructor for Logger class.

	@param fileName, this is the name for the logFile, the logger will write to this file.
*/
Logger::Logger(std::string fileName)
{
	logFile = std::ofstream(fileName);
	Write("start logging");
}

/*
	Destructor for Logger class.
*/
Logger::~Logger()
{

}

/*
	@return, returns an instance of the Logger class.
*/
Logger* Logger::GetInstance()
{
	if(instance == NULL)
	{
		instance = new Logger("Engie.log");
	}
	return instance;
}

/*
	Writes a message to the logFile and the terminal.
	@param message, text to be written.
*/
void Logger::Write(std::string message)
{
	char newDate[9]; 
	char newTime[9];
	_strdate(newDate);
	_strtime(newTime);
	std::cout << "<" << newDate << "> <" << newTime << "> " << message << std::endl;
	logFile << "<" << newDate << "> <" << newTime << "> " << message << std::endl;
}