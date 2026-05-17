#include <vector>
#include <iostream>

using namespace std;

/*
@접근
    이전 문제(153)처럼 배열에 2개의 서브 배열이 같이 있다고 접근하자
    그렇다면 중요한 것은 최소배열의 시작점을 찾아내는 것임
    이를 위해 2가지 방법을 고안했었음
    1) n[i-1]>n[i]를 만족하는 구간을 줄여나가기
    2) 고정점에서부터 길이 확장해나가기

    이번 문제는 이전과는 다르게 중복된 숫자가 있을 수 있단 점이 차이점
    때문에 기존 방법들은 사용에 제한이 있을 수 있음
     ㄴ n[ptrL] == n[ptrR]인 경우, 왼쪽과 오른쪽 중 어느쪽을 선택해야할지 결정할 수 없음
    같은 숫자들이 있는 구간 안에 어떤 숫자가 숨어있을 수 있음
     ㄴ 이를 간단히 bush라고 부르겠음
    이 bush는 2가지 종류가 있음
    배열 앞뒤를 감싸는 것과 그렇지 않은 것
    앞뒤를 감싸지 않는 bush는 가운데 어떤 숫자도 포함되지 않음
     ㄴ 이에 대한 증명은 생각보다 간단한데, 회전된 배열은 원본 배열의 중간을 잘라서 뒤에 이어붙인 것임
     ㄴ 즉, bush가 잘리지 않았다면 bush 내부엔 다른 숫자가 있을 수 없음
     ㄴ 하지만 bush가 잘렸다면 다른 숫자를 감싸는 형태가 되는 것임
    위 관찰에 따라 앞뒤의 bush를 제거하고, 기존 알고리즘을 재적용하면 됨

    현재 배열이 bush에 의해 감싸져 있다면, bush 제거를 수행하도록 함
    bush 제거는 단순히 ptrL과 ptrR을 각자 방향대로 1칸씩 전진시켜 구현함
    각 ptr은 bush와 다른 숫자가 나올때까지 전진함
    그런데 ptr이 서로를 넘겨버리는 경우가 발생했고, 이를 막기 위해 서로를 넘지 않도록 함
    그리고 제거한 bush가 배열의 최소인 경우도 존재했음
    따라서 이후에 return 시에 bush값과 최솟값 중 최소를 반환하게 함
     ㄴ bush는 최댓값 이상으로 초기화 -> 0같은걸로 하면 실제 최솟값을 숨겨버릴 수 있음
    실행 결과, 0ms(over 100%), 16MB(over 27.34%)가 나옴
     ㄴ 메모리는 70% 가량이 16.0~16.2MB에 분포되어 있으므로 신경쓸 지표는 아님

    bush 제거를 더 빠르게 할 수도 있을 것으로 생각됨
    1칸씩 전진하는 것이 아닌, 이진 탐색을 적용한다면 되지 않을까 싶음
    그런데 이진탐색 시, 잘못하면 중간에 숫자가 숨어있는 구간을 넘겨서 점프해버릴 수도 있음
    그러면 역으로 bush가 아닌 구간을 찾아내는건 어떨까?
     ㄴ 그렇다면 처음에 bush가 아닌 지점을 잡아야되지 않을까?
    bush가 아닌 지점을 안정적으로 찾을 방법은 mid에서부터 1칸씩 탐색해나가는 것뿐임
    또한 처음 선택한 지점이 운좋게 bush가 아니라면, 이전 구간에서 bush가 끝나는 지점을 찾아야함
    실행 결과, 0ms(over 100%), 16MB(over 63.69%)가 나옴
     ㄴ 3ms가 나오기도 했음
    평균 성능은 올라갈 수 있으나, 최악의 경우는 여전히 O(n)이 나올 수밖에 없음
    그리고 구조가 지나치게 복잡해져 구현이 어려워지는 측면이 있음
    또한 그로 인한 비용이 실제 성능 향상보다 높을 수도 있음

    다른 풀이에서도 끝단의 중복되는 숫자를 줄이는 것을 목표함
    그러나 한쪽 방향에서만 전진하는 것으로 짬
     ㄴ 왼쪽만 하던가, 혹은 오른쪽만 하던가
    다른 해법으로는 분할-정복법을 사용한 케이스도 있음
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int ptrR = nums.size()-1;
        int ptrL = 0;
        int mid = 0;
        int sameNum = 1e6;

        if (nums[ptrL] == nums[ptrR])
        {
            sameNum = nums[ptrL];
            int bushPtr = ptrL; 

            while(bushPtr < ptrR-1 && nums[ptrL] == sameNum)
            {
                ptrL = bushPtr;
                bushPtr = (ptrL + ptrR) / 2;
                for (int i = 0; i < bushPtr-ptrL+1; ++i)
                {
                    if(nums[bushPtr-i] != sameNum)
                    {
                        ptrL = bushPtr-i;
                        break;
                    }
                }
            }
            
            bushPtr = 0;
            while(bushPtr < ptrL)
            {
                mid = (bushPtr+ptrL) / 2;
                if (nums[mid] == sameNum)
                    bushPtr = mid+1;
                else
                    ptrL = mid;
            }

            bushPtr = ptrL;
            while(bushPtr < ptrR)
            {
                mid = (bushPtr+ptrR) / 2;
                if (nums[mid] == sameNum)
                    ptrR = mid;
                else
                    bushPtr = mid+1;
            }
        }
        
        while (nums[ptrL] > nums[ptrR])
        {
            mid = (ptrL+ptrR) / 2;

            if (nums[ptrL] > nums[mid])
                ptrR = mid;
            else
                ptrL = mid + 1;

        }

        return min(nums[ptrL],sameNum);
    }
};

int main()
{
    Solution s;

    vector<int> v = {4,5,6,7,8,9,0,1,2};

    cout << s.findMin(v) << endl;

    return 0;
}