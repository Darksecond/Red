#include "Parser.h"
#include "List.h"

int main(int argc, char * argv[])
{
	//Parser* p = new Parser(&std::cin);
	//p->more();
	//p->parse(new List());
	
	//Command* cmd = new Command("echo");
	//cmd->addArg("hello, world");
	//cmd->addArg("another test");
	//cmd->setInputFd(0);
	//cmd->setOutputFd(1);
	//cmd->execute();

	//while(p->more())
	//{
	//List* p->parse();
	////...execute
	//}
	
	Parser* p = new Parser(&std::cin);
	while(p->more())
	{
		List* list = new List();
		p->parse(list);
		//list->print();
		list->execute();
		//delete list; //SOME ERROR HERE?
	}
	return 0;
}
