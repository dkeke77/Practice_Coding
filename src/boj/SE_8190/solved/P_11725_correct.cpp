#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
    노드들간 연결 정보만 알려주고 각 노드의 부모를 알아내는 문제
    DFS든 BFS든 구현가능하지만 이번에는 BFS 써봄
    
    처음에는 간선을 저장하는 edges를 map으로 했었는데 100ms로 느리게 나옴
    하지만 이중 vector로 바꾸니 48ms로 엄청 짧아짐
    1,2번 정도만 접근할거면 map보단 이중 vector가 더 나을지도?
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int cntNode;
    cin >> cntNode;

    vector<vector<int>> edges(cntNode+1);
    vector<int> parent(cntNode+1,0);
    queue<int> toVisit;
    
    int input1, input2;
    for(int i=0; i<cntNode-1; i++)
    {
        cin >> input1 >> input2;
        
        edges[input1].push_back(input2);
        edges[input2].push_back(input1);
    }

    int curNode;
    toVisit.push(1);
    while(!toVisit.empty())
    {
        curNode = toVisit.front();
        toVisit.pop();

        for (auto i : edges[curNode])
        {
            if(parent[i] == 0)
            {
                toVisit.push(i);
                parent[i] = curNode;
            }
        }
    }

    for (int i=2; i<=cntNode;i++)
        cout << parent[i] << '\n';
    
    return 0;
}

