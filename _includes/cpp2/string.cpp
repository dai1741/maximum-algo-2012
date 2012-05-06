#include <iostream>
#include <string>
// #include <string.h>
using namespace std;

int main() {
  string str = "abcde";
  // char str[256] = "abcde";

  str = "hoge";
  // strcpy(str, "hoge");

  str += "fuga";
  // strcat(str, "fuga");

  str.size();
  // strlen(str);
  
  if (str == "bar") {}
  // if (strcmp(str, "bar") == 0) {}

  if (str < "piyo") {}
  // if (strcmp(str, "piyo") < 0) {}
  
  str = "fghij";
  cout << str << endl; // #=> fghij
  cout << str[3] << endl; // i

  str.find("hi"); // 2
  str.find("f"); // 0
  str.find("a"); // -1
  
  str.substr(2); // hij
  str.substr(2, 1); // h

	return 0;
}
