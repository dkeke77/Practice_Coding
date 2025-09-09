#include <iostream>
#include <vector>

using namespace std;

/*
    유명한 배낭 문제
    DP로 풀어본것
    처음에 2번째 for문을 앞에서부터 순회하도록 했었는데 : for (int j=0; j <= MAX_WEIGHT; j++)
    이번 순회중에 물건을 넣은 인덱스를 다시 참조하는 이슈가 발생해서 틀렸었음
    그래서 뒤로 순회하게 하여 이슈를 해결함
    더 나아가 if문 하나를 for문의 조건에 병합시킬 수 있었음

    그리고 앞에서부터 순회하는 방식은 완벽히 틀린게 아니고 무한 배낭의 해법이라고 함
    물건을 중복으로 계속 넣을 수 있는 문제인데, 앞에서 순회하는 방식은 다시 참조하여도 문제의 규칙에 어긋나지 않음
*/
int main()
{
    int ITEM_COUNT, MAX_WEIGHT;
    cin >> ITEM_COUNT >> MAX_WEIGHT;

    vector<int> bag(MAX_WEIGHT+1,0);

    int w = 0, v = 0;
    for (int i=0; i < ITEM_COUNT; i++)
    {
        cin >> w >> v;
        for (int j=MAX_WEIGHT; j >= w; j--)
        {
            int newValue = bag[j-w] + v;
            if (bag[j] < newValue)
                bag[j] = newValue;
        }
    }

    cout << bag.back() << endl;
}