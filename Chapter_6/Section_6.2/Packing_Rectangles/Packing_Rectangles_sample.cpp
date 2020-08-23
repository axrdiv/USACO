/*
ID:
LANG: C
TASK: packrec
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WI(x) (x & 0x08) >> 3
#define WJ(x) (x & 0x04) >> 2
#define WK(x) (x & 0x02) >> 1
#define WL(x) (x & 0x01)
typedef struct rect_t {
    int side[2];
}rect_t;
rect_t in[4], out[6];
int idx;
int area;
int max2(int a, int b) {
    return a >= b ? a : b;
}
int max3(int a, int b, int c) {
    return max2(max2(a, b), c);
}
int max4(int a, int b, int c, int d) {
    return max2(max3(a, b, c), d);
}
void check(int w, int h) { //更新最小面积，同时记录边长，使用插入排序法
    int min = w * h;
    int i, j;
    rect_t tmp;

    if(min > area) return;
    else if(min == area) {
        tmp.side[0] = w < h ? w : h;
        tmp.side[1] = w > h ? w : h;
        for(i = 0; i < idx; i++) {
            if(tmp.side[0] == out[i].side[0]) return;
            if(tmp.side[0] < out[i].side[0]) {
                for(j = idx; j > i; j--)
                    out[j] = out[j - 1];
                out[i] = tmp;
                idx++;
                return;
            }
        }
        out[idx++] = tmp;
    }
    else {
        area = min;
        idx = 0;
        out[idx].side[0] = w < h ? w : h;
        out[idx++].side[1] = w > h ? w : h;
    }
}
int main() {
    FILE *fin = fopen("packrec.in", "r");
    FILE *fout = fopen("packrec.out", "w");
    int i, j, k, l;
    unsigned char q;
    memset((char *)in, 0, sizeof(rect_t) * 4);
    memset((char *)out, 0, sizeof(rect_t) * 6);
    for(i = 0; i < 4; i++) {
        fscanf(fin, "%d %d", &in[i].side[0], &in[i].side[1]);
    }
    idx = 0;
    area = ~0x80000000;    //area先取最大值
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(i == j) continue;
            for(k = 0; k < 4; k++) {
                if(k == i || k == j) continue;
                l = 6 - i - j - k;        //用i, j, k, l标识一个排列
                for(q = 0; q < 16; q++) { //位置固定时，每个位置上的矩形旋转，一共有16中可能
                    int w[4], h[4], wmin, hmin;
                    w[0] = in[i].side[WI(q)];        //因为q在0～15之间，恰好可以用4bit表示，每个bit表示一个矩形的旋转
                    h[0] = in[i].side[1 - (WI(q))];
                    w[1] = in[j].side[WJ(q)];
                    h[1] = in[j].side[1 - (WJ(q))];
                    w[2] = in[k].side[WK(q)];
                    h[2] = in[k].side[1 - (WK(q))];
                    w[3] = in[l].side[WL(q)];
                    h[3] = in[l].side[1 - WL(q)];
                    wmin = w[0] + w[1] + w[2] + w[3];       //第1种布局
                    hmin = max4(h[0], h[1], h[2], h[3]);
                    check(wmin, hmin);
                    wmin = max2(w[3], w[0]+w[1]+w[2]);      //第2种布局
                    hmin = max3(h[0], h[1], h[2]) + h[3];
                    check(wmin, hmin);
                    wmin = max2(w[0]+w[1], w[2]) + w[3];    //第3种布局
                    hmin = max3(h[0]+h[2], h[1]+h[2], h[3]);
                    check(wmin, hmin);
                    wmin = max2(w[0], w[1]) + w[2] + w[3];  //第4，5种布局
                    hmin = max3(h[0]+h[1], h[2], h[3]);
                    check(wmin, hmin);
                    if(h[2] == h[3])                        //第6种布局
                        wmin = max2(w[0]+w[1], w[2]+w[3]);
                    else if(h[2] > h[3] && h[2] < h[3]+h[1])
                        wmin = max3(w[2]+w[3], w[2]+w[1], w[0]+w[1]);
                    else if(h[2] < h[3] && h[2]+h[0] > h[3])
                        wmin = max3(w[3]+w[2], w[3]+w[0], w[0]+w[1]);
                    hmin = max2(h[0]+h[2], h[1]+h[3]);
                    check(wmin, hmin);
                }
            }
        }
    }
    fprintf(fout, "%d/n", area);
    for(i = 0; i < idx; i++) {
        fprintf(fout, "%d %d/n", out[i].side[0], out[i].side[1]);
    }
    exit(0);
}
