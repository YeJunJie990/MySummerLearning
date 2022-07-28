#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

// int main() {
//     int n;
//     cin>>n;
//     string num = to_string(n);
//     set<char> appeared;
//     string ans;
//     for (int i = num.size() - 1; i >= 0; i--) {
//         if (appeared.count(num[i])) continue;
//         ans += num[i];
//         appeared.insert(num[i]);
//     }
//     cout<<ans<<endl;
//     return 0;
// }

typedef unsigned long long ll;

bool isValid(ll n) {
    string num = to_string(n);
    int i = 1;
    int k = 0;
    while (i < num.size()) {
        if (num[i] != num[i - 1]) k++;
        i++; 
    }
    return k == 1;
}

int main() {
    int n;
    while (1) {
        cin>>n;
        if (n == 0) break;
        int i = 1;
        ll ans = -1;
        while (ans == -1) {
            ll cur = (ll) n * i;
            if (isValid(cur)) ans = cur;
            i++;
        }
        cout<<n<<": "<<ans<<endl;
    }
    return 0;
}
