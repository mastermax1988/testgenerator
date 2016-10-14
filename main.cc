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
    cfgfile << "./templates" << endl << "/tmp" << endl << "latexmk -f -pdf main.tex" << endl << "evince main.pdf" << endl;
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
    cout << i+1 << ": " <<_dirlist[i] << endl;
  }
  int iSelect;
  string sSubject;
  cout << "select test subject number" << endl;
  cin >> iSelect;
  sSubject=_dirlist[iSelect-1];
 
  _dirlist=MyDir::getAllSubdirs(sTempPath+"/"+sSubject);
 
  cout << "available classes:" << endl;
  for(int i=0;i<_dirlist.size();i++)
  {
    cout << i+1 << ": " << _dirlist[i] << endl;
  }
  string sClass;
  cout << "select class" << endl;
  cin >> iSelect;
  sClass=_dirlist[iSelect-1];
  return 0;
}

