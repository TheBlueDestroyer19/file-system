#include <vector>
#include <unordered_map>
#include <string>
using namespace std;


// Class for containing folder node
class Folder{
public:
  Folder* parent;
  unordered_map<string, Folder*> children;
  unordered_map<string, bool> files;
};

//File System Class
class FileSystem{
  Folder* root;
  Folder* currentPath;
  string name;
  string pathName;

public:
  FileSystem(string name="root") {
    root=new Folder;
    this->name=name;
    root->parent=nullptr;
    currentPath=root;
    pathName="/"+name;
  }
  
  string getPath() {return pathName;}
  void changeDirectory(string path, bool* status);
  void deleteDirectory(Folder* current); //Recursive deletion
  void deleteDirectories(vector<string> name);
  void createDirectories(vector<string> name);
  void createFiles(vector<string> name);
  void listDirectory();
  void deleteFiles(vector<string> names);
  void parseCommand(string cmd);
  //void copyFile
  //void cutFile
  //void copyDirectory
  //void cutDirectory
  
  ~FileSystem() {
    deleteDirectory(root);
  }
};

