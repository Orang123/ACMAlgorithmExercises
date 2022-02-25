/*
题意:给一个最多8个结点的无向图，把结点重排后对于图中每条边(u,v)，
u和v在排列中的最大距离称为该排列的带宽。求带宽最小的排列.
链接:https://www.luogu.com.cn/problem/UVA140
思路:枚举全排列,计算排列中邻接点间的最大距离,求出最小值.
*/
//ac 0ms next_permutation求取全排列
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define N 100
#define INF 0x3f3f3f3f
using namespace std;

int id[N],letter[N],cnt,len,a[10],pos[N],ans,res[10];
char input[N];
vector<int> u,v;

int main(){
    while(scanf("%s",input) && input[0] != '#'){
        u.clear();
        v.clear();
        cnt=0;
        ans=INF;
        for(char ch='A';ch<='Z';ch++){
            if(strchr(input,ch)!=NULL){
                id[ch]=++cnt;//记录字母编号
                letter[cnt]=ch;
            }
        }
        len=strlen(input);
        int p=0,q=0;
        while(1){
            while(p<len && input[p]!=':')
                p++;
            if(p == len)
                break;
            while(q<len && input[q]!=';')
                q++;
            for(int i=p+1;i<q;i++){
                u.push_back(id[input[p-1]]);
                v.push_back(id[input[i]]);
            }
            p++,q++;
        }
        for(int i=1;i<=cnt;i++)
            a[i]=i;
        do{
            for(int i=1;i<=cnt;i++)
                pos[a[i]]=i;
            int bandwidth=0;
            for(int i=0;i<u.size();i++)//记录各个邻接点在排列中的距离 求出最大距离
                bandwidth=max(bandwidth,abs(pos[u[i]]-pos[v[i]]));
            if(bandwidth<ans){
                ans=bandwidth;
                memcpy(res,a,sizeof(a));
            }
        }while(next_permutation(a+1,a+1+cnt));
        for(int i=1;i<=cnt;i++)
            printf("%c ",letter[res[i]]);
        printf("-> %d\n",ans);
    }
    return 0;
}
