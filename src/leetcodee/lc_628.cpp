#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    결과가 음수/양수/0 3가지인데, 각각에 대해 따로따로 계산해서 처리하면 됨
    양수의 경우엔 그 절댓값이 최대일수록 커지므로,
    제일 큰 양수 3개, 혹은 제일 작은 음수 2개와 제일 큰 양수 1개로 계산할 수 있음
    음수의 경우엔 그 절댓값이 최소일수록 커지므로,
    제일 작은 음수 3개, 혹은 제일 작은 양수 2개와 제일 작은 음수 1개로 계산할 수 있음
    마지막으로 0의 경우엔 0이 1번이라도 등장하면 계산할 수 있음
    각각의 케이스를 계산 가능하다면 계산하고, 이 중에서 최댓값을 구하면 됨
    실행 결과, 0ms(over 100%), 31MB(over 76.45%)

    그런데 다른 풀이를 보니 저렇게 분기를 전부 나눌 필요는 없었음
    정답이 음수인 경우는 양수2/음수1 혹은 양수0인 케이스뿐임
    마찬가지로 0인 경우는 위 케이스에 0이 추가된 케이스임
    위의 케이스들에서 최대값은 모두 제일 큰 것 3개의 곱임
    이는 양수의 경우를 처리하는 과정의 일부와 일치함
    따라서 제일 큰 것 3개 / 제일 큰 것 1개와 제일 작은 것 2개의 곱만으로 구할 수 있음
    실행 결과, 0ms(over 100%), 32MB(over 46.18%)

    정렬을 없애고 O(n)으로도 처리할 수 있겠지만, O(nlogn)과의 성능 차이는 미미함
    하지만 그 성능 차이에 비해 구현은 정렬을 쓰는 편이 압도적으로 간결함
*/

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        const int n = nums.size();
        sort(nums.begin(), nums.end());

        return max(nums[n-1]*nums[n-2]*nums[n-3], nums[n-1]*nums[0]*nums[1]);
    }
};
int main()
{
    Solution s;

    return 0;
}