#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
@성공1
    풀이를 본 결과, 접근 자체가 잘못된 것은 아니었음
    숫자를 1개만 바꿔도 되는 구간이 있고, 그리고 숫자를 바꿀 필요가 없는 지점이 있음
    이를 브루트-포스하게 풀어낸다면 처음 시도했던 이산 분포 누적과 동일하게 됨
    그러나 이것이 실패했던 이유는 누적 배열이 최대 2*10^5로 비대하기 때문이 아님
    이산 분포 누적을 위해 누적 배열 전체와 입력 배열 전체를 순회하기 때문임
    이는 O(n*l), 최대 2*10^10번 반복하기 때문에 TLE이 났던것임
    따라서 더 나은 방법이 필요함

    그에 대한 해답은 차분 배열(delta/difference arr)임
    분포값은 어느 시점에 변동이 있고, 다음 변동까진 그 값이 유지됨
    따라서 그 변동만 누적 배열에 누적하여도, 이산 분포 누적을 복구할 수 있음
     ㄴ 누적 종료 후, 누적 배열을 순회하여 복구하는 것을 sweep이라 하겠음
    그리고 변동은 총 4번만 있음
     ㄴ 1-구간 시작/종료, 0-지점 시작/종료
    즉, O(n+l) : 4*n+2*l로 해결이 가능함

    실행 결과, 20ms(over 28.44%), 94MB(over 41.28%)가 나옴
    메모리는 약 50%가 93.3~93.5MB에 분포하기에 준수하다고 생각됨
    실행 속도를 더 줄여보기 위해, highBnd의 계산에서 max 함수를 제거하여봄

    실행 결과, 8ms(over 66.05%), 93MB(over 61.47%)가 나옴
    그리고 더 줄여보기 위해, sweep를 조기 종료 가능하도록 바꿔봄
    제일 마지막 1-구간 종료 지점에서 조기 종료하도록 함

    실행 결과, 3ms(over 88.07%), 94MB(over 41.28%)가 나옴
    따라서 해당 최적화가 유의미하게 영향을 줬다고 볼 수 있음
    그리고 더 나아가 sweep의 시작점도 빠르게 시작할 수 있다고 볼 수 있지만,
    이미 3ms이 뜬 만큼, 큰 효용이 있을지는 모르겠음
*/

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        const int numsSize = nums.size();
        vector<int> diffArr(limit*2+2,0);

        int endSweep = 0;

        for (int i = 0; i < numsSize/2; ++i)
        {
            int comple = nums[i] + nums[numsSize-i-1];

            int lowBnd = min(nums[i],nums[numsSize-i-1]) + 1;
            int highBnd = comple - lowBnd + limit + 2;

            endSweep = max(endSweep,highBnd);

            diffArr[lowBnd]--;
            diffArr[highBnd]++;
            diffArr[comple]--;
            diffArr[comple+1]++;
        }

        int counter = numsSize;
        int answer = numsSize;
        for (int i = 2; i <= endSweep; ++i)
        {
            counter += diffArr[i];
            answer = min(answer,counter);
        }

        return answer;
    }
};

int main()
{
    Solution s;
    vector<int> v = {1,3,1,1,1,2,3,2,3,1,3,2,1,3};
    int k = 3;

    cout << s.minMoves(v,k) << endl;

    return 0;
}