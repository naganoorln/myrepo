#include <stdio.h>
/*
   1.int a; a is a integer variable; a = 10; we can change the value of a ie  a = 20;
   2.const int a; or int const a; a is constant integer variable;a = 10; we can not  the value of a ie a = 20; 
   3.int* p; p is pointer variable which holds address of integer variable; suppose int a = 10; p = &a; *p = 20;
   4.const int* p; or int const *p; p is a pointer variable which holds address of integer variable. 
     The integer variable is constant. suppose int a = 10; p = &a;*p = 20; error
   5.int* const p; p is pointer variable which holds the address of integer variable suppose int a = 10;int b = 20;
     p = &a; but p = &b error it means pointer is constant once it pointes to an address it can not hold another address.
   6.const int* const p; or int const * const p; both pointer and variables are constant
     suppose a= 10; b = 20; p = &a; *p = 30; error  p = & b error.
*/
   
 int main()
 {
     //1.Non constant integer
     int a = 10;
     a = 20; //ok 
     
     //2.Constant integer
     const int b = 50; //or int const b;
     b = 60; //error
     
     //3.pointer to integer
     int* p;
     int c = 10;
     int m = 20;
     p = &c;
     *p = 20; // ok
     p = &m; // ok
     
     //4.Pointer to constant integer
     const int* q; //or int const *p;
     int d = 10;
     q = &d;
     *q = 30; //error
     
     //5.Constant pointer to integer
     int* const r;
     int e = 10;
     int f = 20;
     r = &e;
     r = &f; //error
     
     //6.Constant pointer to constant integer
     const int* const s; // or int const *p;
     int g = 10;
     int h = 20;
     s = &g;
     *s = 40; //error
     s = &h; //error;
     
     return 0;
 }
 
 /*
 main.c: In function ‘main’:
main.c:22:8: error: assignment of read-only variable ‘b’
   22 |      b = 60; //error
      |        ^
main.c:36:9: error: assignment of read-only location ‘*q’
   36 |      *q = 30; //error
      |         ^
main.c:42:8: error: assignment of read-only variable ‘r’
   42 |      r = &e;
      |        ^
main.c:43:8: error: assignment of read-only variable ‘r’
   43 |      r = &f; //error
      |        ^
main.c:49:8: error: assignment of read-only variable ‘s’
   49 |      s = &g;
      |        ^
main.c:50:9: error: assignment of read-only location ‘*(const int *)s’
   50 |      *s = 40; //error
      |         ^
main.c:51:8: error: assignment of read-only variable ‘s’
   51 |      s = &h; //error;
      | 
*/
