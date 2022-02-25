/*
题意:判断字符串s1是否分割为3个连续非空回文子串.
|s1|<=20000.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5340
思路:manacher 根据p数组的回文半径,先枚举出最左边和最右边
的回文串,再判断中间字符串中心下标的回文半径是否比中间字符串
的长度的一半还大,如果比一半大,则说明中间字符串可以构成回文串.
*/
//ac 312ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20010
using namespace std;

char s1[N],s2[N<<1];
int p[N<<1],id,mx,len,cnt1,cnt2,pre[N<<1],sufix[N<<1];

void manacher(){
    len=strlen(s1);
    int k=-1;
    s2[++k]='$';
    for(int i=0;i<len;i++){
        s2[++k]='#';
        s2[++k]=s1[i];
    }
    s2[++k]='#';
    s2[++k]='\0';
    len=k;
    mx=0;
    for(int i=1;i<len;i++){
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
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s1);
        manacher();
        cnt1=cnt2=0;
        for(int i=1;i<len;i++){
            if(p[i] == i && i!=1)
                pre[++cnt1]=i;//记录左端构成回文串的下标
            if(i+p[i] == len && i!=len-1)
                sufix[++cnt2]=i;//记录右端构成回文串的下标
        }
        int l,r,mid,flag=0;
        for(int i=1;i<=cnt1;i++){
            for(int j=cnt2;j>=1;j--){//左端回文串下标正序,右端回文串 下标逆序,这样能更快求出满足条件的中间回文
                l=pre[i]+p[pre[i]];
                r=sufix[j]-p[sufix[j]];
                if(l>r)//如果l>r,那么右端回文串的下标只会更小,回文半径只会更大,后面的r只会更小,直接结束
                    break;
                mid=(l+r)/2;//中间回文串的 对称中心下标
                if(p[mid]>(r-l)/2){
                    flag=1;
                    break;
                }
            }
            if(flag)
                break;
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

/*
//ac 327ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20010
using namespace std;

char s1[N],s2[N<<1];
int p[N<<1],id,mx,len,cnt1,cnt2,pre[N<<1],sufix[N<<1];

void manacher(){
    len=strlen(s1);
    s2[0]='$';
    for(int i=0;i<len;i++){
        s2[i*2+1]='#';
        s2[i*2+2]=s1[i];
    }
    s2[len*2+1]='#';
    s2[len*2+2]='\0';
    len=len*2+2;
    id=mx=0;
    for(int i=1;i<len;i++){
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
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s1);
        manacher();
        cnt1=cnt2=0;
        for(int i=1;i<len;i++){
            if(p[i] == i && i!=1)
                pre[++cnt1]=i;
            if(i+p[i] == len && i!=len-1)
                sufix[++cnt2]=i;
        }
        int l,r,mid,flag=0;
        for(int i=1;i<=cnt1;i++){
            for(int j=cnt2;j>=1;j--){
                l=pre[i]+p[pre[i]];
                r=sufix[j]-p[sufix[j]];
                if(l>r)
                    break;
                mid=(l+r)/2;
                if(p[mid]>(r-l)/2){
                    flag=1;
                    break;
                }
            }
            if(flag)
                break;
        }
        if(flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
*/
