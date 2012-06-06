#ifndef __LIST_H__
#define __LIST_H__

#include <vector>

#include "Pipeline.h"

class List
{
	std::vector<Pipeline*> pipes;

	public:
	List();
	~List();
	Pipeline* addPipeline();
	void execute();
};

#endif //_LIST_H__
