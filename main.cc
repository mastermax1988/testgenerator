#include <iostream>
#include <fstream>
#include <string>
#include "include/dir.h"
using namespace std;

//main program
int main()
{
  fstream cfgfile;
  cfgfile.open("./testgen.cfg");
  if(!cfgfile.is_open())
  {
    cfgfile.open("./testgen.cfg", ios::out);
    cout << "config not found, generating config file testgen.cfg."<<endl<<"Set your templates folder and adjust the other settings" << endl;
    cfgfile << "path/to/templatesfolder" << endl << "/tmp" << endl << "latexmk -f -pdf main.tex" << endl << "evince main.pdf" << endl;
    cfgfile.close();
    return 0;
  }
  string sTemplatesPath, sTempPath, sMake, sShow;
  getline(cfgfile,sTemplatesPath);
  getline(cfgfile,sTempPath);
  getline(cfgfile,sMake);
  getline(cfgfile,sShow);
  MyDir::dirlist _dirlist;
  _dirlist=MyDir::getAllSubdirs(sTemplatesPath);
 
  cout << "available subjects:" << endl;
  for(int i=0;i<_dirlist.size();i++)
  {
    cout << _dirlist[i] << endl;
  }
  string sSubject;
  cout << "select test subject" << endl;
  cin >> sSubject;
 
  _dirlist=MyDir::getAllSubdirs(sTempPath+"/"+sSubject);
 
  cout << "available classes:" << endl;
  for(int i=0;i<_dirlist.size();i++)
  {
    cout << _dirlist[i] << endl;
  }
  string sClass;
  cout << "select class" << endl;
  cin >> sClass;

  return 0;
}

