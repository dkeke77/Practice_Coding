#include <iostream>
#include <array>
#include <queue>

using namespace std;

/*
    두 좌표값 A,B를 주고 아래 조건에 따랐을 경우 A에서 B까지의 최단시간을 묻는 문제
    현재 좌표 x에서 x+-1 이동은 1초 추가, x*2 이동은 0초

    최단 경로를 묻는 문제인만큼 BFS를 적용하면 좋음
    DP는 점화식 세우기도 복잡하고, 한방향으로만 배열을 순회하는 것이 아니라서 부적절
    DFS는 모든 케이스를 확인하기엔 N이 너무 큼 -> 가지치기 안한다면 3^N

    코드는 bfs를 위한 방문큐와 최단시간을 저장을 배열을 기준으로 작동함
    범위를 벗어나거나 굳이 확인할 필요없을 경우(목표를 지나쳤는데 +1 이동)는 무시하도록 함
    만약 그렇지 않다면 현재 위치에서 2배 이동 혹은 +-1 이동한 결과와 최단시간 배열에 저장된 결과를 비교
    현재 위치에서 이동했을때 더 짧다면 해당 값으로 대체하고 방문에 큐에 이동한 위치를 추가

    처음에 curIndex 조건 검사때문에 버그가 많이 났었음
    범위체크 잘못했거나, 굳이 체크 안해도 되는걸 체크했거나...

    GPT한테도 물어봤는데 deque 쓰는걸 추천했음
    0배 이동은 덱 앞에, +-1 이동은 덱 뒤에 추가하고 방문은 덱 앞에서 먼저 하는 방식
    0배 이동이 불필요하게 많아져서 꺼려졌으나 0배 이동은 최악의 경우 logN번만큼 수행되기에
    크게 문제되는 사항은 아니었음
    또한 그 결과 진짜 가까운 거리부터 수행하기에 bfs에 더 가깝게 구현되는 것으로 보임
    그리고 어차피 같은 인덱스에 여러번 방문하지 않기 때문에 O(N)으로 끝나는 신묘함을 보임
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    int N,K,curIndex;

    cin >> N >> K;

    array<int,100001> minTime;
    fill(minTime.begin(),minTime.end(),INT32_MAX);
    queue<int> toVisit;

    toVisit.push(N);
    minTime[N] = 0;

    while (!toVisit.empty())
    {
        curIndex = toVisit.front();
        toVisit.pop();

        if(curIndex <= 50000 && curIndex != 0)
        {
            if (minTime[curIndex*2] > minTime[curIndex])
            {
                minTime[curIndex*2] = minTime[curIndex];
                toVisit.push(curIndex*2);
            }
        }
        if(curIndex > 0)
        {
            if (minTime[curIndex-1] > minTime[curIndex]+1)
            {
                minTime[curIndex-1] = minTime[curIndex]+1;
                toVisit.push(curIndex-1);                
            }
        }
        if(curIndex < 100000 && curIndex<K)
        {
            if (minTime[curIndex+1] > minTime[curIndex]+1)
            {
                minTime[curIndex+1] = minTime[curIndex]+1;
                toVisit.push(curIndex+1);                
            }
        }
    }
    cout << minTime[K];

    return 0;
}