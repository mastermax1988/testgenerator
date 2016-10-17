#include "../include/dir.h"
#include "dirent.h"
#include <iostream>
#include <string.h>
#include <algorithm>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
MyDir::dirlist MyDir::getAllSubdirs(string path)
{
  MyDir::dirlist list;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (path.c_str())) != NULL) 
  {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL)
    {
      if((ent->d_type == DT_DIR) && (strcmp(ent->d_name,".")!=0) && (strcmp(ent->d_name,"..")!=0) && (strcmp(ent->d_name,"templatebase")!=0))
        list.push_back(ent->d_name);
    }  
    closedir (dir);
  }
  else
  {
    cout << "err" << endl;
  }
  sort(list.begin(),list.end(),[](string a, string b) { return a < b; });
  return list;
}
MyDir::dirlist MyDir::getAllFiles(string path)
{
  MyDir::filelist list;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (path.c_str())) != NULL) 
  {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL)
    {
      if((ent->d_type != DT_DIR) && (strcmp(ent->d_name,".")!=0) && (strcmp(ent->d_name,"..")!=0) && (strcmp(ent->d_name,"templatebase")!=0))
        list.push_back(ent->d_name);
    }  
    closedir (dir);
  }
  else
  {
    cout << "err" << endl;
  }
  sort(list.begin(),list.end(),[](string a, string b) { return a < b; });
  return list;
}



void MyDir::createDir(string s)
{
  boost::filesystem::path dir(s);
  boost::filesystem::create_directory(dir);
}
bool MyDir::bTestExists(string s)
{
  boost::filesystem::path dir(s+"/main.tex");
  cout << s << "/main.tex" << endl;
  return boost::filesystem::exists(s);
}
void MyDir::copyImages(string source, string dest)
{
  MyDir::createDir(dest);
  MyDir::filelist list=MyDir::getAllFiles(source);
  for(int i=0;i<list.size();i++)
  {

    boost::filesystem::path sdir(source+"/"+list[i]);
    boost::filesystem::path ddir(dest+"/"+list[i]);
    if(boost::filesystem::exists(ddir))
    {
      boost::filesystem::remove(ddir);
      cout << "Warning! Image overwritten!" << endl;
    }
    
    boost::filesystem::copy_file(sdir, ddir);
  }
  
}
