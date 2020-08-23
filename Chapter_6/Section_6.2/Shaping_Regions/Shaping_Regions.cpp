/*
ID: axrdiv1
PROG: rect1
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

ofstream fout("rect1.out");
ifstream fin("rect1.in");

struct rect {
    int llx, lly, urx, ury, color;
    struct rect *next;
};

vector<rect> rectlist;
int color_count[1001];

void InsertNode(int *input, struct rect *current) {
    struct rect *temp = (struct rect *) malloc(sizeof(struct rect));
    memcpy(temp, input, 5*sizeof(int));
    temp->next = current->next;
    current->next = temp;
}

void DeleteNode(struct rect *prev, struct rect *current) {
    struct rect *temp = current;
    prev->next = current->next;
    free(temp);
}

void CountColor(struct rect *head, int *color_count) {
    memset(color_count, 0, 1001 * sizeof(int));
    if(head == NULL) return;

    head = head->next;
    while(head != NULL) {
        color_count[head->color] += ((head->urx - head->llx) * (head->ury - head->lly));
        head = head->next;
    }
}

void InsertRect(int *input, struct rect *head) {
    struct rect *current = head;
    struct rect *prev = NULL;
    int cn[5];
    int in[5];

    while(current->next != NULL) {
        prev = current;
        current = current->next;
        memcpy(cn, current, 5*sizeof(int));

        int llx, lly, urx, ury;
        llx = max(input[0], cn[0]);
        lly = max(input[1], cn[1]);
        urx = min(input[2], cn[2]);
        ury = min(input[3], cn[3]);

        if((urx <= llx) || (ury <= lly))
            continue;

        DeleteNode(prev, current);
        current = prev;

        /* insert 1 */
        if((llx > cn[0]) && (cn[3] > lly)) {
            in[0] = cn[0];
            in[1] = lly;
            in[2] = llx;
            in[3] = cn[3];
            in[4] = cn[4];
            InsertNode(in, current);
        }

        /* insert 2 */
        if((cn[2] > llx) && (cn[3] > ury)) {
            in[0] = llx;
            in[1] = ury;
            in[2] = cn[2];
            in[3] = cn[3];
            in[4] = cn[4];
            InsertNode(in, current);
        }

        /* insert 3 */
        if((cn[2] > urx) && (ury > cn[1])) {
            in[0] = urx;
            in[1] = cn[1];
            in[2] = cn[2];
            in[3] = ury;
            in[4] = cn[4];
            InsertNode(in, current);
        }

        /* insert 4 */
        if((urx > cn[0]) && (lly > cn[1])) {
            in[0] = cn[0];
            in[1] = cn[1];
            in[2] = urx;
            in[3] = lly;
            in[4] = cn[4];
            InsertNode(in, current);
        }
    }
    InsertNode(input, current);
}

int A, B, N;

int main() {
    int input[1001][5];
    struct rect *head = NULL;
    head = (struct rect *)malloc(sizeof(struct rect));

    fin >> A >> B >> N;
    input[0][0] = 0;
    input[0][1] = 0;
    input[0][2] = A;
    input[0][3] = B;
    input[0][4] = 1;

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < 5; j++)
            fin >> input[i][j];
    }


    for(int i = 0; i <= N; i++) {
        InsertRect(input[i], head);
    }

    CountColor(head, color_count);

    for(int i = 0; i < 1001; i++) {
        if(color_count[i] != 0)
            fout << i << " " << color_count[i] << endl;
    }
    return 0;
}
