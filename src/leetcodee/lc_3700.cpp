#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    어제와 문제는 동일함
    다만, l~r 범위가 더 좁아졌고, n이 10^9으로 굉장히 커졌음
    따라서 단순히 O(n)으로 접근하면 TLE이 발생함
    때문에 logn으로 해결할 방법을 생각해야함

    힌트를 보니 행렬제곱을 이용하라고 되어있음
    생각해보면 i-1배열에 어떤 k*k행렬을 곱하면 i배열이 나옴
     ㄴ 대충 상/하삼각행렬과 유사한 형태임
     ㄴ 다만 모든 원소가 0이 아니라면 1이며, 양쪽 모두 주대각성분이 0이어야함
    그러나 zigzag 배열의 위상은 2종류이며, 매 iter마다 위상이 반전됨
    그리고 각 위상마다 곱해야하는 행렬 또한 다르기 때문에, 매번 다른 행렬을 곱해줘야함
     ㄴ 따라서 i*ABABABABA...와 같은 꼴이 되는 것
    그러므로 (AB)를 하나로 묶고, 이를 거듭제곱하는 것을 통해 접근하는 것이 권장됨
    여기에 필요 시 A를 한번 곱하면 끝
    시간복잡도는 logn*k^3로 예상됨
    k가 클수록 기하급수적으로 시간이 오래 걸리지만, 이 문제는 k가 최대 75이므로 충분히 괜찮음
     ㄴ 75^3은 421,875임
    그렇기에 이전 문제에선 적용이 불가한데, 거기선 k가 최대 2000이었기 때문

    구현은 행렬곱을 구현하는 것이 먼저라고 생각됨
    구현된 행렬곱을 통해, A*B를 곱하여 기본행렬을 생성함
     ㄴ 놀랍게도 기본 행렬은 어떤 규칙성을 가지고 있음
     ㄴ 따라서 행렬곱없이도 기본행렬을 생성할 수 있을것으로 보여짐
    그리고 입력된 n에 대해 2부터 비트가 1인지 시프트하며 검사하면 됨
    이 때, 시프트하며 기본행렬을 거듭제곱하고, 비트가 1이면 기본 행렬을 배열에 곱하면 됨
    그리고 마지막으로 A를 추가로 곱해야하는지 확인하고, 배열의 합을 구하여 이를 2배하고 반환
    또한 이 모든 과정에서 MOD를 빼먹어선 안됨

    실행 결과, 167ms(over 97.67%), 22MB(over 88.37%)
    여기서 하나 중요한 점을 빼먹었는데, 행렬곱으로 인해 int(32bit)끼리 곱하기 때문에 오버플로우가 발생할 수 있음
     ㄴ MOD를 통해 안전하게 보장되는 것은 더하기뿐
    따라서 배열과 행렬은 long long으로 하여야 오버플로우를 방지할 수 있음
*/

inline int MOD(int a)
{ return a % 1'000'000'007; }

inline int MOD(long long a)
{ return a % 1'000'000'007; }

vector<vector<long long>> matMul(vector<vector<long long>>& matA, vector<vector<long long>>& matB)
{
    const int m = matA.size();
    const int n = matB.front().size();
    vector<vector<long long>> result(m,vector<long long>(n,0));

    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            for (int k=0; k<m; k++)
                result[i][j] = MOD(result[i][j] + MOD(matA[i][k] * matB[k][j]));
        }
    }

    return result;
}

vector<long long> arrMul(vector<long long>& arr, vector<vector<long long>>& mat)
{
    const int n = arr.size();
    vector<long long> result(n,0);

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            result[i] = MOD(result[i] + MOD(arr[j] * mat[j][i]));
    }

    return result;
}

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int w = r-l+1;
        vector<long long> dp(w,1);
        vector<vector<long long>> mat1(w,vector<long long>(w,0));
        vector<vector<long long>> mat2(w,vector<long long>(w,0));

        // init dp
        for (int i=0; i<w; i++)
            dp[i] = w-i-1;

        // build mat1
        for (int i=0; i<w; i++)
        {
            for (int j=i+1; j<w; j++)
                mat1[i][j] = 1;
        }

        // build mat2
        for (int i=0; i<w-1; i++)
        {
            for (int j=0; j<w-1; j++)
                mat2[i][j] = min(w-1-i,w-1-j);
        }

        int bit = 2;
        n -= 2;
        while(bit <= n)
        {
            if (bit & n)
                dp = arrMul(dp,mat2);
            mat2 = matMul(mat2, mat2);
            bit <<= 1;
        }

        if (n & 1)
            dp = arrMul(dp,mat1);

        int sum = 0;
        for (const auto elem : dp)
            sum = MOD(sum + elem);

        return MOD(sum << 1);
    }
};
int main()
{
    Solution s;

    return 0;
}