#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

class Box {

public:
 int a;
 int b;
 int c;

 Box() {

 }
 Box(int a, int b, int c) {
  this->a = a;
  this->b = b;
  this->c = c;
 }

 Box& operatro+(Box & aa, Box & bb) {
    this->a = aa.a + bb.a;
    this->b = aa.b + bb.b;
    this->c = aa.c + bb.c;
    return *this
 }

};


int main() {
    Box a(1,1,1);
    Box b(2,2,2);
    auto c = a + b;
    return 0;
}
