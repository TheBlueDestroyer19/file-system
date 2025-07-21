#include <iostream>
#include <stack>
#include <string>
#include "template.h"

bool validate(string name) {
  for(int i=0;i<name.length();i++) 
    if(name[i]==' ' || name[i]=='$' || name[i]=='%') return false;
  return true;
}

void FileSystem::changeDirectory(string path, bool* status) {
  string folder="", oripath=pathName; 
  Folder* original=currentPath;
  *status=true;

  for(int i=0;i<path.length() && *status;i++) {
    if(path[i]!='/')
      folder.push_back(path[i]);
    else {
      if(folder=="..") {
        if(currentPath->parent==nullptr) *status=false;
        else {
          currentPath=currentPath->parent;
          int n=pathName.length();
          while(pathName[n-1]!='/') {
            pathName.pop_back();
            n=pathName.length();
          }
          pathName.pop_back();
        }
      }
      else if(folder=="~") {
        currentPath=root;
        pathName=name;
      }
      else if(currentPath->children[folder]!=nullptr) {
        currentPath=currentPath->children[folder];
        pathName=pathName+'/'+folder;
      }
      else if(currentPath->children[folder]==nullptr)
        *status=false;

      folder="";
    }    
  }
  if(folder!="" && *status) {
      if(folder=="..") {
        if(currentPath->parent==nullptr) *status=false;
        else {
          currentPath=currentPath->parent;
          int n=pathName.length();
          while(pathName[n-1]!='/') {
            pathName.pop_back();
            n=pathName.length();
          }
          pathName.pop_back();
        }
      }
      else if(folder=="~") {
        currentPath=root;
        pathName=name;
      }
      else if(currentPath->children[folder]!=nullptr) {
        currentPath=currentPath->children[folder];
        pathName=pathName+'/'+folder;
      }
      else if(currentPath->children[folder]==nullptr)
        *status=false;
    }
  if(*status==false) {
    currentPath=original;
    pathName=oripath;
  }
  
}

void FileSystem::createDirectories(vector<string> names) {
  stack<string> invalids;

  for(int i=0;i<names.size();i++) {
    string name=names[i];
    bool isValidName=validate(name);
    if(!isValidName) invalids.push(name);
    else {
      currentPath->children[name]=new Folder;
      (currentPath->children[name])->parent=currentPath;
    }
  }

  while(!invalids.empty()) {
    cout<<"ValidationError: "<<invalids.top()<<" - Name not valid. Please enter a valid name";
    invalids.pop();
  }
}

void FileSystem::createFiles(vector<string> names) {
  stack<string> invalids;

  for(int i=0;i<names.size();i++) {
    string name=names[i];
    bool isValidName=validate(name);
    if(!isValidName) invalids.push(name);
    else {
      currentPath->files[name]=true;
    }
  }

  while(!invalids.empty()) {
    cout<<"ValidationError: "<<invalids.top()<<" - Name not valid. Please enter a valid name";
    invalids.pop();
  }
}

void FileSystem::deleteDirectory(Folder* curr) {
  if(curr) {
    for(auto& pair: curr->children)
      deleteDirectory(pair.second);
    for(auto& pair: curr->files)
      pair.second=false;

    curr->parent=nullptr;
    delete curr;
  }
}

void FileSystem::deleteDirectories(vector<string> names) {
  stack<string> invalid;

  for(int i=0;i<names.size();i++) {
    string name=names[i];
    if(currentPath->children[name]==nullptr) 
      invalid.push(name);
    else {
      deleteDirectory(currentPath->children[name]);
      currentPath->children.erase(name);
    }
  }

  while(!invalid.empty()) {
    cout<<"FatalError: "<<invalid.top()<<" - Directory not found!!";
    invalid.pop();
  }
}

void FileSystem::deleteFiles(vector<string> names) {
  stack<string> invalid;

  for(int i=0;i<names.size();i++) {
    string name=names[i];
    if(currentPath->files[name]==false)
      invalid.push(name);
    else 
      currentPath->files.erase(name);
  }

  while(!invalid.empty()) {
    cout<<"FatalError: "<<invalid.top()<<" - File not found!!";
    invalid.pop();
  }
}

void FileSystem::listDirectory() {
  for(auto& pair: currentPath->children)
    cout<<"/"<<pair.first<<endl;
  for(auto& pair: currentPath->files)
    cout<<pair.first<<endl;
}
