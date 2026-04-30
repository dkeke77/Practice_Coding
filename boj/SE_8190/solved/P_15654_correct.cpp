#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
    15650번 풀었던거 그대로 가져가서 개조함
    dict 저장 및 정렬(버블)
    기존 dfs 로직에서 depth 처리 추가
    기존 제약 조건(숫자 크기 제한) 삭제
    그리고 중복없이 dfs 스택에 추가되도록 child 추가 전 dfs 탐색 로직 추가
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N,M;
    cin >> N >> M;
    vector<int> output;
    vector<int> depth(M,0);
    vector<int> dict;
    stack<int> dfs;

    // Input dict
    int input;
    for (int i=0; i<N; i++)
    {
        cin >> input;
        dict.push_back(input);
    }

    // Sort dict
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N-i-1; j++)
        {
            if(dict[j] > dict[j+1])
                swap(dict[j], dict[j+1]);
        }
    }
    
    // Push child of root
    for(int i=N-1; i>=0; i--)
        dfs.push(i);
    depth[0]=N;
    
    while (!dfs.empty())
    {
        // Pop Child
        output.push_back(dfs.top());
        dfs.pop();

        if(output.size()==M)
        {
            for(auto elem : output)
                cout << dict[elem] << " ";
            cout << '\n';

            do
            {
                depth[output.size()-1]--;
                output.pop_back();
            } while (!output.empty() && (depth[output.size()]==0));
        }
        else
        {
            // Push child
            for(int i=N-1; i>=0; i--)
            {
                int isDupl = false;
                for(auto elem : output)
                {
                    if(elem == i)
                    {
                        isDupl = true;
                        break;
                    }
                }
                if (!isDupl)
                {
                    depth[output.size()]++;
                    dfs.push(i);
                }
            }
        }
    }
}
