#include <vector>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

/*
@접근
    bfs로 가능할까?
    우선 마냥 앞으로 갔다간 점프할 곳이 없어질 수도 있음
    뒤로 가는 것까지 동시에 고려해야함
    하지만 최소 점프 수를 필요로 하는 것이 아니라 단순히 갈 수 있는지 여부만 확인하면 됨
    따라서 방문을 하기만 했다면 그 뒤를 다시 탐색할 필요는 없음
    즉, 한 셀에 여러 상태가 중첩되진 않음
    bfs나 dfs로 탐색하는 것은 충분히 가능하다는 결론
    다만 매번 문자열을 앞뒤로 탐색하며 점프 가능한 구역을 찾는건 비효율적일 수 있음
    그러니 사전에 점프 가능한 위치만 벡터에 정리하는 편이 좋다고 생각함
     ㄴ 모든 곳으로 점프가 가능하다면 차이가 없을 것
     ㄴ 하지만 그렇지 않다면 점프할 수 없는 곳을 매번 확인하기에 약간은 더 좋을것
     ㄴ 이미 방문한 셀을 제거할 수 있다면 더 좋겠지만, 이건 필요하다면 쓰자
    예상 시간복잡도는 O(n+n*d) : 초기 정리 n, 매 셀 순회마다 앞뒤 d만큼 탐색 (d : max-min)

    역시나 TLE이 발생함 -> s:10^5, min:1, max:49999
    set이나 list를 통해 풀에서 제거하는 방식이 좋을듯
    set을 이용한다면 low_bound, high_bound를 반복적으로 호출 제거하는 방식을 사용
     ㄴ 이 경우엔 초기 풀 생성에 nlogn, 매 순회 및 제거마다 logn * 4 (순회/제거는 2번씩 발생)
     ㄴ 그러나 점점 줄어들기 떄문에 매번 logn이 소모되진 않을 것
    list의 경우엔 삭제가 O(1)이겠지만, 삭제 시점을 잘 조정해야함
     ㄴ 방문이 종료될때 리스트에서 제거해야함
     ㄴ 왜냐하면 리스트에서 삭제된 노드로는 리스트를 순회할 수 없음
     ㄴ 하지만 제거 시점이 늦기 때문에 큐에 들어간 셀을 다시 추가할 수도 있음
        ㄴ bfs/dfs 양쪽 전부 동일한 문제가 있을것...
    때문에 set으로 pool을 구성하고, 여기서 하나씩 빼는 것으로 수행
     ㄴ 조회로 얻는 iter로 반복적으로 삭제
    
    처음 해석과 달리, 앞으로만 이동하면 되는 문제였음
    실행 결과, 219ms(over 5.25%), 81MB(over 5.42%)
    아무래도 set에서 잦은 삭제가 발생하기 때문에 느려지는 것으로 생각됨
*/

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        vector<int> zeroes;
        set<int> pool;
        zeroes.reserve(s.length());
        const int target = s.length()-1;

        if (s[target] != '0')
            return false;

        for (int i=1; i<s.length(); ++i)
        {
            if (s[i] == '0')
                pool.insert(i);
        }

        queue<int> toVisit;
        toVisit.push(0);

        while(!toVisit.empty())
        {
            auto curNode = toVisit.front();
            toVisit.pop();

            int jumpTo = curNode + minJump;
            auto it = pool.lower_bound(jumpTo);
            while(it != pool.end() && *it <= curNode+maxJump)
            {
                if (*it == target)
                    return true;
                toVisit.push(*it);
                it = pool.erase(it);
            }

            jumpTo = curNode - maxJump;
            it = pool.upper_bound(jumpTo);
            while(*it <= curNode-minJump)
            {
                toVisit.push(*it);
                it = pool.erase(it);
            }
        }

        return false;
    }
};

int main()
{
    Solution s;

    return 0;
}