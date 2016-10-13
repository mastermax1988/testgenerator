#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//main program
int main()
{
 fstream cfgfile;
 cfgfile.open("./testgen.cfg");
 if(!cfgfile.is_open())
 {
    cfgfile.open("./testgen.cfg", ios::out);
    cout << "config not found, generating config file testgen.cfg. Set your preferences." << endl;
    cfgfile << "path/to/templates" << endl << "/path/for/temp/files" << endl;
    cfgfile.close();
    return 0;
 }
 string sTemplatesPath, sTempPath;
 getline(cfgfile,sTemplatesPath);
 getline(cfgfile,sTempPath);

 cout << sTemplatesPath << endl;
 return 0;
}

