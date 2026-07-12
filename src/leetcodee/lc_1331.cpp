#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    각 숫자를 정렬하고, 여기서 중복된 숫자를 제외하여 순위표를 만듦
    그리고 lower_bound를 통해 그 순위를 logn로 파악해가며 배열을 완성하면 됨
    중복된 숫자를 없애는 함수는 stl에 있는 것으로 기억하나, 그 이름과 사용법까진 기억이 안 나므로 직접 작성함
     ㄴ wPtr과 rPtr를 나눠서 중복되지 않았을때만 wPtr에게 쓰기 후 이동을 지시하면 됨
    실행 결과, 23ms(over 96.01%), 37MB(over 98.62%)
*/

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        const int n = arr.size();
        vector<int> result;
        result.reserve(n);

        vector<int> sorted(arr.begin(), arr.end());
        sort(sorted.begin(), sorted.end());

        int wPtr = 1;
        for (int i=1; i<n; i++)
        {
            if (sorted[i-1] != sorted[i])
                sorted[wPtr++] = sorted[i];
        }
        sorted.resize(wPtr);
        
        for (const auto& num : arr)
        {
            int rank = lower_bound(sorted.begin(), sorted.end(), num) - sorted.begin() + 1;
            result.push_back(rank);
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}