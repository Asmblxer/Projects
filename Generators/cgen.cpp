#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
typedef long long ll;

string randomString(int len) {
     string s = "";
     for (int i = 0; i < len; i++) {
          s += rnd.next('a', 'z');
     }
     return s;
}

void writeTest(int test) {
     startTest(test);
     int n = rnd.next(1, (int)1e5);
     cout << randomString(n) << '\n';
}
 
int main(int argc, char *argv[]) {
     registerGen(argc, argv, 1);
     for (int tc = 1; tc <= 3; tc++) {
          writeTest(tc);
     }
}
