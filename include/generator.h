#ifndef gen_hh
#define gen_hh
#include<iostream>
#include<string>
#include<fstream>
#include "command.h"
using namespace std;

class generator
{
  public:
    typedef vector<string> dirlist;
    generator(string, string, string); //temppath, make, pdfapp
    ~generator(){}
    void showAvailableTests(string); //basepath
    void generateTest(dirlist, string); //selected tests, savedirectory
  private:
    string sTemp, sMake, sShow;

};

#endif
