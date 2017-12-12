#include <bits/stdc++.h>
using namespace std;

char * func(char *ptr)
{
    ptr+=3;
    return ptr;
}

class A {

};
extern int a();
int a();
int main(void)
{
 //   char *x, *y;
 //   x = "Hello";
 //   y = func(x);
 //   printf("y = %s\n", y);
/*
    try {
        throw '5';
    }
    catch(...) { cout << "A\n";}
    catch (int param) { cout << "B\n"; } 
    catch (char  param) { cout << "C\n"; } 
*/

    int i, *j, ** k;
    j = &i;
    k = &j;
   cout << *j << **k << *(*k) << "\n";

   int a = 7;
   if (a = 1) {
    cout << "a=" << a << "\n";

   }

 const int MAX = 10;
 enum a {a, b, MAX};
   cout << "AMX: " << MAX;
}
