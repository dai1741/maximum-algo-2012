#include <iostream>
#include <string>
#include <stack>
using namespace std;

int number(string& s, int& i) {
  int n = s[i++] - '0';
  while(isdigit(s[i])) n = n*10 + s[i++] - '0';
  return n;
}

enum Symbol {EXPR, EXPR2, TERM, TERM2, FACTOR, NONE};

int expr(string& s, int& i) {
  stack<Symbol> st;
  stack<int> st_val;
  stack<char> st_op;
  st.push(EXPR);
  st_op.push('$');  // É_É~Å[
  do {
    int val, val2;
    char op;
    switch(st.top()) {
    case EXPR2:
      op = st_op.top();
      if (op == '+' || op == '-') {
        st_op.pop();
        val = st_val.top(); st_val.pop();
        val2 = st_val.top(); st_val.pop();
        st_val.push(op == '+' ? (val2 + val) : (val2 - val));
      }
      if (s[i] == '+' || s[i] == '-') {
        st_op.push(s[i++]);
        st.push(TERM);
      } else {
        st.pop();
      }
      break;
    case EXPR:
      st.pop();
      st.push(EXPR2);
      st.push(TERM);
      break;
      
    case TERM2:
      op = st_op.top();
      if (op == '*' || op == '/') {
        st_op.pop();
        val = st_val.top(); st_val.pop();
        val2 = st_val.top(); st_val.pop();
        st_val.push(op == '*' ? (val2 * val) : (val2 / val));
      }
      if (s[i] == '*' || s[i] == '/') {
        st_op.push(s[i++]);
        st.push(FACTOR);
      } else {
        st.pop();
      }
      break;
    case TERM:
      st.pop();
      st.push(TERM2);
      st.push(FACTOR);
      break;
      
    case FACTOR:
      if (isdigit(s[i])) {
        st_val.push(number(s, i));
        st.pop();
      } else if (s[i] == '(') {
        i++;
        st.push(EXPR);
        st_op.push('(');
      } else if (s[i] == ')') {
        i++;
        st.pop();
        st_op.pop();
      } else {
        return -1;
      }
      break;
    }
  } while(!st.empty());
  
  return st_val.top();
}


int main() {
  string str = "1+2*6/(10-7)";
  int i = 0;
  cout << str << " = " << expr(str, i) << endl;
  return 0;
}


