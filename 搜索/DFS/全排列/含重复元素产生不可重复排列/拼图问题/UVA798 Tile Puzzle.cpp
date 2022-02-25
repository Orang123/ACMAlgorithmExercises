/*
题意:摘自网上
给出w*h的矩形和n种拼图(矩形)，，给出n种拼图的个数num[i]，宽w[i]，高h[i]，
问说用这些拼图可以用多少种不同的方法拼凑出w*h的矩形。每个矩形可以横放或竖放.
w,h<100.n<=10.
输入应该能保证这个问题一定优解.
链接:https://www.luogu.com.cn/problem/UVA798
思路:枚举每一个位置(x,y)处所能放置的可能种类的拼图.
*/
//ac 700ms dfs回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 110
using namespace std;

int n,sumW,sumH,num[N],w[N],h[N],mp[M][M],ans;

//在(x,y)处放置一个宽和高为(th,tw)的拼图,注意因为(x,y)本身就占据一个单位的宽和高 所以枚举的增量上界是 th-1和tw-1
int check(int x,int y,int th,int tw){
    if(x+th-1>sumH || y+tw-1>sumW)//注意最大只能加th-1,tw-1,因为(x,y)位置本身还各占据一个单位的宽和高
        return 0;
    for(int i=0;i<th;i++){
        for(int j=0;j<tw;j++){
            if(mp[x+i][y+j])//当前
                return 0;
        }
    }
    return 1;
}

void update(int x,int y,int th,int tw,int val){
    for(int i=0;i<th;i++){
        for(int j=0;j<tw;j++){
            mp[x+i][y+j]=val;
        }
    }
}

void dfs(int x,int y){
    if(y == sumW+1){//当前列用完,开始扫描下一行第一列
        x++;
        y=1;
    }
    if(x == sumH+1){//w*h的矩形已经填满
        ans++;
        return;
    }
    if(!mp[x][y]){//(x,y)位置未被占据
        for(int i=1;i<=n;i++){
            if(num[i] && check(x,y,h[i],w[i])){//横放
                num[i]--;
                update(x,y,h[i],w[i],1);
                dfs(x,y+1);//下一个位置之所以从(x,y+1)开始 是因为宽高所占据的位置不确定,害怕遗漏空余位置,所以一个单元一个单元扫描判断
                update(x,y,h[i],w[i],0);
                num[i]++;
            }
            if(num[i] && w[i]!=h[i] && check(x,y,w[i],h[i])){//当该拼图 宽高不同时,竖放也单独算一种方案.
                num[i]--;
                update(x,y,w[i],h[i],1);
                dfs(x,y+1);
                update(x,y,w[i],h[i],0);
                num[i]++;
            }
        }
    }
    else
        dfs(x,y+1);//(x,y)位置已经被别的拼图占据,扫描下一个位置(x,y+1)
}

int main(){
    while(scanf("%d%d%d",&sumW,&sumH,&n)!=EOF){//这里的宽高其实颠倒 也不会影响答案
        ans=0;
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&num[i],&w[i],&h[i]);
        dfs(1,1);
        printf("%d\n",ans);
    }
    return 0;
}
