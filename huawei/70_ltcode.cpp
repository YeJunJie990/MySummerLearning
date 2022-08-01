/*
    leetcode 70 爬楼梯
    假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
    每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin>>n;
    vector<int> dp(n + 1);
    dp[1] = 1;
    if (n == 1) return 1;
    dp[2] = 2;
    if (n == 2) return 2;
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout<<dp[n]<<endl;
    return 0;
}