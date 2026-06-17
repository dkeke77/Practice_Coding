#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    어제 다뤘던 slow/fast 방법을 이용하면 된다고 봄
    하지만 리스트가 짝수 길이라는 보장이 없기 때문에, while에서 fast에 대한 조건을 하나 더 추가해야함
    또한 길이가 1인 경우엔 따로 처리를 해줘야 하는데, 이 경우엔 중간 노드인 head를 delete하면 안됨
     ㄴ 함수 외부에서 delete head를 호출하는 것으로 보임
     ㄴ 때문에 매개변수로 들어왔던 head 자체가 delete되면, 이후에 double free가 발생
    실행 결과, 0ms(over 100%), 312MB(over 83.64%)
    덧붙여, delete 연산이 실행 시간에 영향이 있나 확인해보았지만 영향은 거의 없었던 것으로 보임
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
    ListNode* deleteMiddle(ListNode* head) {
        if (head->next == nullptr)
            return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = head;

        while(fast != nullptr && fast->next != nullptr)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        prev->next = slow->next;
        delete slow;

        return head;
    }
};

int main()
{
    Solution s;

    return 0;
}