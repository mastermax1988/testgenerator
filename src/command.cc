#include "../include/command.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <thread>
using namespace std;
using namespace boost;

void command::threadexec(const char* cmd)
{
  thread t ( exec, cmd);

  this_thread::sleep_for(chrono::seconds(2)); //make sure evince opens
  t.detach();
}

command::cmd_return_type command::exec(const char* cmd)
{
	FILE* pipe = popen(cmd, "r");
	if (!pipe) throw NULL;
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);


	cmd_return_type SplitVec;
	split( SplitVec, result, is_any_of("\n") );
	SplitVec.erase(SplitVec.begin() + SplitVec.size() - 1);
	return SplitVec;
}

void command::printoutput(cmd_return_type output)
{
	for(uint i = 0; i < output.size(); i++)
		cout << output[i] << endl;
}
