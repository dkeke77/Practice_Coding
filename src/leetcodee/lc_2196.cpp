#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

/*
@풀이
    언제 어떤 노드가 들어올지 알 수 없으니, 이전에 처리한 노드를 저장하고 있어야 함
     ㄴ 결과물인 트리는 모든 노드가 연결되지만, 결과 완성 이전엔 연결되지 않은 부분트리들이 있을 수 있음
    이에 적합한 것은 우선 해시임
    해시로 부모와 자식 모두 해시에 저장하고 인출하는 방법이 적절함
    만약 해시에 없다면 새로 만들고, 있다면 그대로 인출하면 됨
    그리고 루트 노드를 추적해야할 필요가 있음
    처음엔 desc를 읽으며 현재 루트로 추정하는 노드가 자식으로 등장하면 해당 자식의 부모를 루트로 변경했음
    그러나 이 방법은 새로 등장한 부모가 이전에 자식으로 등장했었다면 잘못될 수 있음
    따라서 배열로 연결리스트를 만들고, 자식이 부모 인덱스를 가르키게 해야함
    desc를 전부 읽은 후, 연결리스트에서 부모 인덱스를 연쇄적으로 읽도록 함
    거기서 더 부모 인덱스가 없다면, 해당 인덱스가 루트임
    실행 결과, 131ms(over 89.88%), 298MB(over 19.51%)
    여기서 실행 속도를 더 증가시키려면 해시를 벡터를 대체하면 됨
    대체 결과, 70ms(over 93.59%), 348MB(over 5.12%)

    그러나 의외로 많은 메모리를 사용하게 되는데, 이는 함수 내부에서 벡터를 선언 및 정의하기 때문임
    그렇기에 매 함수 호출마다 새로운 벡터를 선언 및 정의하면서 발생하는 오버헤드 및 메모리가 적지 않을 것임
    따라서 함수 외부(즉, 클래스 멤버)에 선언 및 정의하고, 함수 종료 시 이를 초기화하기만 하면 됨
    트리를 순회하면서 이를 초기화하면 낭비없이 초기화가 가능하다고 봄
    개선 후, 57ms(over 93.73%), 239MB(over 93.45%)
    예상대로 양쪽 모두 더 좋은 수치를 보였으며, 특히 메모리는 큰 향상이 있었음

    혹은 등장한 노드번호 중 최소/최대를 구하고, 이 구간의 모든 원소를 초기화할 수도 있음
    이 방식은 초기화하지 않아도 될 것들을 초기화할 수도 있지만, 어쩌면 이쪽이 더 빠를 수도 있음
    캐시 히트율 문제뿐만 아니라 큐/스택 관리비용 때문도 있음
    변경 후, 34ms(over 95.30%), 235MB(over 94.02%)
    예상대로 실행속도가 더 빨라졌음
    여기서 더 나아가 큐를 배열로 구현하는 방법도 있으나, 거기까지는 하지 않기로 함
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int headTrack[100'001] = {};
    TreeNode* nodes[100'001] = {};

    TreeNode* getNodeFromMap(int target)
    {
        if (nodes[target] == nullptr)
            nodes[target] = new TreeNode(target);

        return nodes[target];
    }

    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        int root = descriptions[0][0];
        int minVal = 100'001;
        int maxVal = 0;
        
        for (const auto& desc : descriptions)
        {
            TreeNode* parentPtr = getNodeFromMap(desc[0]);
            TreeNode* childPtr = getNodeFromMap(desc[1]);

            if (desc[2] == 0)
                parentPtr->right = childPtr;
            else
                parentPtr->left = childPtr;

            headTrack[desc[1]] = desc[0];

            if (root == desc[1])
                root = desc[0];

            minVal = min(minVal, min(desc[0],desc[1]));
            maxVal = max(maxVal, max(desc[0],desc[1]));
        }

        while(headTrack[root] != 0)
            root = headTrack[root];

        TreeNode* rootPtr = nodes[root];

        for (int i = minVal; i<=maxVal; ++i)
        {
            headTrack[i] = 0;
            nodes[i] = nullptr;
        }

        return rootPtr;
    }
};

int main()
{
    Solution s;

    return 0;
}