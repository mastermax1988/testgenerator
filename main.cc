#include <iostream>
#include <fstream>
#include <string>
#include "include/dir.h"
#include "include/generator.h"

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
    cfgfile << "./templates" << endl << "/tmp" << endl << "/tmp/savedtests" << endl<< "latexmk -f -pdf" << endl << "evince" << endl;
    cfgfile.close();
    return 0;
  }
  string sTemplatesPath, sTempPath, sMake, sShow, sSaveBasePath;
  getline(cfgfile,sTemplatesPath);
  getline(cfgfile,sTempPath);
  getline(cfgfile,sSaveBasePath);
  MyDir::createDir(sSaveBasePath);
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
 
  _dirlist=MyDir::getAllSubdirs(sTemplatesPath+"/"+sSubject);
 
  cout << "available classes:" << endl;
  for(int i=0;i<_dirlist.size();i++)
  {
    cout << i+1 << ": " << _dirlist[i] << endl;
  }
  string sClass;
  cout << "select class" << endl;
  cin >> iSelect;
  sClass=_dirlist[iSelect-1];

  _dirlist=MyDir::getAllSubdirs(sTemplatesPath+"/"+sSubject+"/"+sClass);
  
  string sCName, sTitle, sDate;
  cin.ignore (numeric_limits<std::streamsize>::max(), '\n');//flush for getline 
  cout << "Enter class name, e.g. Klasse 5a" << endl;
  getline(cin,sCName);
  
  cout << "Enter test title, e.g. 1. Schulaufgabe" << endl;
  getline(cin,sTitle);
  
  cout << "Enter test date" << endl;
  getline(cin,sDate);

  generator *gen=new generator(sTemplatesPath,sTempPath, sMake, sShow,sCName,sTitle, sDate);
  string sBasePath=sTemplatesPath+"/"+sSubject+"/"+sClass;
  gen->showAvailableTests(sBasePath);
  string sSelectedTestNumbers;
  cout << "Enter test numbers to generate new test, seperated my colon"<<endl;
  cin >> sSelectedTestNumbers;
  string sPath;
  cout << "enter save path: " + sSaveBasePath+"/" << endl;
  cin >> sPath;
  while(MyDir::bTestExists(sSaveBasePath + "/" + sPath))
  {
    cout << sSaveBasePath << "/main.tex exists!" << endl;
    cin >> sPath;
  }
  sPath=sSaveBasePath+"/"+sPath;
  gen->generateTestFromSelectionString(sBasePath, sSelectedTestNumbers, sPath);
  return 0;
}

