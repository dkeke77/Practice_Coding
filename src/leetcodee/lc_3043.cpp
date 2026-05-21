#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

/*
@접근
    단순 브루트 포스는 최대 10^9만큼 걸리기 때문에 적절치 않아보임
    개인적으론 트리로 구성하면 좋겠단 생각이 들음
     ㄴ x에 대한 트리를 만들고, y로 이를 방문하면서 최대 방문 깊이를 계산하기
     ㄴ x보다 y가 더 길더라도 상관없이 두 수의 공통 prefix를 찾는 것이므로 상관없음
    예상 시간 복잡도는 O(n+mlogn) : 트리 구성(n) + 트리 순회 횟수(m) * 트리 깊이(logn)
     ㄴ 즉, 최대 대략 5*10^5 정도
    그런데 꼭 노드여야할까?
    어차피 최대 자릿수가 8면, 9*10 bool 행렬에 어떤 수가 어느 자리에서 등장했었는지만 적으면 되지 않을까?
    하지만 139, 26과 같은 상황에서 등장도 안한 269가 있다고 판단해버릴 수 있음
    즉, 수에 대한 정보가 전부 합져쳐서 구분이 되지 않게 됨
    대신 bool 대신 비트마스크를 넣자
    하지만 실패함
    중간 노드가 공유될 수 있다고 판단했지만, 이는 잘못된 판단이었음
     ㄴ 123, 92 같은 경우, 2 노드가 공유됨
     ㄴ 그리고 해당 노드에서 3으로 뻗어나갈 수 있기에, 923가 있다고 판단해버릴 수 있음
    즉, 각 노드는 부모가 하나뿐이어야함
    해시를 이용하여 트리를 구현함
    키는 실제 prefix로써 구성하게 함
    실행 결과, 565ms(over 6.83%), 437MB(over 5.16%)가 나옴
    아무래도 해시라서 지역성과 버킷 생성 비용 문제가 있는듯

@개선
    따라서 해시를 배제하고 트리를 직접 구현하였음
    크기 10인 포인터 배열을 가진 Node 구조체를 통해 트리를 구성함
    그 결과, 543ms(over 8.16%), 481MB(over 5.16%)가 나옴
    
    혹시 new를 통해 힙 메모리를 할당받는 방식 자체가 느릴 수 있으므로, 벡터를 이용하도록 함
    미리 큰 벡터를 예약하고 여기에 노드들을 채워 넣도록 함
    노드엔 주소값이 아닌 벡터의 인덱스를 저장하여 해당 노드에 접근 가능하도록 함
    그럼에도, 459ms(over 10.33%), 377MB(over 5.16%)가 나옴
    즉, 문제는 트리의 표현 방식이 아니라는 결론에 도달함

    진짜 원인은 스택을 이용한 prefix 처리에 있었음
    매번 스택이 할당되고 제거되는 비용이 적지 않았던 것으로 파악됨
    따라서 스택 방식이 아니라 제일 큰 자릿수에 해당하는 10 제곱을 가져오도록 함
    그 결과, 34ms(over 100%), 134MB(over 98.50%)가 나옴

    혹시 몰라 제일 처음 성공했던 해시 방식에 다음 두 방식을 실험해봄
    stack을 재활용하는 방식 : 207ms(over 47.83%), 133MB(over 98.50%)
    자릿수 방식 : 95ms(over 99.17%), 118MB(over 99.50%)
    이를 통해 stack을 매번 재생성하는 비용이 꽤 컸던 것으로 분석됨
    그리고 stack에 잦은 입출입으로 인해, 적지 않은 비용이 발생했던 것으로 생각됨
     ㄴ 최대 8*10^5번 "입력"이 발생함. 출력까지 생각하면 저것의 2배일 것
    또한 양쪽에서 동일하게 큰 메모리 사용량 감소를 확인할 수 있었음
    이를 토앻 잦은 재생성이 메모리 사용량에도 영향을 준다는 결론을 내릴 수 있음
    
    마지막으로 포인터 배열을 이용한 트리 방식에서 stack 대신 자릿수 방식을 적용해봄
    그 결과, 72ms(over 99.50%), 160MB(over 54.00%)가 나옴
    역시나 성능과 메모리 전반에서 큰 개선을 보였음
    하지만 힙 메모리를 할당받는 것은 벡터보다 느린다는 사실 또한 다시 확인할 수 있었음
    혹은 벡터가 지역성이 더 높기 때문에 캐시 히트율이 높아졌다고도 생각할 수 있음
*/

struct Node
{
    Node* child[10] = {};
};

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int answer = 0;

        Node head;

        for (auto i : arr1)
        {
            int key = 0;
            int maxDigit = getDigit(i);
            Node* treePtr = &head;

            while(maxDigit != 0)
            {
                int curNum = i / maxDigit; 
                if (treePtr->child[curNum] == nullptr)
                    treePtr->child[curNum] = new Node;
                treePtr = treePtr->child[curNum];
                
                i %= maxDigit;
                maxDigit /= 10;
            }
        }
        
        for (auto i : arr2)
        {
            int digit = 0;
            int maxDigit = getDigit(i);
            Node* treePtr = &head;

            while(maxDigit != 0)
            {
                int curNum = i / maxDigit; 
                auto& chld = treePtr->child[curNum];
                if (chld == nullptr)
                    break;
                digit++;
                treePtr = chld;
                
                i %= maxDigit;
                maxDigit /= 10;
            }
            answer = max(answer, digit);
        }

        return answer;
    }
private:
    int getDigit(int num)
    {
        int result = 1;
        while(result <= num)
            result *= 10;

        return result/10;
    }
};

int main()
{
    Solution s;
    vector<int> a = {123,7089};
    s.longestCommonPrefix(a,a);

    return 0;
}