#include <vector>
#include <iostream>

using namespace std;

/*
@성공1
    처음엔 입력되는 연결리스트에 대해 수정을 하면 안된다고 생각하였음
    함수의 반환타입이 void가 아닌 점, 그리고 연결리스트가 포인터로 들어오기 때문이었음
    그래서 연결리스트를 순회하며 길이를 재는 동시에, 연결리스트의 값을 벡터에 저장하도록 함
    그리고 새로운 연결리스틀 만들어서 반환함
    이 때, 입력값 k에 따라 인덱스에 값을 더하여 벡터를 참조하도록 함
    0ms(over 100%), 16.6MB(over 31.20%)가 나옴
    이 방식의 시간복잡도는 O(n) (리스트 2번 순회)로 계산됨
    그러나 공간복잡도는 O(n)으로 예상됨

@성공2
    이렇게 연결리스트를 주는 문제들은 입력으로 들어오는 연결리스트를 수정해도 문제없다고 함
    따라서 주어진 연결리스트를 수정하는 방법을 사용함
    마찬가지로 연결리스트 순회하여 길이를 알아내고, 순회 후 마지막 노드와 시작 노드를 연결함
    그리고 필요한만큼 다시 연결리스트를 순회함
    순회 종료 후, 직전 노드와 현재 노드의 연결을 끊고 현재 노드를 반환함
    0ms(over 100%), 16.4MB(over 31.20%)가 나옴
    이 방식도 시간복잡도는 O(n)으로 나오지만, 이전 방식보단 미세하게 빠름
     ㄴ 마지막 순회를 리스트 마지막까지 완전히 하는 것은 아니기 때문
    그리고 공간복잡도는 O(1)으로 예상됨
    하지만 직전 방식과 비교해서 실제 차이는 별로 안 나는데, 이는 leetcode 실행환경 때문으로 예상됨

@실수
    포인터를 다룸에 있어 몇가지 실수가 있었음
    1) 범위를 벗어난 리스트 포인터
        순회 후, 포인터가 nullptr가 된다는 사실을 놓친 바람에 nullptr exception이 발생함
        대표적으로 nullptr가 되어, 더 이상 가리키는 노드가 없는 상태임에도 노드와 관련된 작업을 수행하는 경우,
        노드 주소가 있는 것으로 착각하고 다른 포인터에 할당하는 경우 등이 있었음
    2) 초기화 되지 않은 포인터 사용
        초기화된 것으로 오인하고 해당 포인터를 다른 포인터에게 복사하려고 했음
        이 때, 해당 포인터는 "껍데기만 있는" 상태이기 때문에, 복사 시 넘겨주어야할 주소값이 없어 에러가 발생함
        그런데 특이한 점은 해당 에러 시, 빨간 밑줄이 복사를 받는 포인터의 정의문 쪽에 쳐짐
        이 때문에 원인을 찾아내는 데 다소 시간이 걸림
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int length = 0;
        ListNode* currNode = head;
        ListNode* prevNode = head;
        
        while(currNode != nullptr)
        {
            length++;
            prevNode = currNode;
            currNode = currNode->next;
        }

        if (length == 0)
            return nullptr;

        prevNode->next = head;
        currNode = head;

        int offset = length - (k % length);
        
        for (int i = 0; i < offset % length; ++i)
        {
            prevNode = currNode;
            currNode = currNode->next;
        }

        prevNode->next = nullptr;

        return currNode;
    }
};

int main()
{


    return 0;
};