#include <iostream>
#include "template.h"
using namespace std;

/** Command Guide
 * cd <path> - change directory
 * mkdir <name(s)> - create directory/directories in the current folder
 * touch <name(s)> - create file(s) in the current folder
 * rmdir <name(s)> - delete folder(s) (empty) from the current folder
 * rmf <name(s)> - forced deletion of all contents mentioned (to be added)
 * rm - remove a file from the current directory
*/

string clean(string path) {
  string cleaned_path="";
  for(char c:path) {
    if(c!=' ') cleaned_path.push_back(c);
  }
  return cleaned_path;
}

vector<string> extractPredicate(string cmd, int i) {
  vector<string> predicate;
  int n=cmd.length();
  while(i<n) {
    string str="";
    while(i<n && cmd[i]!=' ') {
      str.push_back(cmd[i]);
      i++;
    }
    while(i<n && cmd[i]==' ') i++;
    predicate.push_back(str);
  }
  return predicate;
}

void FileSystem::parseCommand(string cmd) {
  int i=0, n=cmd.length();
  vector<string> predicate; string command="";
  bool status;

  while(i<n && cmd[i]==' ') i++;
  while(i<n && cmd[i]!=' ') {command.push_back(cmd[i]); i++;}
  while(i<n && cmd[i]==' ') i++;
  
  if(command=="cd") {
    predicate.push_back(clean(cmd.substr(i,n-i)));
    changeDirectory(predicate[0], &status);
    if(status) 
      cout<<"Path changed to: "<<predicate[0]<<endl;
    else 
      cout<<"Fatal Error: System could not find the path specified\n";
  } else if(command=="mkdir") {
    createDirectories(extractPredicate(cmd,i));
  } else if(command=="touch") {
    createFiles(extractPredicate(cmd,i));
  } else if(command=="rmdir") {
    deleteDirectories(extractPredicate(cmd,i));
  } else if(command=="rm") {
    deleteFiles(extractPredicate(cmd,i));
  } else if(command=="ls") {
    listDirectory();
  } else cout<<"Error: "<<command<<" is not recognized as a command"<<endl;
}
