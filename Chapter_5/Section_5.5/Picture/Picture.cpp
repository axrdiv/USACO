/*
ID: axrdiv1
PROG: picture
LANG: C++
*/

/*
USER: Kefan Cao [axrdiv1]
TASK: picture
LANG: C++

Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.004 secs, 1420 KB]
   Test 2: TEST OK [0.004 secs, 1412 KB]
   Test 3: TEST OK [0.000 secs, 1384 KB]
   Test 4: TEST OK [0.004 secs, 1444 KB]
   Test 5: TEST OK [0.004 secs, 1412 KB]
   Test 6: TEST OK [0.004 secs, 1396 KB]
   Test 7: TEST OK [0.014 secs, 3208 KB]
   Test 8: TEST OK [0.004 secs, 1388 KB]
   Test 9: TEST OK [0.014 secs, 3200 KB]
   Test 10: TEST OK [0.004 secs, 1412 KB]
   Test 11: TEST OK [0.052 secs, 3276 KB]

All tests OK.
Your program ('picture') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations!
 */
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
const int MAX_N = 5000;
const int INF = 100000;

ofstream fout("picture.out");
ifstream fin("picture.in");
int N;

struct rect {
    int x1, y1, x2, y2, l, r;
};

struct node {
    int l, r, len, low;
};

vector<int> xmap, ymap;
vector<rect> G;

node tree[MAX_N << 5];

bool cmp(const rect& a, const rect& b) {
    return a.y1 > b.y1;
}

void build(int root, int l, int r) {
    node &t = tree[root];
    t.l = l; t.r = r;
    t.len = 0; t.low = INF;

    if(l == r) return;
    int mid = (l + r) / 2;
    build(root * 2 + 1, l, mid);
    build(root * 2 + 2, mid + 1, r);
}

void add(int root, int l, int r, const rect& rc, const vector<int> &axis) {
    if(l == r) {
        node &t = tree[root];
        if(rc.y1 < t.low) {
            t.len += 2 * (axis[l] - axis[l-1]);
        }
        t.low = min(t.low, rc.y2);
        return;
    }

    int mid = (l + r) / 2;
    if(rc.l < mid) add(root * 2 + 1, l, mid, rc, axis);
    if(rc.r > mid) add(root * 2 + 2, mid + 1, r, rc, axis);
    tree[root].len = tree[root * 2 + 1].len + tree[root * 2 + 2].len;
}

int main() {
    fin >> N;

    for(int i = 0; i < N; i++) {
        int x1, x2, y1, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        xmap.push_back(x1);
        xmap.push_back(x2);
        ymap.push_back(y1);
        ymap.push_back(y2);
        if(x1 > x2) swap(x1, x2);
        if(y2 > y1) swap(y1, y2);
        G.push_back((rect){x1, y1, x2, y2, 0, 0});
        // cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
    }

    sort(G.begin(), G.end(), cmp);
    sort(xmap.begin(), xmap.end());
    sort(ymap.begin(), ymap.end());
    xmap.erase(unique(xmap.begin(), xmap.end()), xmap.end());
    ymap.erase(unique(ymap.begin(), ymap.end()), ymap.end());


    for(int i = 0; i < G.size(); i++) {
        G[i].l = find(xmap.begin(), xmap.end(), G[i].x1) - xmap.begin();
        G[i].r = find(xmap.begin(), xmap.end(), G[i].x2) - xmap.begin();
    }

    int ans = 0;

    build(0, 0, xmap.size()-1);
    for(int i = 0; i < G.size(); i++) {
        add(0, 0, xmap.size()-1, G[i], xmap);
    }

    ans += tree[0].len;
    // cout << ans << endl;

    for(int i = 0; i < G.size(); i++) {
        swap(G[i].x1, G[i].y2);
        swap(G[i].x2, G[i].y1);
    }
    sort(G.begin(), G.end(), cmp);
    for(int i = 0; i < G.size(); i++) {
        G[i].l = find(ymap.begin(), ymap.end(), G[i].x1) - ymap.begin();
        G[i].r = find(ymap.begin(), ymap.end(), G[i].x2) - ymap.begin();
    }

    build(0, 0, ymap.size()-1);
    for(int i = 0; i < N; i++) {
        add(0, 0, ymap.size()-1, G[i], ymap);
    }
    ans += tree[0].len;
    fout << ans << endl;

    return 0;
}
