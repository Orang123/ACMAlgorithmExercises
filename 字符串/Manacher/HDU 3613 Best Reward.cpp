/*
题意:摘自网上
给你一个字符串（仅含字母），每个字母有一个价值，
把字符串切断成两部分，若其中一部分为回文串，则其价值
等于各字母价值和相加；否则为0。总价值为两部分价值相加，求最大价值。
字符串长度<=500000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3613
思路:manacher.记录各个前缀和各个后缀构成回文串的长度,然后枚举
原始字符串的分割点,累加前缀后缀构成回文串的价值,记录最大价值和.
*/
//ac 124ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
#define INF -0x3f3f3f3f
using namespace std;

char s1[N],s2[N<<1];
//st[i]表示以i为对称中心的回文串的起始点下标
int val[26],p[N<<1],st[N<<1],id,mx,len,ans,sum[N],pre[N],sufix[N],cnt1,cnt2;

void manacher(){
    int k=0;
    s2[k++]='$';
    for(int i=1;i<=len;i++){
        s2[k++]='#';
        s2[k++]=s1[i];
    }
    s2[k++]='#';
    s2[k]='\0';
    len=k;
    mx=0;
    for(int i=2;i<len;i++){
        if(i<mx)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=1;
        while(s2[i-p[i]] == s2[i+p[i]])
            p[i]++;
        if(i+p[i]>mx){
            mx=i+p[i];
            id=i;
        }
        //st[i]=(i-p[i])/2;
    }
}

int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(pre,0,sizeof(pre));
        memset(sufix,0,sizeof(sufix));
        for(int i=0;i<26;i++)
            scanf("%d",&val[i]);
        scanf("%s",s1+1);
        len=strlen(s1+1);//从下标1开始,方便统计sum数组,并不影响manacher算法,最终s2数组下标仍然从0开始
        for(int i=1;i<=len;i++)
            sum[i]=sum[i-1]+val[s1[i]-'a'];
        n=len;
        manacher();
        cnt1=cnt2=0;
        for(int i=2;i<len;i++){
            if(p[i] == i)//前缀构成回文串
                pre[p[i]-1]=1;
            if(i+p[i] == len)//后缀构成回文串
                sufix[p[i]-1]=1;
        }
        int s;
        for(int i=1;i<n;i++){
            s=0;
            if(pre[i])//长度为i的前缀 构成回文串
                s+=sum[i];
            if(sufix[n-i])//长度为n-i的后缀构成回文串.
                s+=sum[n]-sum[i];
            ans=max(ans,s);
        }
        printf("%d\n",ans);
    }
    return 0;
}
