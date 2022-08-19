#include<bits/stdc++.h>

using namespace std;

vector<string> split(string s, char token) {
	/*
		s: 待分割字符串
		token：以token为间隔进行分割
		return：返回以token分割好的字符串，存在vector里面
	*/
    stringstream sin(s);
    string tmp;
    vector<string> ans;
    while (getline(sin, tmp ,token)) {
        ans.push_back(tmp);
    }
    return ans;
}

bool Solution(string & code) {
    
}


int main() {
    int n;
    cin>>n;
    while (n--) {
        string code;
        cin>>code;

    }
    return 0;
}
