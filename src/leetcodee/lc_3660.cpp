#include <iostream>>
#include <vector>

using namespace std;

/*
@접근1
    구간 [a,b]에 대해, nums[b]가 global min이라면 [a,b]의 모든 수는 그 구간의 max로 바꿀 수 있음
     ㄴ 구간 내 모든 수가 b로 점프 가능하고, b에선 모든 수로 점프가 가능하기 때문
    그리고 가능한 모든 수를 현재 max로 바꾸는 것이 좋음
     ㄴ nums[a] > nums[b+i]라면 nums[a]로 대체할 수 있기 때문
     ㄴ 만약 nums[a] < nums[b+i]라면, 애시당초 [0,b+i-1]는 nums[b+i]일 수 없음
    따라서 다음과 같이 진행
    1) 최솟값과 그 사이의 최댓값 탐색
    2) 0~최솟값까지 일괄적으로 그 사이의 최댓값으로 점령
    3) 최솟값 이후부터 다시 최솟값과 그 사이의 최댓값 탐색 후, 최댓값으로 점령
    4) 반복
    시간복잡도 O(n) 예상 : 전체 배열을 2번 순회하기 때문

    반례 : [30,21,5,35,24]
    위 경우엔 30,21이 5를 경유하지 않고, 제일 왼쪽의 24를 경유해야 최댓값 35에 도달할 수 있음
    즉, 당장 최솟값으로 이동하는 것이 최댓값을 보장하지 않음
    때문에 이 로직은 전역적으로 최댓값을 추적하지 않는 경우들이 있음

@접근2
    오른쪽에서부터 점령해나간다는 아이디어
    값의 크기에 따라 한쪽 사이드가 점령된다는 점에서 착안
     ㄴ 어느 영역에 대해, 그곳의 최댓값은 자신 오른쪽을 전부 자신으로 채울 수 있고, 최솟값은 왼쪽을 채울 수 있음
    사전에 i까지의 최솟값/최댓값의 인덱스를 저장하는 배열을 마련
     ㄴ 최솟값은 역순으로 구성
    제일 오른쪽에서 현재 최댓값 인덱스로 이동
    최댓값 인덱스에서 최솟값 인덱스가 무엇인지 확인 후, 왼쪽으로 해당 최솟값보다 작은 최댓값이 나올때까지 이동
    그 후, 점령된 영역에서부터 왼쪽으로 최솟값이 바뀔때까지 이동
    이동이 끝난 후, 그 직전까지 해당 최댓값으로 점령 가능한 것으로 보고 해당 영역까지 점령

    시간복잡도 O(n) 예상 : 4번 순회하기 때문 (3번으로 줄일 수 있음)

    반례 : [56,8,56,31,68,15,87,75,63]
    위 경우엔 56이 56->15->68->63->87를 통해 최댓값인 87이 가능함
    하지만 이 로직에선 점령 이후, 왼쪽으로 최솟값과 비교하며 확장하는 상황에서 더 작은 최솟값을 만나면 확장이 끝남
    따라서 8 앞의 56에는 도달하지 못함
    그래서 확장이 최솟값에 의해 멈추지 않고, 인덱스 0까지 확인하도록 변경
    그랬더니 입력이 긴 경우에 TLE이 발생함
     ㄴ 이 변경으로 인해 시간복잡도가 O(n^2)가 됐음
    이전 버전은 TLE이 안 뜨는 것으로 보아, O(n)이어야 테스트 케이스를 통과할 수 있을 것으로 보임

@성공
    어느 인덱스 기준 왼쪽 구간에서 "오른쪽 최솟값보다 큰 값" 중 제일 왼쪽에 위치한 것
    해당 위치까지 점령이 가능함
    이에 대한 배열을 만들어서 점령 중에 이를 이용하도록 하였음
    이 배열은 최솟값 배열과 포인터를 활용하여 생성함
     ㄴ 앞에서부터 현재 최솟값 인덱스랑 ptr의 값과 비교해가며 진행
     ㄴ 만약 기존값이 최솟값보다 크거나 같다면 그대로 진행
     ㄴ 그러나 최솟값보다 작게 된다면 그 값보다 큰 값이 나올때까지 ptr 이동
    시간복잡도는 O(n)으로 예상됨
     ㄴ 대략 최대 5n 정도 소모될 것으로 보임

    실행 결과, 39ms(over 5.39%), 231MB(over 5.00%)가 나옴
    메모리는 50%가 256MB를 사용한 것을 미루어보아, 크게 문제는 없다고 생각됨
    하지만 실행시간은 대체로 7ms~16ms에 위치한 것을 보아, 더 빠르게 할 여지가 있다고 보여짐

    최댓값 인덱스에 따라 점진적으로 확장하지 않고, leftBridgeIdx만 이용하여 확장하도록 함
    그 결과, 14ms(over 47.84%), 232MB(over 5.00%)가 나옴
     ㄴ 실행시간이 최대 31ms까지 나오기에 신뢰도 높은 수치는 아닌 것으로 보임

@개선
    다른 풀이를 본 결과, 대부분 접근은 유사하지만 이것보다 더 간단하게 풀어내는 것도 가능했음
    단순히 최댓값와 최솟값을 비교하기만 하면 됨
    맨 뒤에서부터 한칸 앞의 최댓값이 현재 최솟값보다 크다면, 해당 칸은 점령 가능함
    따라서 현재 칸의 값을 앞 칸에 덮어씌우고 전진할 수 있음
    만약 그렇지 않다면 앞 칸엔 새로운 최댓값을 쓰고 전진하면 됨

    동일하게 시간복잡도는 O(n)이지만 3n 정도 소모되기때문에 성능은 더 뛰어남
     ㄴ 실행 결과, 5~19ms가 나옴
     ㄴ 벡터를 2개로 줄일 수 있어, 메모리는 219MB(over 80.53%)로 약간 절약이 가능함
     ㄴ 사실 최솟값 1개만 사용할 수 있으나, 정답을 저장할 별도의 벡터가 필요하기에 무조건 2개 이상이 필요함
*/

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        vector<int> result(nums.size(),0);
        vector<int> prefixMaxIdx(nums.size(),0);
        vector<int> suffixMinIdx(nums.size(),0);
        vector<int> leftBridgeIdx(nums.size(),0);

        if (nums.size() == 1)
            return nums;

        suffixMinIdx[nums.size()-1] = nums.size()-1;
        for (int i = nums.size()-2; i >= 0; --i)
        {
            if (nums[suffixMinIdx[i+1]] >= nums[i])
                suffixMinIdx[i] = i;
            else
                suffixMinIdx[i] = suffixMinIdx[i+1];
        }

        int ptr = 0;
        prefixMaxIdx[0] = 0;
        leftBridgeIdx[0] = 0;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[prefixMaxIdx[i-1]] <= nums[i])
                prefixMaxIdx[i] = i;
            else
                prefixMaxIdx[i] = prefixMaxIdx[i-1];

            while(nums[ptr] <= nums[suffixMinIdx[i]] && ptr < nums.size()-1)
                ptr++;
            leftBridgeIdx[i] = ptr;
        }

        int conquered = nums.size();

        while (conquered > 0)
        {
            int toConquer = prefixMaxIdx[conquered-1];

            while(toConquer > 0 && leftBridgeIdx[toConquer] < toConquer)
                toConquer = leftBridgeIdx[toConquer];

            for (int i = conquered-1; i >= toConquer; --i)
                result[i] = nums[prefixMaxIdx[conquered-1]];
            
            conquered = toConquer;
        }

        return result;
    }
};

int main()
{
    Solution s;
    vector<int> v = {21,135,15,56,149,37,121,128,166,99,85,170,139};

    for(auto i : s.maxValue(v))
        cout << i << " ";
    cout << endl;

    return 0;
}