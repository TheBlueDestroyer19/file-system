#include <iostream>
#include <string>
#include "template.h"
using namespace std;

int main() {
  cout<<"Welcome to the setup wizard!!\nPlease enter the name of the root folder:\n";
  string name; cin>>name;
  FileSystem file(name);

  while(true) {
    string cmd;
    cout<<file.getPath()<<" $ ";
    getline(cin,cmd);
    if(cmd=="exit") break;
    file.parseCommand(cmd);
  }
}
