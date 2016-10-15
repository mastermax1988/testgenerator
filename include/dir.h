#ifndef dir_hh
#define dir_hh
#include <string>
#include <vector>

using namespace std;

class MyDir
{
  public:
    typedef vector<string> dirlist;
    static dirlist getAllSubdirs(string);
    static void createDir(string);
};

#endif
