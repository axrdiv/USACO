/*
ID: axrdiv1
PROG: heritage
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

ofstream fout("heritage.out");
ifstream fin("heritage.in");

string inord, preord;

struct node {
    char c;
    node* l; 
    node* r;
    node(char c=0, node* l=NULL, node* r=NULL): c(c), l(l), r(r) {}
};

node* rebuild(string preord, string inord) {
    if(preord.size() == 0) return NULL;
    node* p = new(node);
    p->c = preord[0];
    string lst = inord.substr(0, inord.find(preord[0]));
    // cout << lst << endl;
    string rst = inord.substr(inord.find(preord[0])+1);
    // cout << rst << endl;
    p->l = rebuild(preord.substr(1, lst.size()), lst);
    p->r = rebuild(preord.substr(1+lst.size()), rst);
    return p;
}

void postordp(node* root) {
    if(root->l) postordp(root->l);
    if(root->r) postordp(root->r);
    fout << root->c;
}

int main() {
    fin >> inord >> preord;
    node* root = rebuild(preord, inord);
    postordp(root);
    fout << endl;
    return 0;
}
