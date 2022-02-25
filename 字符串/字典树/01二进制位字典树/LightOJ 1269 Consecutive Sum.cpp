/*
题意:给定一个序列，选定一段区间的亦或和，输出最大和最小。
链接:http://lightoj.com/volume_showproblem.php?problem=1269
思路:将区间的前缀异或值作为一个数值插入01字典树.
对于查找最大,每次找不同位反值的,反向走.对于找最小的每次
找相同位相同值,正向走.因为找最小的是按当前值相同的位正向
走的,所以一定要先查找再插入,不然返回的最小值永远是0.

理解摘自博客:https://blog.csdn.net/SSimpLe_Y/article/details/61618135
sum[1] = a[1];
sum[2] = a[1] ^  a[2];
sum[3] = a[1] ^ a[2] ^a[3];
如果进行到查询sum[3]的时候，sum[3]就相当于给定的那个数，sum[1],sum[2]就相当于先前给的一组数，
如果sum[3]和sum[1]的异或值是最值，那么就相当于[2,3]这个区间的异或值是最值，
因为sum[3]^sum[1] = a[1] ^ a[2] ^a[3] ^ a[1] = a[2] ^a[3]，一个数被异或了两次，就相当于没有。
*/
//ac 281ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1550010
#define INF 0x3f3f3f3f
using namespace std;

int n,tr[N][2],cnt,a[50010],maxans,minans;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int rt=0,son;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val,int mark){
    int rt=0,son,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^mark]){
            res|=mark<<i;
            rt=tr[rt][son^mark];
        }
        else{
            res|=(mark^1)<<i;
            rt=tr[rt][son^(mark^1)];
        }
    }
    return res;
}

int main(){
    int T,cas=0,val;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        insertWord(a[0]);//a[0]=0 先插入0, 有可能最大值是a[i]本身
        maxans=0,minans=INF;
        for(int i=1;i<=n;i++){
            scanf("%d",&val);
            a[i]=a[i-1]^val;
            //maxans=max(maxans,a[i]);
            maxans=max(maxans,findWord(a[i],1));
            //minans=min(minans,a[i]);
            minans=min(minans,findWord(a[i],0));
            insertWord(a[i]);//对于找最小的,要先查找再插入, 避免返回0
        }
        printf("Case %d: %d %d\n",cas,maxans,minans);
    }
    return 0;
}
