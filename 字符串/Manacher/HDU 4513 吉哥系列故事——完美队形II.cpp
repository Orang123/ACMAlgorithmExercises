/*
题意:给定n个整数h[i],求最长回文串长度,并且左端非递减,右端非递增.
n<=100000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4513
思路:manacher 向连边扩展的条件还需满足s2[i-p[i]+2]>=s2[i-p[i]],
+2是因为 原串中加入了间隔符'#',只能整数和整数对比不递减.
*/
//ac 296ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,s1[N],s2[N<<1],p[N<<1],id,mx,maxLen;

void manacher(){
    int k=0;
    s2[k++]=-1;
    for(int i=0;i<n;i++){
        s2[k++]=0;
        s2[k++]=s1[i];
    }
    s2[k++]=0;
    s2[k]=-2;//末尾结束符 也要和前面的字符不一致
    n=k;
    mx=maxLen=0;
    for(int i=1;i<n;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        //p[i]=1时,s2[i-p[i]+2]>=s2[i-p[i]] 就等价于s2[i+p[i]>=s2[i-p[i]]
        while(s2[i-p[i]] == s2[i+p[i]] && s2[i-p[i]+2]>=s2[i-p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        if(p[i]-1>maxLen)
            maxLen=p[i]-1;
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&s1[i]);
        manacher();
        printf("%d\n",maxLen);
    }
    return 0;
}

/*
//ac 280ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,s1[N],s2[N<<1],p[N<<1],id,mx,maxLen;

void manacher(){
    s2[0]=-1;
    for(int i=0;i<n;i++){
        s2[i*2+1]=0;
        s2[i*2+2]=s1[i];
    }
    s2[2*n+1]=0;
    s2[2*n+2]=-2;
    n=2*n+2;
    id=mx=maxLen=0;
    for(int i=1;i<n;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]] && s2[i-p[i]+2]>=s2[i-p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        if(p[i]-1>maxLen)
            maxLen=p[i]-1;
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&s1[i]);
        manacher();
        printf("%d\n",maxLen);
    }
    return 0;
}
*/
