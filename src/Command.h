#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <vector>
#include <string>

class Command
{
	std::string name;
	std::vector<std::string> args;
	std::string input;
	std::string output;
	std::string append;
	int fd[2];

	void prepareFd();

	public:
	Command(std::string word);
	~Command();
	void execute();
	void addArg(std::string word);
	void addInput(std::string word);
	void addOutput(std::string word);
	void addAppend(std::string word);
	void setInputFd(int input);
	void setOutputFd(int output);
	bool isExit();
};

#endif //_COMMAND_H__
