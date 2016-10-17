#ifndef dir_hh
#define dir_hh
#include <string>
#include <vector>

using namespace std;

class MyDir
{
  public:
    typedef vector<string> dirlist;
    typedef vector<string> filelist;
    static dirlist getAllSubdirs(string);
    static void createDir(string);
    static void copyImages(string, string);//sourcedirectory, destdirectory
    static filelist getAllFiles(string);
};

#endif
