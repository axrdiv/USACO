/*
ID: axrdiv1
PROG: packrec
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

struct rect_t {
    int side[2] = {0, 0};
};
rect_t in[4], out[4];

int area;
int idx;

// 更新最小面积,同时记录边长,采用插入排序
void check(int w, int h) {
    int area_t = w * h;
    rect_t tmp;

    tmp.side[0] = w < h ? w : h;
    tmp.side[1] = w > h ? w : h;

    if(area_t > area) return;
    else if(area_t == area) {
        for(int i = 0; i < idx; i++) {
            if(tmp.side[0] == out[i].side[0]) return;
            if(tmp.side[0] < out[i].side[0]) {
                for(int j = idx; j > i; j--) {
                    out[j] = out[j - 1];
                }
                out[i] = tmp;
                idx++;
                return;
            }
        }
        out[idx++] = tmp;
        return;
    } else {
        area = area_t;
        idx = 0;
        out[idx++] = tmp;
    }
}


int main() {
    ofstream fout("packrec.out");
    ifstream fin("packrec.in");

    for(int i = 0; i < 4; i++) {
        fin >> in[i].side[0] >> in[i].side[1];
    }

    idx = 0;
    area = ~0x80000000;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i == j) continue;
            for(int k = 0; k < 4; k++) {
                if(k == i || k == j) continue;
                int l = 6 - i - j - k;
                for(int q = 0; q < 16; q++) {
                    int w[4], h[4], wmin, hmin;
                    w[0] = in[i].side[(q&1) ? 1 : 0];
                    h[0] = in[i].side[(q&1) ? 0 : 1];
                    w[1] = in[j].side[(q&2) ? 1 : 0];
                    h[1] = in[j].side[(q&2) ? 0 : 1];
                    w[2] = in[k].side[(q&4) ? 1 : 0];
                    h[2] = in[k].side[(q&4) ? 0 : 1];
                    w[3] = in[l].side[(q&8) ? 1 : 0];
                    h[3] = in[l].side[(q&8) ? 0 : 1];

                    // 第一种布局
                    wmin = w[0] + w[1] + w[2] + w[3];
                    hmin =  *max_element(h, h+4);
                    check(wmin, hmin);

                    // 第二种布局
                    wmin = max(w[3], w[0] + w[1] + w[2]);
                    hmin = h[3] + *max_element(h, h + 3);
                    check(wmin, hmin);

                    // 第三种布局
                    wmin = max(w[0] + w[1], w[2]) + w[3];
                    hmin = max(max(h[0] + h[2], h[1] + h[2]), h[3]);
                    check(wmin, hmin);

                    // 第四种布局、第五种布局
                    wmin = max(w[0], w[1]) + w[2] + w[3];
                    hmin = max(max(h[0] + h[1], h[2]), h[3]);
                    check(wmin, hmin);

                    // 第六种布局
                    if(h[2] == h[3])
                        wmin = max(w[0] + w[1], w[2] + w[3]);
                    else if(h[2] > h[3] && h[2] < h[3] + h[1])
                        wmin = max(max(w[2] + w[3], w[2] + w[1]), w[0] + w[1]);
                    else if(h[2] < h[3] && h[2] + h[0] > h[3])
                        wmin = max(max(w[3] + w[2], w[3] + w[0]), w[0] + w[1]);
                    hmin = max(h[0] + h[2], h[1] + h[3]);
                    check(wmin, hmin);
                }
            }
        }
    }
    fout << area << endl;
    for(int i = 0; i < idx; i++) {
        fout << out[i].side[0] << " " << out[i].side[1] << endl;
    }

    return 0;
}
