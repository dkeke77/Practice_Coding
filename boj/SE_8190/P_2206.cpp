#include <iostream>
#include <vector>
#include <queue>

#define INF 1e7
using namespace std;

struct Grid
{
    int u,v;
    int dist;
    bool wallCrashed;
};


int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N,M,dist;
    bool reachedDest = false;
    string input;

    cin >> N >> M;
    vector<vector<int>> map(N,vector<int>(M));

    for (int i=0; i<N; ++i)
    {
        cin >> input;
        for (int j=0; j<M; ++j)
        {
            map[i][j] = int(input[j])-48;
        }
    }

    vector<vector<bool>> visited(N,vector<bool>(M, false));
    queue<Grid> toVisit;

    toVisit.push(Grid{0,0,1,false});

    while(!toVisit.empty())
    {
        auto curGrid = toVisit.front();
        toVisit.pop();
        visited[curGrid.u][curGrid.v] = true;

        if (curGrid.u == N-1 && curGrid.v == M-1)
        {
            reachedDest = true;
            dist = curGrid.dist;
            break;
        }

        for (const auto& move : {pair<int,int>{0,-1}, {0,1}, {-1,0}, {1,0}})
        {
            int uNext = curGrid.u + move.first;
            int vNext = curGrid.v + move.second;
            if (uNext < 0 || uNext >= N) continue;
            if (vNext < 0 || vNext >= M) continue;
            if (visited[uNext][vNext]) continue;

            if (map[uNext][vNext] == 1)
            {
                if (curGrid.wallCrashed)
                    continue;
                else
                    toVisit.push(Grid{uNext,vNext,curGrid.dist+1,true});
            }
            else
                toVisit.push(Grid{uNext,vNext,curGrid.dist+1,curGrid.wallCrashed});
        }
    }

    if (reachedDest)
        cout << dist;
    else
        cout << -1;

    return 0;
}