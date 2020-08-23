/*
ID: axrdiv1
PROG: castle
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int maxn = 50 + 5;
int castle[maxn][maxn];
int component[maxn][maxn];
int cnt[maxn*maxn];

int m, n, maxs;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const int wa[] = {1, 2, 4, 8};
const char dw[] = {'W', 'N', 'E', 'S'};


void floodfill(int comp) {
    int num_visited;
    do {
        num_visited = 0;
        for(int y = 0; y < n; y++) for(int x = 0; x < m; x++) {
            if(component[y][x] == -2) {
                num_visited++;
                component[y][x] = comp;
                cnt[comp]++;
                for(int d = 0; d < 4; d++) {
                    if(y+dy[d]<n && y+dy[d]>=0 && x+dx[d]<m && x+dx[d]>=0)
                        if(component[y+dy[d]][x+dx[d]] == 0 && !(castle[y][x]&wa[d]))
                            component[y+dy[d]][x+dx[d]] = -2;
                }
            }
        }
    } while(num_visited != 0);
}

int findcomponents() {
    int num_component = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(component[i][j] == 0) {
            num_component++;
            component[i][j] = -2;
            floodfill(num_component);
        }
    }
    return num_component;
}
int main() {
    memset(component, 0, sizeof(component));
    ofstream fout("castle.out");
    ifstream fin("castle.in");
    fin >> m >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            fin >> castle[i][j];
    int compcnt = findcomponents();

    // 1. The number of rooms the castle has
    fout << compcnt << endl;

    // 2. The size of the largest room
    int larsize = 0;
    for(int i = 1; i <= compcnt; i++)
        larsize = max(larsize, cnt[i]);
    fout << larsize << endl;

    // 3. The size of the largest room create by removing one wall
    // 4. The single wall to remove to make the largest room possible
    int rex, rey, red;
    for(int x = 0; x < m; x++) for(int y = n-1; y >= 0; y--){
        for(int d = 0; d < 4; d++) {
            int ny = y+dy[d], nx = x+dx[d];
            if(ny<n && ny>=0 && nx<m && nx>=0)
                if(component[ny][nx] != component[y][x]) {    // different rooms
                    int rooma = component[ny][nx];
                    int roomb = component[y][x];
                    if(cnt[rooma] + cnt[roomb] > larsize) {
                        larsize = cnt[rooma] + cnt[roomb];
                        rex = x + 1;
                        rey = y + 1;
                        red = d;
                    }
                }
        }
    }

    fout << larsize << endl << rey << " " << rex << " " << dw[red] << endl;
    /*
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cout << component[i][j] << " ";
        cout << endl;
    }
    */

    return 0;
}
