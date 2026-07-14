#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    dp 문제임은 힌트와 코멘트를 보고 빠르게 알 수 있었지만, seq를 dp를 통해 구성하는 것에 어려움이 있었음
    코멘트에 따르면 seq1/seq2/skip 3가지로 나누면 풀 수 있다고 하였으나, 그 해설을 잘 이해하지 못했었음
    하지만 오랫동안 고민한 끝에 해결의 실마리를 잡을 수 있었음
    우선, 간단하게 seq를 dp를 통해 만드는 것 먼저 시작해야함
    이는 선택/미선택으로 구성되며 아래와 같은 점화식에 의해 구성됨
     ㄴ 이번의 선택은 이전의 선택/미선택에 이번 숫자를 삽입
     ㄴ 이번의 미선택은 이전의 선택/미선택을 그대로 가져오기만 함
    이를 매 원소마다 반복하면 해당 배열에 대한 모든 seq(어찌보면 부분집합)를 얻을 수 있음
    이 규칙은 그대로 seq1/seq2/skip에 적용 가능함
    각 seq엔 그 개수만 기록하는게 아니라, seq의 gcd를 기록하고, seq1/seq2 간 동일 gcd의 조합을 통해 계산
    하지만 이 방법은 두 seq 간 중복 원소 배제가 불가능함

    풀이를 보고나서야 접근을 다르게 해야됨을 알음
    어떤 두 seq의 gcd를 각각 g1, g2라고 하자
    그러면 가능한 seq끼리 (g1,g2) 조합이 생길 것이고, 이 조합에 새로운 숫자를 추가해서 다음 조합을 만들 수 있음
    여기서 새 숫자를 seq1에 넣을지, 혹은 seq2에 넣을지, 아니면 아무 곳에도 안 넣을지를 각각 처리하는 것
     ㄴ 따라서 다음 DP의 (gcd(g1,num),g2), (g1,gcd(g2,num)), (g1, g2)에 이전 DP값을 누적
    이전 시행의 모든 조합에 대해 시행해야하므로, 매번 가능한 조합이 무엇이 있었는지 확인해야함
    그리고 처음 시작시엔 양쪽 모두 비어있으므로, [0][0]을 1로 초기화해야함
    마지막으로 두 gcd가 같은 경우를 세어야하므로 DP 테이블의 대각선 성분의 합을 구하면
     ㄴ 단, [0][0]은 제외
    실행 결과, 228ms(over 89.56%), 35MB(over 86.09%)
*/

class Solution {
public:
    const int MOD_FACTOR = 1'000'000'007;

    int getGCD(int a, int b)
    {
        if (a == 0 || b == 0)
            return a+b;

        while(a % b != 0)
        {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return b;
    }

    int subsequencePairCount(vector<int>& nums) {
        const int n = nums.size();
        const int maxVal = *max_element(nums.begin(), nums.end());
        int answer = 0;
        vector<vector<int>> prevDP(maxVal+1, vector<int>(maxVal+1,0));
        vector<vector<int>> currDP(maxVal+1, vector<int>(maxVal+1,0));
        currDP[0][0] = 1;

        for (int i=0; i<n; i++)
        {
            swap(prevDP, currDP);
            for (int j=0; j<=maxVal; j++)
            {
                for (int k=0; k<=maxVal; k++)
                    currDP[j][k] = 0;
            }
            
            int num = nums[i];

            for (int j=0; j<=maxVal; j++)
            {
                for (int k=0; k<=maxVal; k++)
                {
                    if (prevDP[j][k] == 0) continue;

                    currDP[j][k] = (currDP[j][k] + prevDP[j][k]) % MOD_FACTOR;

                    int j_gcd = getGCD(num,j);
                    currDP[j_gcd][k] = (currDP[j_gcd][k] + prevDP[j][k]) % MOD_FACTOR;

                    int k_gcd = getGCD(num,k);
                    currDP[j][k_gcd] = (currDP[j][k_gcd] + prevDP[j][k]) % MOD_FACTOR;
                }
            }
        }

        for (int i=1; i<=maxVal; i++)
            answer = (answer + currDP[i][i]) % MOD_FACTOR;

        return answer;
    }
};
int main()
{
    Solution s;

    return 0;
}