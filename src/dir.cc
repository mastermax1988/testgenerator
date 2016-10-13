#include "../include/dir.h"
#include "dirent.h"
#include <iostream>
#include <string.h>
#include <algorithm>
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
      if((ent->d_type == DT_DIR) && (strcmp(ent->d_name,".")!=0) && (strcmp(ent->d_name,"..")!=0))
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


