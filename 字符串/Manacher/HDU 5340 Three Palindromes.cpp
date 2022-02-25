/*
����:�ж��ַ���s1�Ƿ�ָ�Ϊ3�������ǿջ����Ӵ�.
|s1|<=20000.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5340
˼·:manacher ����p����Ļ��İ뾶,��ö�ٳ�����ߺ����ұ�
�Ļ��Ĵ�,���ж��м��ַ��������±�Ļ��İ뾶�Ƿ���м��ַ���
�ĳ��ȵ�һ�뻹��,�����һ���,��˵���м��ַ������Թ��ɻ��Ĵ�.
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
                pre[++cnt1]=i;//��¼��˹��ɻ��Ĵ����±�
            if(i+p[i] == len && i!=len-1)
                sufix[++cnt2]=i;//��¼�Ҷ˹��ɻ��Ĵ����±�
        }
        int l,r,mid,flag=0;
        for(int i=1;i<=cnt1;i++){
            for(int j=cnt2;j>=1;j--){//��˻��Ĵ��±�����,�Ҷ˻��Ĵ� �±�����,�����ܸ�����������������м����
                l=pre[i]+p[pre[i]];
                r=sufix[j]-p[sufix[j]];
                if(l>r)//���l>r,��ô�Ҷ˻��Ĵ����±�ֻ���С,���İ뾶ֻ�����,�����rֻ���С,ֱ�ӽ���
                    break;
                mid=(l+r)/2;//�м���Ĵ��� �Գ������±�
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
