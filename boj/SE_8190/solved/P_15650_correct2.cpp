#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
    백트래킹으로 풀 수도 있다는 얘기를 듣고 백트래킹으로 구현해서 풀어봄
    stack을 이용하여 구혆함
    내림차순을 고려해서 방문할 노드들을 역순으로 넣음
    깊이가 M이 되면 출력용 벡터를 출력함
    그리고 현재 노드가 더 없다고 판단되면 pop하는걸 반복
    판단방법은 각 깊이별 가능한 최대값과 비교
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N,M;
    cin >> N >> M;
    vector<int> output;
    stack<int> dfs;
    
    for(int i=N-(M-1); i>0; i--)
        dfs.push(i);
    
    while (!dfs.empty())
    {
        // Pop Child
        output.push_back(dfs.top());
        dfs.pop();

        if(output.size()==M)
        {
            for(auto elem : output)
                cout << elem << " ";
            cout << '\n';

            int preChild;
            do
            {
                preChild = output.back();
                output.pop_back();
            } while (!output.empty() && (preChild == N - (M-output.size()-1)));
        }
        else
        {
            // Push child
            for(int i=N-(M-output.size()-1); i>output.back(); i--)
                dfs.push(i);
        }
    }
}
