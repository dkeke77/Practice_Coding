#include <iostream>
#include <vector>

using namespace std;

/*
    수열을 입력받고, 그 수열에서 증가하는 부분수열 중 최대 길이를 알아내는 문제

    이 방식은 GPT가 추천한 O(NlogN) 방법
    DP와 그리디를 섞은 방식
    lis는 최대 길이 수열을 모방한 것으로, 이 벡터의 제일 끝의 원소값을 작게 만드는 것을 목표로 함
    이는 제일 끝의 원소값이 작을수록 더 많은 원소를 넣을 수 있기 때문
    같은 이유로 벡터의 다른 원소들도 작을수록 뒤에 더 작은 원소가 들어올 수 있기 때문에 가능한 작은 값으로 교체함

    입력을 받으면 lis에서 lower_bound를 통해 입력보다 큰 값이 있나 찾아봄
    더 큰 값이 없다면 이를 lis 뒤에 추가
    더 큰 값이 있다면 해당 값을 입력받은 새로운 값으로 교체
    이를 통해 배열 원소의 전반적인 크기를 최소화시킴

    단, 이 lis는 진짜 최대 길이 부분수열이 아님을 명심할것!!!
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<int> lis;
    int input;

    for(int i=0; i<N; i++)
    {
        cin >> input;

        auto it = lower_bound(lis.begin(),lis.end(),input);

        if(it == lis.end())
            lis.push_back(input);
        else
            *it = input;
    }
    cout << lis.size();
}