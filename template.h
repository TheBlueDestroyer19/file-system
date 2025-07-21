#include <vector>
#include <unordered_map>
using namespace std;


// Class for containing folder node
class Folder{
public:
  Folder* parent;
  unordered_map<string, Folder*> children;
  unordered_map<string, bool> files;
};

bool validate(string);


//File System Class
class FileSystem{
  Folder* root;
  string name;

public:
  Folder(string name="root") {
    root=new Folder;
    this->name=name;
    root->parent=nullptr;
  }

  Folder* changeDirectory(string path, Folder* currentPath, bool* status);
  void deleteDirectory(Folder* current); //Recursive deletion
  void deleteDirectories(vector<string> name, Folder* currentPath);
  void createDirectories(vector<string> name, Folder* currentPath);
  void createFiles(vector<string> name, Folder* currentPath);
  void listDirectory(Folder* currentPath);
  void deleteFiles(vector<string> names, Folder* currentPath);
  //void copyFile
  //void cutFile
  //void copyDirectory
  //void cutDirectory
  
  ~Folder() {
    deleteDirectory(root);
  }
};


//Interface for the file system
class Interface{
public:

};
