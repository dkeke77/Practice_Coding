#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    세그먼트 트리로 풀면 되는 문제
    다만, 단순한 세그먼트 트리와는 다르게 인접 구간 간 문자열 병합을 신경써야함
    따라서 세그먼트에 제일 왼쪽/오른쪽 문자를 표기하고, 이를 확인하여 병합과 최댓값 업데이트를 병행해야함
    또한 병합되면서 기존에 최대가 아니었던 문자가 최대가 될 수 있음
    때문에 제일 왼쪽/오른쪽 문자의 길이 또한 필요함
    그리고 왼쪽/오른쪽 세그먼트가 완전히 동일한 문자로 구성된 경우,
    두 세그먼트 연결부의 문자가 동일하다면 왼쪽/오른쪽 문자의 길이를 업데이트해야함
    그런데 완전히 동일한 문자로 이루어졌는지에 대한 평가를 세그먼트 양끝의 문자가 동일한지 여부로 확인했는데,
    이 때문에 버그가 발생했음
    이는 중간에 문자가 다른 경우도 동일한 문자로 이루어진 세그먼트로 처리했기 때문임
    따라서 merge에서 depth를 받고, 이를 기준으로 현재 세그먼트의 width를 계산하여 평가에 같이 사용함

    실행 결과, 153ms(over 62.91%), 114MB(over 22.51%)
*/

struct ChInfo
{
    int len;
    char ch;
};

struct Seg
{
    ChInfo longest;
    ChInfo left;
    ChInfo right;
};

class SegTree
{
public:
    SegTree(const string& s) : n(s.length())
    {
        arr.resize(n);
        int depth = 0;

        while(1<<depth < n)
            depth++;
        
        maxDepth = depth;
        arr.resize((2<<depth) - 1);

        int startIdx = (1<<depth) - 1;
        for (int i=0; i<n; i++)
            arr[startIdx+i] = { { 1,s[i] }, { 1,s[i] }, { 1,s[i] } };
        
        for (depth--; depth >= 0; depth--)
        {
            startIdx = (1<<depth) - 1;
            for (int i=0; i<(1<<depth); i++)
            {
                int idx = startIdx+i;

                arr[idx] = mergeSeg(depth, arr[idx*2+1], arr[idx*2+2]);
            }
        }
    }

    int query(char qCh, int qIdx)
    {
        int depth = maxDepth;
        int idx = (1<<depth) - 1 + qIdx;
        arr[idx].left.ch = qCh;
        arr[idx].right.ch = qCh;
        arr[idx].longest.ch = qCh;

        for (depth--; depth >= 0; depth--)
        {
            idx = (idx-1) / 2;
            arr[idx] = mergeSeg(depth, arr[idx*2+1], arr[idx*2+2]);
        }

        return arr[0].longest.len;
    }

    void print()
    {
        for (int depth=0; depth<=maxDepth; depth++)
        {
            int startIdx = (1<<depth) - 1;
            for (int i=0; i<(1<<depth); i++)
                cout << arr[startIdx+i].longest.ch << " ";
            cout << endl;
        }
    }

private:
    Seg mergeSeg(int depth, const Seg& segL, const Seg& segR)
    {
        if (segL.right.ch < 'a' || segL.right.ch > 'z')
            return segR;
        if (segR.right.ch < 'a' || segR.right.ch > 'z')
            return segL;

        int width = 1<<(maxDepth - depth - 1);
        Seg newSeg;
        if (segL.longest.len > segR.longest.len)
            newSeg.longest = segL.longest;
        else
            newSeg.longest = segR.longest;

        newSeg.left = segL.left;
        newSeg.right = segR.right;

        if (segL.right.ch == segR.left.ch)
        {
            int mergedLen = segL.right.len + segR.left.len;

            if (mergedLen > newSeg.longest.len)
            {
                newSeg.longest.len = mergedLen;
                newSeg.longest.ch = segL.right.ch;
            }

            if (segL.left.len == width)
                newSeg.left.len = mergedLen;

            if (segR.left.len == width)
                newSeg.right.len = mergedLen;
        }

        return newSeg;
    }

    const int n;
    int maxDepth;
    vector<Seg> arr;
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        const int n = queryIndices.size();
        vector<int> result;
        result.reserve(n);

        SegTree st(s);

        for (int i=0; i<n; i++)
        {
            result.push_back(st.query(queryCharacters[i], queryIndices[i]));
        }

        return result;
    }
};

int main()
{
    Solution s;

    return 0;
}