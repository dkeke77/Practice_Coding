#include <iostream>
#include <vector>

#define INF 100000001


using namespace std;

/*
    플로이드 와셜 알고리즘 문제
    어찌 보면 DP인 그런 알고리즘임
    j->k로 갈때 i를 경유하는게 좋을지 계속 추가하며 평가하는 알고리즘

    근데 여러 부분에서 미흡한 곳이 보였음

    1. INF 설정
    INF를 설정할때 단순히 INT32_MAX를 쓰니 둘이 더하니 오버플로우가 남
    그래서 cost의 최댓값+1인 100001로 했는데 깊게 생각을 안했었음
    저 cost는 입력으로 주어질 수 있는 최댓값이고, 결과의 최댓값은 이니었음.
    따라서 입력의 최댓값 * 최대방문도시개수로 생각하여 100000*99를 최대라고 생각하고,
    저것보다 큰 값을 INF로 했어야했음

    2. 답 출력 방식
    INF면 0을 출력해야되는데, 진짜로 INF를 출력함
    문제 제대로 읽어보자
    실전에서는 질문게시판 못 쓴다

    별개로 1e6과 같이 10^6를 지수표기법을 사용할 수 있었음
    단위가 큰 것들을 다룰때 유용할 것
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N, M, city1, city2, cost;
    cin >> N >> M;

    vector<vector<int>> tb(N,vector<int>(N,INF));

    for (int i=0; i<N; i++)
        tb[i][i] = 0;

    for(int i=0; i<M; i++)
    {
        cin >> city1 >> city2 >> cost;

        if(tb[city1-1][city2-1] > cost)
            tb[city1-1][city2-1] = cost;
    }

    for (int i=0; i<N; i++)    
    {
        for (int j=0; j<N; j++)
        {
            if (j==i) continue;
            for (int k=0; k<N; k++)
            {
                if(k==j || k==i) continue;

                if(tb[j][k] > tb[j][i]+tb[i][k])
                    tb[j][k] = tb[j][i]+tb[i][k];

                if(tb[j][k]>INF) tb[j][k]=INF;
            }
        }
    }

    for (auto elemVec : tb)
    {
        for (auto elem : elemVec)
        {
            if (elem == INF)
                cout << "0 ";
            else
                cout << elem << " ";
        }
            
        cout << '\n';
    }

    return 0;
}