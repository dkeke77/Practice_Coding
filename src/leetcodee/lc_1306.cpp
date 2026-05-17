#include <vector>
#include <iostream>
#include <queue>

using namespace std;

/*
@접근
    이 문제는 최대 입력 길이가 5*10^4이기 때문에 O(n)이어도 됨
    따라서 BFS를 통해 이동 가능한 노드로 순회하는 것에 문제가 없음
    동시에 각 원소를 동시에 여러번 방문하지 않음
     ㄴ 방문하는 노드에 거리, 비용 같은 상태가 없기 때문
    때문에 최대 발생 가능한 방문 큐 크기 또한 입력 길이를 넘어서지 않음
    예상 시간 복잡도 O(n)
    실행 결과, 0ms(over 100%), 35MB(over 85.60%)가 나옴
    어떤 트릭이나 기법도 필요없는 단순한 BFS/DFS 문제였음
*/

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        const int n = arr.size();

        vector<bool> isVisited(n,false);
        queue<int> toVisit;

        toVisit.push(start);
        isVisited[start] = true;

        while(!toVisit.empty())
        {
            int curVisit = toVisit.front();
            toVisit.pop();

            if (arr[curVisit] == 0)
                return true;

            int nextL = curVisit - arr[curVisit];
            int nextR = curVisit + arr[curVisit];

            if (nextL >= 0 && !isVisited[nextL])
            {
                toVisit.push(nextL);
                isVisited[nextL] = true;
            }

            if (nextR < n && !isVisited[nextR])
            {
                toVisit.push(nextR);
                isVisited[nextR] = true;
            }
        }

        return false;
    }
};

int main()
{
    Solution s;

    vector<int> v = {4,5,6,7,8,9,0,1,2};

    return 0;
}