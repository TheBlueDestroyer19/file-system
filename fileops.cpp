#include <iostream>
#include <stack>
#include "template.h"

Folder* FileSystem::changeDirectory(string path, Folder* currentPath, bool* status) {
  string folder=""; 
  Folder* original=currentPath;
  *status=true;

  for(int i=0;i<path.length() && *status;i++) {
    if(path[i]!='/')
      folder.push_back(path[i]);
    else {
      if(folder=="..")
        currentPath=currentPath->parent;
      else if(folder=="~")
        currentPath=root;
      else if(currentPath->children[folder]!=nullptr)
        currentPath=currentPath->children[folder];
      else if(currentPath->children[folder]==nullptr)
        *status=false;

      folder="";
    }
  }
  if(*status==false) return original;
  return currentPath;
}

void FileSystem::createDirectories(vector<string> names, Folder* currentPath) {
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

void FileSystem::createFiles(vector<string> names, Folder* currentPath) {
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
      pair.second=null;

    curr->parent=nullptr;
    delete curr;
  }
}

void FileSystem::deleteDirectories(vector<string> names, Folder* currentPath) {
  stack<string> invalid;

  for(int i=0;i<names.size();i++) {
    string name=names[i];
    if(currentPath->children[name]==nullptr) 
      invalid.push(name);
    else {
      deleteDirectory(currentPath->children[name]);
      currentPath->children[name]=nullptr;
    }
  }

  while(!invalids.empty()) {
    cout<<"FatalError: "<<invalids.top()<<" - Directory not found!!";
    invalids.pop();
  }
}

void FileSystem::deleteFiles(vector<string> names, Folder* currentPath) {
  stack<string> invalid;

  for(int i=0;i<names.size();i++) {
    string name=names[i];
    if(currentPath->files[name]==false)
      invalid.push(name);
    else 
      currentPath->files[name]=false;
  }

  while(!invalids.empty()) {
    cout<<"FatalError: "<<invalids.top()<<" - File not found!!";
    invalids.pop();
  }
}

void FileSystem::listDirectory(Folder* currentPath) {
  for(auto& pair: currentPath->children)
    cout<<"/"<<pair.first<<endl;
  for(auto& pair: currentPath->files)
    cout<<pair.first<<endl;
}
