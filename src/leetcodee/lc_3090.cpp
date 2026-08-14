#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    n이 최대 100이니까 그냥 브루트포스로 접근해도 됨
    여기에 약간의 최적화를 섞는다면, 시작지점이 a이고 길이가 l인 부분문자열에 대해,
    만약 그 부분문자열이 조건을 충족시키지 않는다면, 동일한 시작지점을 가지며 길이 l이상인 부분문자열은 모두 조건을 만족하지 않음
    이를 이용해 검사를 빠르게 넘길 수 있음
    실행 결과, 0ms(over 100%), 9MB(over 87.78%)

    혹은 슬라이딩 윈도우 방식을 사용하여, 조건을 만족하는 구간을 유지하도록 윈도우 사이즈를 조절하고,
    각 윈도우 사이즈를 확인하여 그 중 최댓값을 반환하는 방법이 있음
    시간복잡도 상으로는 슬라이딩 윈도우 방식이 O(n)으로, 브루트 포스의 O(n^2)보다 뛰어남
    하지만 n=100 수준에서는 그렇게 큰 차이가 없음
*/

class Solution {
public:
    int maximumLengthSubstring(string s) {
        const int n = s.length();
        int maxLen = 2;

        for (int i=0; i<n; i++)
        {
            int freq[26] = {};
            for (int len=1; len<=n-i; len++)
            {
                int chIdx = s[i+len-1] - 'a';
                if (++freq[chIdx] > 2)
                    break;
                else
                    maxLen = max(maxLen, len);
            }
        }
        
        return maxLen;
    }
};

int main()
{
    Solution s;

    return 0;
}