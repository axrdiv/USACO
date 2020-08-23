/*
ID: axrdiv1
PROG: theme
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cstring>
using namespace std;
const int MAXN = 5000 + 5;

ofstream fout("theme.out");
ifstream fin("theme.in");

int N;
int melody[MAXN];
int d[2][MAXN];
int ans = 1;

// d[i][j] 两个字符串，分别以i j结尾的公共长度
// 状态转移方程
/* 
 *  if(melody[i] == melody[j]) 
 *      // min()的作用是，j-i能够防止将重叠的尾部纳入计数
 *      d[i][j] = min(j-i, d[i-1][j-1]+1);
 *  else
 *      d[i][j] = 0;
 */

int main() {
    fin >> N;
    for(int i = 1; i <= N; i++) {
        fin >> melody[i];
        d[1][i] = 1;
    }
    for(int i = N; i != 0; i--) {       // 将每一项与前一项求差，这样可以忽略变奏的影响
        melody[i] -= melody[i-1];
    }

    for(int i = 1; i <= N; i++) {
        for(int j = i+ans; j <= N; j++) {     // 不重叠所以j = i+ans+1;
            if(melody[i] == melody[j]) {        // 如果这一项相同
                d[i&1][j] = min(j-i, d[!(i&1)][j-1]+1);
                ans = max(ans, d[i&1][j]);
            } else
                d[i&1][j] = 1;
        }
    }
    fout << ((ans < 4) ? 0 : ans) << endl;

    return 0;
}
