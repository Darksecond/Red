#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include <vector>
#include <string>

#include "Command.h"

class Pipeline
{
	std::vector<Command*> commands;

	public:
	Pipeline();
	~Pipeline();
	Command* addCommand(std::string word);
	void execute();
};

#endif //_PIPELINE_H__
