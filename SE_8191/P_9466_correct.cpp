#include <iostream>
#include <vector>
#include <stack>

#define UNBINDED -1
#define NOVISITED 0
#define BINDED 1

using namespace std;

/*
    사이클을 이루는 그래프와 그렇지 못한 노드를 구분하는 문제
    각 노드가 다른 노드로 향하는 간선을 하나만 표현
    따라서 간선을 따라가며 방문한 노드는 표시하고
    만약 이미 방문한 노드가 다시 나온다면 사이클이 형성된 것
    하지만 모든 노드가 사이클이 형성된 것은 아님 -> 경로의 중간부터 형성된 것일수도 있음
    따라서 사이클이 형성되기 시작한 노드가 나올때까지 방문리스트를 역으로 순회
    그리고 사이클이 형성되지 않은 노드는 앞으로의 루프에서 제외

    다른 사람들의 코드를 보면 더 빠르게 만들 수 있을것 같지만 너무 귀찮아...
    420ms에서 620ms로 극단적으로 차이나는건 아니니까 일단 이 문제는 여기서 마무리
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int T, N, input, result;
    int curIdx, nextIdx;
    cin >> T;

    vector<int> choice;
    vector<int> visitList;
    vector<int> binded;
    vector<bool> visited;

    while(T--)
    {
        cin >> N;

        result = 0;
        choice = vector<int>(N+1);
        binded = vector<int>(N+1,0);

        for(int i=1; i<=N; i++)
            cin >> choice[i];

        for(int i=1; i<=N; i++)
        {
            if (binded[i] != NOVISITED)
                continue;

            visitList.push_back(i);
            visited = vector<bool>(N+1, false);
            visited[i] = true;
            
            while(!visitList.empty())
            {
                nextIdx = choice[visitList.back()];

                // Foward travel
                if(!visited[nextIdx] && binded[nextIdx] == NOVISITED)
                {
                    visitList.push_back(nextIdx);
                    visited[nextIdx] = true;
                    continue;
                }
                
                // Backward travel
                if(visited[nextIdx])
                {
                    while(visitList.back() != nextIdx)
                    {
                        binded[visitList.back()] = BINDED;
                        visitList.pop_back();
                    }
                    binded[nextIdx] = BINDED;
                    visitList.pop_back();
                }
                if(visitList.size() > 0)
                {
                    while(!visitList.empty())
                    {
                        binded[visitList.back()] = UNBINDED;
                        visitList.pop_back();
                    }
                }
            }
        }

        for(auto elem : binded)
        {
            if(elem == UNBINDED)
                result++;
        }

        cout << result << '\n';
    }

    return 0;
}