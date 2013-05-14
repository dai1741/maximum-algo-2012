#include <iostream>
#include <string>
using namespace std;

int expr(string& s, int& i);
int term(string& s, int& i);
int factor(string& s, int& i);
int number(string& s, int& i);


int expr(string& s, int& i) {
  int val = term(s, i);
  while(s[i] == '+' || s[i] == '-') {
    char op = s[i];
    i++;
    int val2 = term(s, i);
    if (op == '+') val += val2;
    else val -= val2;
  }
  return val;
}

int term(string& s, int& i) {
  int val = factor(s, i);
  while(s[i] == '*' || s[i] == '/') {
    char op = s[i];
    i++;
    int val2 = factor(s, i);
    if (op == '*') val *= val2;
    else val /= val2;
  }
  return val;
}

int factor(string& s, int& i) {
  if (isdigit(s[i])) return number(s, i);

  // ‚±‚±‚Å\•¶‚ª³‚µ‚¯‚ê‚Î s[i] == '(' ‚Æ‚È‚é
  i++; // '('‚ğ“Ç‚İ”ò‚Î‚·
  int ret = expr(s, i);
  i++; // ')'‚ğ“Ç‚İ”ò‚Î‚·
  return ret;
}

int number(string& s, int& i) {
  int n = s[i++] - '0';
  while(isdigit(s[i])) n = n*10 + s[i++] - '0';
  return n;
}


int main() {
  string str = "1+2*6/(10-7)";
  int i = 0;
  cout << str << " = " << expr(str, i) << endl;
  return 0;
}


