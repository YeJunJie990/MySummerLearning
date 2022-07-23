#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

using namespace std;

int main() {
    if (!fork()) {
        cout<<"im child, doing: ";
        cout<<"im child, doing: ";
        cout<<"im child, doing: ";
        execv("help", NULL);
    }
    wait(NULL);
    cout<<"im father process"<<endl;
    return 0;
}
