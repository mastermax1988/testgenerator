#ifndef gen_hh
#define gen_hh
#include<iostream>
#include<string>
#include<fstream>
#include "command.h"
#include "dir.h"
using namespace std;

class generator
{
  public:
    typedef vector<string> dirlist;
    generator(string, string, string, string); //temppath, make, pdfapp
    ~generator(){}
    void showAvailableTests(string); //basepath
    void generateTestFromSelectionString(string, string, string);//basepath, sel, savedir
  private:
    string sTemplates, sTemp, sMake, sShow;
    void generateTest(dirlist, string); //selected tests, savedirectory
    dirlist getAllTests(string);

};

#endif
