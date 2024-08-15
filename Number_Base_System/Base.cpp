#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string decimal_to_any_base(ll decimal, ll base){
     if(decimal == 0) return "0";
     string num = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
     string result;
     do{
          result.push_back(num[decimal % base]);
          decimal /= base;
     }while(decimal != 0);
     return string(result.rbegin(), result.rend());
}

ll  any_base_to_decimal(string str, int base) {
     auto val = [](char c){
        return (c >= '0' && c <= '9' ? (int) c - '0' : (int) c - 'A' + 10);
     };
     ll len = str.size(), power = 1, num = 0, i;
     for (i = len - 1; i >= 0; i--) {
          num += val(str[i]) * power;
          power = power * base;
     }
     return num;
}

int main(int argc, char const *argv[]) {
     cout << "welcome to our program" << endl;
     while (true) {
          cout << "enter the number you want to convert : ";
          string number;      cin >> number;
          cout << "enter the base of the number : ";
          ll base;            cin >> base;
          cout << "enter the base you want to convert to : ";
          ll new_base;        cin >> new_base;
          cout << "the number in base " << new_base << " is " 
          << decimal_to_any_base(any_base_to_decimal(number, base), new_base) << endl;
          cout << "do you want to continue? (y / n): ";
          char c;             cin >> c;
          if (c == 'n') break;
     }
     return 0;
}
