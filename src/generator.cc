#include "../include/generator.h"

generator::generator(string s1, string s2, string s3, string s4)
{
  sTemplates=s1;
  sTemp=s2;
  sMake=s3;
  sShow=s4;
}

void generator::showAvailableTests(string sPath)
{
  ifstream templatefile;
  templatefile.open(sTemplates+"/templatebase/test");
  if(!templatefile.is_open())
  {
    cout << "can't open templatebase/test";
    throw 0;
  }
  MyDir::dirlist _dirlist = MyDir::getAllSubdirs(sPath);
  ifstream testfile;
  MyDir::dirlist availableTests;
  for(int i=0;i<_dirlist.size();i++)//check all directories for available tests
  {
    testfile.open(sPath+"/"+_dirlist[i]+"/test");
    if(!testfile.is_open())
    {
      cout << "can't open " << _dirlist[i] << endl;
      continue;
    }
    testfile.close();
    availableTests.push_back(sPath+"/"+_dirlist[i]);
  }
  generateTest(availableTests, sTemp+"/testgenerator");

}

void generator::generateTest(generator::dirlist _dirlist, string sSavePath)
{
  string line;
  ofstream generatedtest;
  MyDir::createDir(sSavePath);
  generatedtest.open(sSavePath+"/main.tex", ios::trunc);
  if(!generatedtest.is_open())
  {
    cout << "can't write main.tex" << endl;
    throw 0;
  }
  ifstream templatefile;
  templatefile.open(sTemplates+"/templatebase/test");
  if(!templatefile.is_open())
  {
    cout << "can't open templatebase/test";
    throw 0;
  }

  while(true)//writing generated test until content
  {
    getline(templatefile,line);
    if(line=="#CONTENT")
      break;
    generatedtest << line << endl;
  }
  for(int i=0;i<_dirlist.size();i++)
  {
    ifstream testfile;
    for(int i=0;i<_dirlist.size();i++)
    {
      testfile.open(_dirlist[i]+"/test");
      if(!testfile.is_open())
        cout << "can'r open " << _dirlist[i]<< "/test" << endl;
      while(getline(testfile,line))
        generatedtest << line << endl;
      testfile.close();
    }
  }
  while(getline(templatefile,line))
    generatedtest << line << endl;
  generatedtest.close();

}
