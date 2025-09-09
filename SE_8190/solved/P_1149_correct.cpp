#include <iostream>
#include <vector>

using namespace std;

/*
    그리디로 풀었다가 결국 DP...
*/

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0);
    cout.tie(0);

    int iter;
    cin >> iter;

    vector<int[3]> price(iter);
    int input[3];

    for(int i=0; i<iter; i++)
    {
        cin >> input[0] >> input[1] >> input[2];

        if (i==0)
        {
            copy(input, input+3, price[0]);
            continue;
        }
        
        price[i][0] = min(price[i-1][1],price[i-1][2]) + input[0];
        price[i][1] = min(price[i-1][0],price[i-1][2]) + input[1];
        price[i][2] = min(price[i-1][0],price[i-1][1]) + input[2];
    }
    cout << min(min(price[iter-1][0],price[iter-1][1]),price[iter-1][2]);
}
