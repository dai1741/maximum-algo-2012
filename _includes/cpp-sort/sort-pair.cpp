#include <stdio.h>
#include <vector>
#include <algorithm> // sort
#include <map> // pair
using namespace std;

int main() {
  int n = 10;
  vector<pair<int, int> > pairs(n);
  
  for (int i = 0; i < n; i++) {
    pairs[i] = make_pair(i*i % 10, i);
  }

  // firstが小さい順、secondが小さい順にソート
  sort(pairs.begin(), pairs.end());

  for (int i = 0; i < n; i++) {
    printf("(%d,%d) ", pairs[i].first, pairs[i].second);
  }
  puts(""); // => (0,0) (1,1) (1,9) (4,2) (4,8) (5,5) (6,4) (6,6) (9,3) (9,7)
  
  return 0;
}


