#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

/*

@성공1
    1. 배열을 순회하며 양수와 0은 즉시 누적합에 더하고, score++. 그리고 음수는 최대힙에 push
    2. 최대힙을 pop하며 누적합에서 가산. 누적합이 그대로 양수면 score++, 아니면 종료
    이렇게 구현했지만, 44ms로 생각보다 빠르진 않았음
    이에 gpt는 힙이 그렇게 cpu 친화적이진 않다고 함
    또한 if문이 3개인 것도 성능 하락의 원인 중 하나일 수 있다고 함

@성공2
    algorithm의 sort를 활용함
    19ms로 큰 성능 향상을 확인함
    sort가 더 cpu 친화적이어서 그런 것으로 보이며, 정렬 후엔 벡터를 순회하는 것도 캐시 친화적이어서 그런것같음
    동시에 if문도 1개밖에 없는 것도 적지 않은 영향이 있는듯
*/

class Solution {
public:
    int maxScore(vector<int>& nums) {
        long long sum = 0;
        int count = 0;
        sort(nums.begin(), nums.end());
        
        for (int i = nums.size()-1; i >= 0; --i)
        {
            sum += nums[i];
            if (sum > 0)               
                count++;
            else
                break;
        }

        return count;
    }
};

int main()
{
    Solution s;
    vector<int> arr1 = { 2,-1,0,1,-3,3,-3 };
    vector<int> arr2 = { -2,-3,0 };

    cout << s.maxScore(arr1) << endl;
    cout << s.maxScore(arr2) << endl;

    return 0;
}