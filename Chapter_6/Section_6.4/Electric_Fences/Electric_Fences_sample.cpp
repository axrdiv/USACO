/*
ID: zc.rene1
LANG: C
PROG: fence3
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX 100
#define MAX_DISTANCE 9999999.0

int F;
double fences[150][4];
double global_min_distance = MAX_DISTANCE, global_min_x, global_min_y;

void GetInput(FILE *fin)
{
    int i, j;

    fscanf(fin, "%d", &F);
    for (i=0; i<F; i++)
    {
        for (j=0; j<4; j++)
        {
            fscanf(fin, "%lf", &fences[i][j]);
        }
    }
}

double PointToSegDist(double x, double y, int index)
{

    double x1 = fences[index][0];
    double y1 = fences[index][1];
    double x2 = fences[index][2];
    double y2 = fences[index][3];

    double cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
    if (cross <= 0) return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

    double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    if (cross >= d2) return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    double r = cross / d2;
    double px = x1 + (x2 - x1) * r;
    double py = y1 + (y2 - y1) * r;
    return sqrt((x - px) * (x - px) + (py - y) * (py - y));
}

double GetDistance(double x, double y)
{
    int i;
    double ret = 0.0;

    for (i=0; i<F; i++)
    {
        ret += PointToSegDist(x, y, i);
    }

    return ret;
}

void CalDistance(double min_x, double max_x, double min_y, double max_y, double step)
{
    double x, y, new_step;
    double temp_distance, temp_min_distance = MAX_DISTANCE; 
    double stack[10][2];
    int i, bottom = -1, top = -1;

    for (x=min_x; x<=max_x; x+=step)
    {
        for (y=min_y; y<=max_y; y+=step)
        {
            temp_distance = GetDistance(x, y);
            if (temp_distance < temp_min_distance)
            {
                temp_min_distance = temp_distance;
                top = 0;
                stack[top][0] = x;
                stack[top][1] = y;
            }
            else if (temp_distance == temp_min_distance)
            {
                top++;
                stack[top][0] = x;
                stack[top][1] = y;
            }
        }
    }

    new_step = step / 10.0;

    if (new_step >= 0.01)
    {
        while (top > bottom)
        {
            x = stack[top][0];
            y = stack[top][1];
            CalDistance(x - step, x + step, y - step, y + step, new_step);
            top--;
        }
    }
    else
    {
        if (temp_min_distance < global_min_distance)
        {
            for (i=bottom+1; i<=top; i++)
            {
                global_min_distance = temp_min_distance;
                global_min_x = stack[i][0];
                global_min_y = stack[i][1];
            }
        }
    }
}

int main(void)
{
    FILE *fin, *fout;

    fin = fopen("fence3.in", "r");
    fout = fopen("fence3.out", "w");

    GetInput(fin);
    CalDistance(0.0, 100.0, 0.0, 100.0, 10.0);
    fprintf(stdout, "%.1lf %.1lf %.1lf\n", global_min_x, global_min_y, global_min_distance);

    return 0;
}
