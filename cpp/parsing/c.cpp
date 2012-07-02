#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<numeric>
#include<queue>
#include<stack>
using namespace std;
#define all(c) (c).begin(), (c).end()
#define rep(i,n) for(int i=0; i<(int)(n); i++)
typedef __int64 ll;

struct Tree {
	Tree* l;
	int type;
	Tree* r;
	
	Tree(Tree* l, int type, Tree* r) : l(l), type(type), r(r) {}
	Tree() : l(NULL), type(0), r(NULL) {}
};


string s;
int pos = 0;
Tree trees[2000];
int numTrees = 0;

Tree* form() {
	char c = s[pos++];
	Tree ret;
	Tree* l;
	char opr;
	switch(c) {
	case '(':
		l = form();
		opr = s[pos++];
		if (opr == '-') { // "->"
			pos++;
			opr= '$';
		}
		ret = Tree(l, opr, form());
		pos++; // )
		break;
	case '-':
		ret = Tree(form(), c, NULL);
		break;
	default:
		if (c == 'T') c = 1;
		else if (c == 'F') c = 0;
		ret = Tree(NULL, c, NULL);
		break;
	}
	trees[numTrees] = ret;
	return &trees[numTrees++];
}

Tree* expr() {
	pos = 0;
	numTrees = 0;
	trees[numTrees] = Tree(form(), s[pos++], form());
	//cout << (char)(trees[numTrees].type) << endl; // assert == '='
	return &trees[numTrees++];
	
}

Tree* t;
vector<char> vars;
vector<bool> taiou;

int check(Tree* t) {
	int l, r;
	int ret;
		//cout << (char)t->type << " checkbefore " << endl;
	switch(t->type) {
	case '=':
		ret = check(t->l) == check(t->r);
		break;
	case '+':
		ret = check(t->l) || check(t->r);
		break;
	case '*':
		ret = check(t->l) && check(t->r);
		break;
	case '$':
		l = check(t->l);
		r = check(t->r);
		ret = !l || r;
		break;
	case '-':
		ret = !check(t->l);
		break;
	case 1:
		ret = 1;
		break;
	case 0:
		ret = 0;
		break;
	default:
		ret = taiou[t->type - 'a'];
		break;
	}
		//cout << (char)t->type << " checkafter " << ret << endl;
	return ret;
}


bool detect_and_check(int i) {
	if (i == vars.size()) {
		int a = check(t);
		//cout << "check" << a << endl;
		return a;
	}
	else {
		taiou[i] = true;
		if (!detect_and_check(i+1)) return false;
		taiou[i] = false;
		if (!detect_and_check(i+1)) return false;;
	}
	return true;
}

int main() {
	for(char i = 'a'; i <= 'k'; i++) {
		vars.push_back(i);
	}
	taiou = vector<bool>(vars.size());
	while(cin >> s, s != "#") {
		s += "=";
		t = expr();
		for(char i = 0; i < taiou.size(); i++) {
			taiou[i] = false;;
		}
		cout << (detect_and_check(0) ? "YES" : "NO") << endl;
	}
	
	return 0;
}
