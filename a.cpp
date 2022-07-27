#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main() {
    /*
    if (!fork()) {
        execv("help", NULL);
    }
    wait(NULL);
    cout<<"im father process"<<endl;
    */
    int fd = open("makefile", O_RDWR);
    cout<<fd<<endl;
    while(1);
    return 0;
}
