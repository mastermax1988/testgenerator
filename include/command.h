#include <boost/algorithm/string.hpp>
#include <vector>

namespace command
{
	typedef std::vector<std::string> cmd_return_type;
	///executes command and return console output
	cmd_return_type exec(const char* cmd);
  void threadexec(const char* cmd);
	void printoutput(cmd_return_type output);
};

