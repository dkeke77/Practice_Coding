#include <vector>
#include <iostream>

using namespace std;

/*
@성공
    이 문제에서 매 F에 대한 계산을 수행하면 O(N^2)으로 상당히 느려짐
    그러나 정렬되지 않은 데이터가 들어오고, 이를 정렬해선 안되기 때문에 모든 F는 구해야만 함
    따라서 F 계산을 최적화하는 것이 주효한 방법임
    F(j) = sigma(a_(n-j) * (n-1))인데 F(j)를 한번만 계산하면 다음 F(j+1)를 구할 수 있음
    F(j+1) = F(j) - sum + a_j * n이 성립함
    이는 말로 설명하기 어려우나, 실제로 식을 세워보면 간단히 위 수식이 성립함을 알 수 있음
    따라서 위 수식을 이용하면 O(n)으로 최적화가 가능해짐
    실행 결과는 4~7ms가 나왔는데, 서버 상태에 따른 편차가 있는 것으로 보이며 좋은 상태에선 0ms도 가능할 것으로 보임
     ㄴ 동일한 로직을 가진 알고리즘이 0ms이 달성했음을 다른 사람의 글로 확인함
*/

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0;
        long long rf = 0;
        long long maxResult;
        
        for (int i = 0; i < n; ++i)
        {
            sum += nums[i];
            rf += i * nums[i];
        }
        maxResult = rf;

        for (int i = 0; i < n-1; ++i)
        {
            rf = rf - sum + n * nums[i];
            maxResult = max(rf,maxResult);
        }

        return maxResult;
    }
};

int main()
{
    Solution s;
    vector<int> arr1 = { 2,-1,0,1,-3,3,-3 };
    vector<int> arr2 = { -2,-3,0 };

    cout << s.maxRotateFunction(arr1) << endl;
    cout << s.maxRotateFunction(arr2) << endl;

    return 0;
}