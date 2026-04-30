#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    5 * 10^7 이하로 할 수 있도록 하자
    이웃집과 색칠이 겹치지 않도록 하는 문제
    각 집마다 최소 가격을 선택 안했을 시의 손해를 저장
    최대 손해가 발생할 수 있는 집부터 순회하며 최소값을 선택하도록 함
    즉, 최대 손실을 회피하는 것이 의도

    하지만 틀림
    이 방식이 전역적인 최소비용을 보장하진 않나봄...
*/

struct House
{
    int index;
    int loss;
    int prices[3];
    int minIdx[3] = {0,1,2};

    bool operator<(const House& other) const 
    {
        return loss < other.loss;
    }
};

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int iter;
    int amount = 0;

    cin >> iter;

    vector<int> colored(iter, -1);
    priority_queue<House> houses;

    for (int i=0; i<iter; i++)
    {
        House input;
        input.index = i;
        cin >> input.prices[0] >> input.prices[1] >> input.prices[2];

        for (int i=0; i<2; i++)
        {
            for (int j=0; j<2-i; j++)
            {
                if(input.prices[input.minIdx[j]] > input.prices[input.minIdx[j+1]])
                    swap(input.minIdx[j],input.minIdx[j+1]);
            }
        }
        input.loss = (input.prices[input.minIdx[2]] + input.prices[input.minIdx[0]] - input.prices[input.minIdx[1]]*2)/2;

        houses.push(input);
    }

    while(!houses.empty())
    {
        House curHouse = houses.top();
        houses.pop();
        
        for (int i=0; i<3; i++)
        {
            if (curHouse.index - 1 >= 0)
            {
                if (colored[curHouse.index-1] == curHouse.minIdx[i])
                    continue;
            }
            if (curHouse.index + 1 < iter)
            {
                if (colored[curHouse.index+1] == curHouse.minIdx[i])
                    continue;
            }

            amount += curHouse.prices[curHouse.minIdx[i]];
            colored[curHouse.index] = curHouse.minIdx[i];
            break;
        }
    }

    cout << amount;
}
