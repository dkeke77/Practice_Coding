#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

/*
@접근
    BFS를 쓰며, 점프할 수 있는 다른 인덱스들을 알려주는 해시를 마련
    시간복잡도 대략 O(n) : n+n 걸릴 것으로 예상
     ㄴ 해시 생성 때문에 보기보다 더 걸릴 수도 있음
    실행 결과, 62ms(over 98.95%), 77MB(over 72.55%)
    불필요한 해시(사이즈가 1인 것들)를 정리할 수 있다면 더 좋을듯
    하지만 정리에 n이 필요하고, 정리한다고 하여도 얻을 수 있는 이익은 메모리 절약 정도밖에 없음
    그러나 어떤 방법으로도 1번만 등장하는 숫자에 대해 기록을 피할 수 없음
    따라서 이 방법이 제일 최적이라고 생각함

    다른 풀이 중엔, 배열을 이용한 연결리스트 방식도 있었음
    나도 이를 적용할까 했었지만, 연결리스트 중간부터 순회할 가능성과,
    그리고 이미 방문하여 더 이상 사용하지 않는 연결리스트 노드들에 대한 처리가 복잡하고 비싸다고 판단했음
     ㄴ 노드 방문하면서 초기화를 시키는 방식
    그러나 해당 풀이 작성자에 따르면 33ms로 훨씬 빠르다는 것을 알 수 있음
    아무래도 중간부터 순회할 가능성에 대해선 걱정할 필요가 없었다고 생각됨
    해시로 연결리스트의 헤드만 가르키게 하고, 연결리스트 사용 후엔, 해당 해시 버킷을 삭제하면 됨

    그런데 꼭 해시를 사용할 필요도 없긴 하지만, 그 방법을 위해선 숫자 범위 만큼의 배열을 필요로 함
    결국 해당 숫자에 대한 노드가 이전에 몇번이었는지 파악해야하기 때문
*/

class Solution {
public:
    int minJumps(vector<int>& arr) {
        const int MAX_DIST = 1e5;
        const int n = arr.size();
        vector<int> dist(n,MAX_DIST);
        unordered_map<int,vector<int>> sameNumIdx;

        for (int i = 0; i < n; ++i)
            sameNumIdx[arr[i]].push_back(i);

        queue<int> toVisit;
        toVisit.push(0);
        dist[0] = 0;

        while(!toVisit.empty())
        {
            int curIdx = toVisit.front();
            toVisit.pop();

            if (curIdx > 0 && dist[curIdx-1] == MAX_DIST)
            {
                dist[curIdx-1] = dist[curIdx]+1;
                toVisit.push(curIdx-1);
            }
            if (curIdx < n-1 && dist[curIdx+1] == MAX_DIST)
            {
                dist[curIdx+1] = dist[curIdx]+1;
                toVisit.push(curIdx+1);
            }

            if (sameNumIdx[arr[curIdx]].size() > 1)
            {
                for (const auto& idx : sameNumIdx[arr[curIdx]])
                {
                    if (dist[idx] == MAX_DIST)
                    {
                        dist[idx] = dist[curIdx]+1;
                        toVisit.push(idx);
                    }
                }
                sameNumIdx[arr[curIdx]] = {0};
            }

            if (dist.back() != MAX_DIST) break;
        }

        return dist.back();
    }
};

int main()
{
    Solution s;



    return 0;
}