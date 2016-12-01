#include "../include/generator.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

generator::generator(string s1, string s2, string s3, string s4, string s5, string s6, string s7)
{
  sTemplates=s1;
  sTemp=s2;
  sMake=s3;
  sShow=s4;
  sClass=s5;
  sTestName=s6;
  sTestDate=s7;
}
MyDir::dirlist generator::getAllTests(string sPath)
{
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
  return availableTests;
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
  MyDir::dirlist availableTests=getAllTests(sPath);
  generateTest(availableTests, sTemp+"/testgenerator");
  createNamesTex(sTemp+"/testgenerator",true);
  string s="cd "+sTemp+"/testgenerator;"+ sMake+" "+sTemp+"/testgenerator/main.tex";
  command::exec(s.c_str());
  command::exec((sShow+" "+sTemp+"/testgenerator/main.pdf&").c_str());
}
void generator::generateTestFromSelectionString(string sPath, string sSelect, string sSavePath)
{
  vector<int> iSelectedNumbers;
  vector<string> strs;
  boost::split(strs,sSelect,boost::is_any_of(","));
  for(int i=0;i<strs.size();i++)
    iSelectedNumbers.push_back(boost::lexical_cast<int>(strs[i])-1);
  MyDir::dirlist selectedTests;
  MyDir::dirlist availableTests=getAllTests(sPath);
  for(int i=0;i<iSelectedNumbers.size();i++)
    selectedTests.push_back(availableTests[iSelectedNumbers[i]]);
  generateTest(selectedTests, sSavePath);
  createNamesTex(sSavePath,false);
  string s="cd "+sSavePath+";"+ sMake+" " + "main.tex";
  command::exec(s.c_str());
  command::exec((sShow+" "+sSavePath+"/main.pdf&").c_str());

}

void generator::createNamesTex(string sPath, bool bOverview)
{
  ofstream file(sPath+"/names.tex");
  if(!file.is_open())
  {
    cout << "can't write names.tex" << endl;
    throw 0;
  }
  file << "\\newcommand{\\myclassname}[0]{"<<(bOverview?"":sClass)<<"}" << endl;
  file << "\\newcommand{\\mytitle}[0]{"<<(bOverview?"":sTestName)<<"}" << endl;
  file << "\\newcommand{\\testdate}[0]{"<<(bOverview?"":sTestDate)<<"}" << endl;
  file.close();
}

void generator::createFromOneExercise(string s)
{
  generator::dirlist list;
  list.push_back(s);
  generator::generateTest(list,sTemp+"/testgenerator");
  createNamesTex(sTemp+"/testgenerator",true);
  s="cd "+sTemp+"/testgenerator;"+ sMake+" " + "main.tex";
  command::printoutput(command::exec(s.c_str()));
  command::exec((sShow+" "+sTemp+"/testgenerator/main.pdf&").c_str());
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

  ifstream testfile;
  int iTestNr=1;
  for(int i=0;i<_dirlist.size();i++)
  {
    testfile.open(_dirlist[i]+"/test");
    if(!testfile.is_open())
      cout << "can'r open " << _dirlist[i]<< "/test" << endl;
    vector<string> testcontent;
    while(getline(testfile,line))
      testcontent.push_back(line);
    cout << "testcontent size " << testcontent.size() << endl;
    char cSubtask='a';
    bool bSubtasks=false;
    bool bInMulticol=false;
    int iBE;
    for(int j=1;j<testcontent.size();j++)
      if(testcontent[j][0]=='#')
      {
        bSubtasks=true;
        break;
      }

    for(int j=0;j<testcontent.size();j++)
    {
      if(testcontent[j][0]=='#')
      {
        generatedtest << "\\hline" << endl;
        vector<string> strs;
        boost::split(strs,testcontent[j],boost::is_any_of("#"));
        if(cSubtask=='a')
          generatedtest << iTestNr;
        if(strs.size()>2)
          generatedtest << "&\\multicolumn{2}{p{14cm}|}{" << strs[2] << "}&&\\\\" << endl << "\\hline";
        generatedtest  << "&" << (bSubtasks?cSubtask:' ') << (bSubtasks?")&":"&");
        cout << strs[1] << endl;
        iBE=boost::lexical_cast<int>(strs[1]);
        cSubtask++;
      }
      else
      {
        if((testcontent[j-1][0]!='#'))
          generatedtest << "\\newline ";
        generatedtest  << testcontent[j];
      }
      cout << j << endl;
      if(j+1==testcontent.size() || testcontent[j+1][0]=='#')
      {
        generatedtest << "&" << iBE << "&" << (j+2==testcontent.size()?" ":"\\\\") << endl;
      }
    }
    generatedtest << "\\hline" << endl;
    iTestNr++;
    MyDir::copyImages(_dirlist[i]+"/img",sSavePath+"/img");
    testfile.close();
  }
  while(getline(templatefile,line))
    generatedtest << line << endl;
  generatedtest.close();
  ofstream makefile;
  makefile.open(sSavePath+"/makefile");
  makefile << "#testgenerator" << endl << "new:"<< endl << "\t" <<sMake <<" main.tex" << endl;
}
