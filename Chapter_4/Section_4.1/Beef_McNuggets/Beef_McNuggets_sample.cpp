/*
ID: axrdiv1
PROG: nuggets
LANG: C++
*/

#include<fstream>
#include<iostream>
using namespace std;

ofstream fout("nuggets.out");
ifstream fin("nuggets.in");

int nsize;
int sizes[10];

/* cando specifies whether a given number is possible or not */
/* since max size = 256, we'll never need to mark more than 256
 *    in the future, so we use a sliding window */
int cando[256];

int gcd(int a, int b) {
    int t;

    while (b != 0) {
        t = a % b;
        a = b;
        b = t;
    }

    return a;
}

int main() {
    int lv, lv2; /* loop variable */
    int pos;     /* count position */
    int last;    /* last impossible count */

    fin >> nsize;
    for (lv = 0; lv < nsize; lv++) fin >> sizes[lv];

    /* ensure gcd = 1 */
    lv2 = sizes[0];
    for (lv = 1; lv < nsize; lv++)
        lv2 = gcd(sizes[lv], lv2);

    if (lv2 != 1) {
        fout << 0 << endl;
        return 0;
    }

    /* we can do 0 */
    cando[0] = 1;

    lv = pos = 0;
    last = 0;
    while (pos < 2000000000)
    { /* bound as stated */

        /* if last 256 were all possible, we are done */
        if (pos - last > 256) break; 

        if (!cando[lv]) 
            last = pos; /* this isn't possible, update last impossible */
        else 
        { /* this is possible */
            cando[lv] = 0; /* mark pos+256 as impossible */

            /* mark pos + size as possible for each package size */
            // 向后标记
            for (lv2 = 0; lv2 < nsize; lv2++)
                cando[(lv+sizes[lv2])%256] = 1;
        }

        /* update lv & pos */
        lv = (++pos) % 256; 
    }

    if (pos >= 2000000000) last = 0; /* shouldn't occur */

    fout << last << endl;
    return 0;

}
