#include <vector>
#include <iostream>

using namespace std;

/*
@풀이1
    벡터를 순회하며 pivot보다 작은 것과 큰 것을 분류하고, 나중에 합치면 됨
    이때, pivot과 동일한 것은 분류하지 않고 그 개수만 세어야함
    그리고 합칠땐 작은 것을 모은 벡터에 그대로 pivot과 큰 것을 붙이면 됨
     ㄴ 굳이 새로운 벡터를 만들 필요가 없는 것
    실행 결과, 4ms(over 81.51%), 129MB(over 70.78%)

    더 최적화하자면 작은 것을 nums의 앞에서부터 저장하고, 큰 것은 배열에 저장하는 것이 있음
    이 동작은 모두 인덱스 포인터를 이용하여 수행하면 됨
    실행 결과, 3ms(over 87.42%), 128MB(over 70.83%)
    그러나 구조 변경이 없는 상태에서, 자료구조의 변경만으로 얻는 이득은 적은 것으로 보임
    이는 데이터의 크기가 그렇게 크지도 않으며, 기존 방식의 데이터 접근이 이미 충분히 optimal하였기 때문이라고 생각됨
     ㄴ 여기에 시간복잡도가 O(n)인 점도 컸던 것으로 보임
    
@풀이2
    이 문제를 공간복잡도 O(1)에서 해결하는 것도 가능함
    하지만 이는 삽입 정렬을 응용한 방식으로 접근해야함
    pivot보다 큰 것들을 왼쪽에서 밀어낸다는 느낌으로 풀어내면 됨
     ㄴ 공간복잡도 O(1)에 해결하기 위해선 교환 연산만이 가능하기 때문
    그리고 오른쪽에서부터 작은 것들이 나오기 직전까지 pivot을 또 밀어내면 됨
    밀어내기 연산은 각 원소마다 끝까지 봐야할 수도 있음
    따라서 삽입 정렬과 마찬가지로 시간복잡도 O(n^2)을 가짐
    그렇기에 단순하게 구현한다면 10^10로 TLE이 발생함
    보다 영리한 방법을 이용하여 구현할 필요가 있음

    왼쪽부터 nums의 원소를 확인할때, 단순히 밀어내는 것이 아니라 어디로 보내야할지 안다면 불필요한 swap이 줄어들 것
    즉, 해당 위치부터 스택처럼 차곡차곡 쌓으면 됨
    여기서 발상하여 큐와 스택을 흉내내어, 왼쪽과 오른쪽 구역을 구성하는 방법을 설계함
    우선 pivot보다 큰 것이 있는 곳을 오른쪽 구역, 그외의 구역을 왼쪽 구역이라고 함
     ㄴ 이는 nums를 한번 순회하여 계산
    이 방법은 왼쪽 구역과 오른쪽 구역의 앞에서부터 순차적으로 정답을 구성해감
    처리가 끝난 영역은 절대 건들지 않으며, 처리가 필요한 영역을 circular하게 스캔함
    이를 위해 구현한 것이 의사-큐임
     ㄴ 왼쪽 구역 중 처리가 되지 않은 영역을 큐처럼 사용함
    큐를 circular하게 순회하며 아래 규칙에 따라 동작함
     ㄴ 만약 현재 ptr의 원소가 pivot보다 작다면, 제일 왼쪽으로 밀어내고 큐 크기 줄임
     ㄴ pivot와 같다면, 제일 오른쪽으로 밀어내고 큐 크기 줄임
     ㄴ pivot보다 크다면 rEnd와 교환
    위 동작을 통해 의사-큐엔 nums의 순서대로 새로운 원소가 들어오게 됨
    이를 pivot보다 작은 쪽이 완성될때까지 반복함
    그리고 마지막으로 pivot과 동일한 쪽이 완성되도록 밀어내기를 수행함
     ㄴ 이는 처리가 되지 않은 오른쪽 구역과 수행함
    
    실행 결과, 2794ms(over 5.39%), 128MB(over 78.20%)
    물론 공간복잡도 O(1)을 목표하였기에 풀이1보다 느린 것은 당연함
     ㄴ 정확한 시간복잡도를 알기 어렵지만 O(n^2)일 것
     ㄴ 그래도 대충 n^2/2수준까진 되지 않을까 생각함
    하지만 swap이 확실히 최초의 접근이었던 단순 밀어내기 방식보다 덜 발생하는 것으로 분석됨
    우선 오른쪽 구역은 최소한의 swap만을 통해 구성됨
    그리고 의사-큐 덕분에 밀어내야할 거리도 크게 줄어듦
     ㄴ 덧붙여 높은 지역성도 가져갈 수 있음
    
    실제 테스트 케이스 중 제일 긴 것(10^5)으로 테스트해본 결과, swap 횟수는 아래와 같았음
    단순 밀어내기 : 1,255,205,602번
    의사-큐 : 418,478,943번
    약 1/3 정도로 swap이 줄어든 것을 확인할 수 있었음
*/

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        const int n = nums.size();
        int countSame = 0;
        int countLess = 0;
        int countGreater = 0;
        int lEnd = 0;

        for (auto num : nums)
        {
            if (num == pivot)
                countSame++;
            else
            {
                if (num < pivot)
                    countLess++;
                else
                    countGreater++;
            }
        }
        
        int endM = n - countGreater - 1;
        int endR = n - countGreater;
        int queueSize = countLess + countSame;
        int queuePtr = 0;

        for (int i=0; i<countLess; ++i)
        {            
            while(true)
            {
                if (queuePtr >= i+queueSize)
                    queuePtr = i;
                
                if (nums[queuePtr] < pivot)
                {
                    // push to front
                    for (int j=queuePtr; j>i; j--)
                        swap(nums[j],nums[j-1]);

                    queueSize--;
                    queuePtr++;
                    break;
                }
                else if (nums[queuePtr] == pivot)
                {
                    // push to back
                    for (int j=queuePtr; j<endM; j++)
                        swap(nums[j],nums[j+1]);

                    queueSize--;
                    endM--;
                }
                else
                {
                    swap(nums[queuePtr],nums[endR]);
                    endR++;
                    queuePtr++;
                }
            }
        }

        for (int i=countLess; i<=endM; ++i)
        {
            if (nums[i] == pivot) continue;

            for (int j=endR; j<n; ++j)
            {
                swap(nums[i], nums[j]);
                if (nums[i] == pivot)
                    break;
            }
            endR++;
        }
        
        return nums;
    }
};
int main()
{
    Solution s;

    vector<int> v = {4,0,4,5,-11};

    s.pivotArray(v,5);

    return 0;
}