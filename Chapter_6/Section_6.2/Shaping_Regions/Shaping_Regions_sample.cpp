/*
ID: zc.rene1
LANG: C
PROG: rect1
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct rectangle
{
    int llx, lly, urx, ury, color;
    struct rectangle *next;
};


void CountColor(struct rectangle *head, int *color_count)
{
    memset(color_count, 0, 1001*sizeof(int));
    if (head == NULL)
    {
        return ;
    }

    head = head->next;

    while (head != NULL)
    {
        color_count[head->color] += ((head->urx - head->llx) * (head->ury - head->lly));
        head = head->next;
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void InsertNode(int *input, struct rectangle *current)
{
    struct rectangle *temp = (struct rectangle *)malloc(sizeof(struct rectangle));
    memcpy(temp, input, 5*sizeof(int));
    temp->next = current->next;
    current->next = temp;
}

void DeleteNode(struct rectangle *prev, struct rectangle **current)
{
    struct rectangle *temp = *current;
    prev->next = (*current)->next;
    *current = prev;
    free(temp);
}

void InsertRectangle(int *input, struct rectangle *head)
{
    struct rectangle *current = head;
    struct rectangle *prev = NULL;
    int cn[5];
    int in[5];
    int llx, lly, urx, ury;

    while (current->next != NULL)
    {
        prev = current;
        current = current->next;

        memcpy(cn, current, 5*sizeof(int));
        llx = max(input[0], cn[0]);
        lly = max(input[1], cn[1]);
        urx = min(input[2], cn[2]);
        ury = min(input[3], cn[3]);

        if ((urx <= llx) || (ury <= lly))
        {
            continue;
        }
        DeleteNode(prev, &current);
        /*insert 1*/
        if ((llx > cn[0]) && (cn[3] > lly))
        {
            in[0] = cn[0];
            in[1] = lly;
            in[2] = llx;
            in[3] = cn[3];
            in[4] = cn[4];
            InsertNode(in, current);
        }
        /*insert 2*/
        if ((cn[2] > llx) && (cn[3] > ury))
        {
            in[0] = llx;
            in[1] = ury;
            in[2] = cn[2];
            in[3] = cn[3];
            in[4] = cn[4];
            InsertNode(in, current);
        }
        /*insert 3*/
        if ((cn[2] > urx) && (ury > cn[1]))
        {
            in[0] = urx;
            in[1] = cn[1];
            in[2] = cn[2];
            in[3] = ury;
            in[4] = cn[4];
            InsertNode(in, current);
        }
        /*insert 4*/
        if ((urx > cn[0]) && (lly > cn[1]))
        {
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

int main(void)
{
    FILE *fin, *fout;
    int A, B, N;
    int input[1001][5];
    struct rectangle *tail = NULL;
    struct rectangle *head = NULL;
    int i, j, color, temp;
    int color_count[1001];

    fin = fopen("rect1.in", "r");
    fout = fopen("rect1.out", "w");

    /*get input*/
    fscanf(fin, "%d %d %d", &A, &B, &N);
    input[0][0] = 0;
    input[0][1] = 0;
    input[0][2] = A;
    input[0][3] = B;
    input[0][4] = 1;

    for (i=1; i<=N; i++)
    {
        for (j=0; j<5; j++)
        {
            fscanf(fin, "%d", &input[i][j]);
        }
    }
    /*begin to insert*/
    head = (struct rectangle *)malloc(sizeof(struct rectangle));
    for (i=0; i<=N; i++)
    {
        InsertRectangle(input[i], head);
    }
    /*get the count of each color*/
    CountColor(head, color_count);
    for (i=0; i<1001; i++)
    {
        if (color_count[i] != 0)
        {
            fprintf(fout, "%d %d\n", i, color_count[i]);
        }
    }
    return 0;
}
