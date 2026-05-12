#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/*
@접근
    이 문제를 약간 변형해서 생각해보면 블록 채우기와 같음
    블록을 최대한 빈틈없이 채우는 것이 목표임
    단, 각 블록은 길이와 최소 시작 위치가 주어짐
     ㄴ 원래는 task 시작 시 필요한 최소 비용이지만, 최소비용-소모비용하여 시작위치로 바꿔 생각하자
    그러면 시작 위치가 작은 블록을 우선 배치하고,
    그로 인해 발생한 빈 공간에 넣을 수 있는 블록을 찾아서 넣으면 됨
    
    시작 위치가 작은 순으로 정렬되는 힙
    그리고 넣을 수 있는 저비용을 찾아내는 힙이 또 필요함...
     ㄴ 이것도 힙으로 만들면 문제가 있음
     ㄴ top이 (c,i), top 다음이 (c+a,i-b)일 경우, top이 제일 저렴하지만 시작 위치로 인해 불가능함
     ㄴ 그러나 top 다음이 가능할 수 있으나, 이를 지나칠 수 있음
     ㄴ 그렇다고 시작 위치 힙으로도 비슷하게 불가능한 경우가 존재

    그런데 굳이 빈 공간을 채우려고 할 필요가 있을까?
    현재 제일 빨리 사용할 수 있는 블록을 먼저 쓴다 -> 다른 블록으론 해당 블록 앞을 못 채운다
    따라서 블록 앞의 빈 공간은 굳이 채우려고 할 필요가 없음
    그렇다면 뒷공간은 어떤지 생각해봐야함
    뒷공간은 뒤의 블록한테 맡기면 되는데, 뒷 블록도 위의 사실이 적용됨
    즉, 시작 위치힙 하나만으로 충분함
    이 경우, 시간복잡도는 O(nlogn)으로 생각됨
     ㄴ 무조건 nlogn + n 정도로 예상
    
    실행 결과, 69ms(over 31.07%), 101MB(over 29.61%)가 나옴
    약 50%가 28ms 부근에 분포한 것으로 보아, 더 나은 방법이 있는 것으로 예상됨
    tasks를 sort하는 방법도 고려했으나, 해당 방법은 1800ms을 넘음
    pq도 이용하지 않고 이를 처리할 방법이 있는 것으로 보임
     ㄴ 아마 O(n)이지 않을까 생각함
    
    다른 풀이를 본 결과, 내 설계나 접근은 절대 틀린 것이 아니었음
    sort를 이용하면 위 결과에 도달할 수 있음
     ㄴ 27ms(over 95.15%), 101MB(over 39.81%)
    그런데 1800ms이 나왔던 것은 람다에서 &를 빼먹어서 매번 복사가 발생해서 그랬던 것
    힙 방법에서 sort보다 약 2배가량 더 느렸던 것은 pq에 접근하고, 또 pop하는 것 때문으로 유추됨
    반면 sort 방법은 배열에 접근하는 것만 하기에 더 빠를 수밖에 없음
*/

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        auto comp = [&tasks](int lhs, int rhs) {
             return tasks[lhs][1]-tasks[lhs][0] > tasks[rhs][1]-tasks[rhs][0]; 
            };

        priority_queue<int,vector<int>,decltype(comp)> pq(comp);
        for (int i = 0; i < tasks.size(); ++i)
            pq.push(i);
        
        int cost = 0;

        for (int i = 0; i < tasks.size(); ++i)
        {
            auto idx = pq.top();
            pq.pop();

            cost = max(tasks[idx][1]-tasks[idx][0], cost);
            cost += tasks[idx][0];
        }

        return cost;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> v = {{1,3},{2,4},{10,11},{10,12},{8,9}};

    cout << s.minimumEffort(v) << endl;

    return 0;
}