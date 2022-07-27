#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/types.h>

using namespace std;

void myprint(int fd){
    cout<<"hello exec: "<< fd <<endl;
}

int main() {
    //cout<<"im help func, now im doing: ";
    int fd = open("makefile", O_RDWR);
    if (fd == -1) {
        perror("open file false");
    }
    myprint(fd);
    return 0;
}