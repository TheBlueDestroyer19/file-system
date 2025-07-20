#include <vector>
using namespace std;

struct Folder{
  string name;
  vector<Folder*> children;
  vector<string> files;
};


