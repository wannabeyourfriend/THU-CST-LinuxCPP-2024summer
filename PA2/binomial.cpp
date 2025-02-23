#include <iostream>
#include <cmath>
#include <vector>

int dp_binomial(int n, int k)
{
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(k+1,0));
    for(int i = 0; i <=n ; ++i)
    {
        dp[i][0] = 1;
    }   
    for(int i = 0; i <=n ; ++i)
    {
        for(int j = 1; j <= std::min(i, k) ; ++j)
        {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }
    return dp[n][k];
}

int iteractive_binomial(int n, int k)
{
    int res = 1;
    for(int i = 0; i < k; ++i)
    {
        res *= (n-i);
        res /= (i+1);
    }
    return res;
}

int recursive_binomial(int n, int k)
{
    if (k == 0 || k == n){
        return 1;
    }    
    else{
        return recursive_binomial(n-1, k-1) + recursive_binomial(n-1, k);
    }
}

int main()
{
    int n, k;
    std::cout << "Enter n and k: ";
    std::cin >> n >> k;
    std::cout << "Iteractive binomial: " << iteractive_binomial(n, k) << std::endl;
    std::cout << "Recursive binomial: " << recursive_binomial(n, k) << std::endl;
    std::cout << "Dynamic programming binomial: " << dp_binomial(n, k) << std::endl;
    return 0;
}