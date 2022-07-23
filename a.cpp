#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;

int main() {
    if (!fork()) {
        cout<<"im child, doing: ";
        execv("help", NULL);
    }
    waitpid();
    cout<<"im father process"<<endl;
    return 0;
}
