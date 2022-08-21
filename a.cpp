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

// bool solution(string & s, string & p){
//     vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
//     dp[0][0] = true;
//     for (int i = 2; i < dp[0].size(); i += 2)
//     {
//         if (p[i - 1] == '*')
//             dp[0][i] = dp[0][i - 2];
//     }
//     for (int i = 0; i < dp.size() - 1; i++)
//     {
//         for (int j = 0; j < dp[0].size() - 1; j++)
//         {
//             if (p[j] == '*')
//             {
//                 dp[i + 1][j + 1] = (firstMatch(s, p, i, j - 1) && dp[i][j + 1]) || dp[i + 1][j - 1];
//             }
//         }
//     }
//     return dp[dp.size() - 1][dp[0].size() - 1];
// }


class Solution{
public:
    inline bool firstMatch(string &s, string &p, int i, int j)
    {
        return !s.empty() && p[j] == '.' || s[i] == p[j];
    }
    bool isMatch(string s, string p)
    {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        dp[0][0] = true;
        for (int i = 2; i < dp[0].size(); i += 2)
        {
            if (p[i - 1] == '*')
                dp[0][i] = dp[0][i - 2];
        }
        for (int i = 0; i < dp.size() - 1; i++)
        {
            for (int j = 0; j < dp[0].size() - 1; j++)
            {
                if (p[j] == '*')
                {
                    dp[i + 1][j + 1] = (firstMatch(s, p, i, j - 1) && dp[i][j + 1]) || dp[i + 1][j - 1];
                }
                else
                {
                    dp[i + 1][j + 1] = firstMatch(s, p, i, j) && dp[i][j];
                }
            }
        }
        return dp[dp.size() - 1][dp[0].size() - 1];
    }
};

int main() {
    int n;
    cin >> n;
    string tmp;
    cin >> tmp;
    string p;
    int i = 0;
    while (i < tmp.size()) {
        if (tmp[i] == '{') {
            while (tmp[i] != '}')
                i++;
            p += ".*";
        }
        if (tmp[i] != '}')
            p += tmp[i];
        i++;
    }
    // cout << p << endl;
    Solution a;
    while (n--)
    {
        string s;
        cin >> s;
        //cout << s << endl;
        if (a.isMatch(s, p))
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }

    return 0;
}
