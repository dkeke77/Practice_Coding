#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근1
    이 문제 풀이 자체는 굉장히 단순함
    전체 순회를 하며 배열에 리스트값을 저장하고, 이 배열을 순회하며 최댓값을 계산하면 됨
    시간복잡도는 O(n) : 2n, 공간복잡도는 O(n)
    실행 결과, 2ms(over 70.05%), 129MB(over 38.11%)

@접근2
    하지만 공간복잡도 O(1)로 구현하는 것은 보다 더 어려움
    이 리스트는 이전 노드를 가르키지 않는 단방향 리스트임
    따라서 이전 노드로 돌아가는 방법은 오직 head에서부터 순회하는 것뿐임
     ㄴ 이는 매번 시간복잡도 O(n)을 요구함
    그러니 이전 노드로 돌아가기 위해 매번 head에서부터 돌아가는 것은 비효율적임
    
    분할정복을 써보는건 어떨까?
    구간을 길이 k로 나눴다고 가정하자
    그러면 양쪽 부분 구간에서 최댓값 계산을 위해 한쪽이 순환적 순회(k^2/2)를 하고, 반대편은 일반 순회(k)를 할것
     ㄴ 순환적 순회란, 직전 노드로 가기 위해 구간 제일 앞으로 회귀하여 순회한다는 의미로 씀
    그러면 해당 부분 구간들에선 k^2/2+k가 발생하며, 이는 n/2k번 발생
    즉, 최종적으론 n/2+n*k/4가 발생
    하지만 재귀를 이용해선 안되므로, 순환적 순회 구간의 정보(시작 노드, 끝 노드)는 직접 찾아서 줄 수밖에 없음
    시작노드만 필요하다는 가정 하에, 이 또한 n^2/4k만큼 필요할 것으로 예상됨
     ㄴ 이 계산이 정확한진 모르겠음
    이 방식도 결국 O(n^2)을 벗어날순 없음
     ㄴ 순수 순환 순회보단 빠르겠지만....
    예상대로 TLE 발생

    힌트에 의하면 연결리스트를 직접 반전시키는 방법을 얘기함
    아무래도 오른쪽 구간의 next를 반대로 만드는 것을 의미하는 것으로 보임
    이에 따라 prev, cur, next를 저장하며, cur->next가 prev이도록 수정하며 순회하는 코드를 구현함
    그리고 마지막엔 원래 리스트 형태로 원상복구시키도록 함
     ㄴ 이 때, 왼쪽 구간과 오른쪽 구간을 연결시키고, 제일 오른쪽 노드의 next가 nullptr이도록 해야함
     ㄴ 단 이 방법은 리스트가 어느 정도 길때만 시행하도록 함
    시간 복잡도는 O(n) : 3n
    실행 결과, 4ms(over 56.67%), 128MB(over 38.55%)
    의외로 메모리 사용량이 줄진 않음
     ㄴ 아무래도 leetcode 채점 시스템이 노드 반전 과정을 메모리 사용으로 인식해버린듯
    
    다른 풀이들에선 이렇게 복잡하게 하진 않고 slow,fast,prev 포인터를 이용하여 구현함
    slow는 next를 1칸씩, fast는 next를 2칸씩 이동함
    prev는 slow의 이전을 저장함
    fast가 nullptr에 닿기 전까지 루프를 반복하는데, fast는 2칸씩 이동하므로 slow는 정확히 리스트의 중간에서 멈춤
    그리고 이 과정에서 slow의 next를 prev로 바꿈
     ㄴ 바꾸기 전엔 temp에 진짜 next를 미리 저장
    그 결과, 왼쪽 구간이 반전된 형태를 띄게 됨
    이 코드들에선 원상복구하는 코드가 없었음
     ㄴ 아무래도 원상복구를 하지 않아도 됐던 것으로 보이나, 원상복구는 여러 측면에서 하는 것이 맞다고 생각함
    또한 해당 코드들에서도 메모리 소모는 차이가 없었음
    하지만 해당 방식으로 구현하면 더 간단한 형태로 구현할 수 있다는 장점이 있음
    구현 결과, 0ms(over 100%), 128MB(over 41.54%)
    길이를 구하는 과정, 그리고 반전 과정이 간결해진 덕분에 더 빨라진 것으로 보임
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
    int pairSum(ListNode* head) {
        int maxSum = 0;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;

        while(fast != nullptr)
        {
            fast = fast->next->next;
            ListNode* temp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = temp;
        }

        ListNode* rEnd = prev;
        ListNode* rNext = slow;

        while(slow != nullptr)
        {
            maxSum = max(maxSum, slow->val+prev->val);
            
            slow = slow->next;
            prev = prev->next;

            // For restore
            rEnd->next = rNext;
            rNext = rEnd;
            rEnd = prev;
        }

        return maxSum;
    }
};
int main()
{
    Solution s;

    return 0;
}