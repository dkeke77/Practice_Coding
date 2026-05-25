#include <vector>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

/*
@개선
    한쪽 방향만으로 이동한다면, 정말 단순하게 접근하면 됨
    문자열을 쭉 이동하면서 현재 칸에 도달 가능한 제일 먼 인덱스와 제일 가까운 인덱스를 관리
    큐를 만들어서 관리하면 좋을듯
     ㄴ 제일 앞의 원소가 curIdx - max 밖이면 pop
     ㄴ 범위 내라면 min 체크 후 큐에 추가
    이를 큐가 완전히 비거나 끝에 도달할 때까지 수행
    굳이 큐가 아니더라도 배열로 연결리스트를 만들어서 구현 가능할듯
    예상 시간복잡도 O(n) : 쭉 순회하면서 큐 확인하며 추가/삭제만 수행하기 때문
     ㄴ 아마 실제론 참조/삭제/추가 때문에 3n쯤?
     ㄴ 그리고 큐 자체 속도때문에 예상보다 느릴 수 있음
    실행 결과, 11ms(over 53.53%), 23MB(over 68.85%)

    지금도 충분히 빠르지만, queue말고 벡터로 구현하면 더 빠를 것으로 보임
    따라서 큐를 벡터로 변경하고, ptr를 통해 이를 추적토록 구현함
    실행 결과, 3ms(over 96.04%), 24MB(over 54.22%)

    다른 풀이에선 슬라이딩 윈도우 개념으로 풀어냄
    현재 위치에 도달 가능한 윈도우의 개수를 추적하며 풀어냄
     ㄴ 현재 위치에서 minJump 뒤 위치를 방문했다면 +1
     ㄴ 현재 위치에서 maxJump 뒤 위치를 방문했으면서 maxJump+1 뒤가 '1'이라면 -1
     ㄴ 슬라이딩 윈도우를 들어가고 벗어났다는 개념으로 생각하면 됨
    내 방식과 달리 큐 비우기나 ptr 이동 같은 것이 필요 없으므로, 보다 빠른 방법임
*/

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        vector<int> visited;
        visited.reserve(s.length());
        int qPtr = 0;
        const int target = s.length()-1;

        if (s[target] != '0')
            return false;

        visited.push_back(0);

        for (int i=minJump; i<s.length(); ++i)
        {
            if (qPtr >= visited.size())
                break;
            if (s[i] == '0')
            {
                while(qPtr < visited.size() && i - visited[qPtr] > maxJump)
                    qPtr++;

                if (qPtr >= visited.size())
                    break;
                else if (i - visited[qPtr] >= minJump)
                    visited.push_back(i);
            }
        }

        if (visited.back() == target)
            return true;
        else
            return false;
    }
};

int main()
{
    Solution s;

    return 0;
}