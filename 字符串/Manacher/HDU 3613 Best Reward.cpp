/*
����:ժ������
����һ���ַ�����������ĸ����ÿ����ĸ��һ����ֵ��
���ַ����жϳ������֣�������һ����Ϊ���Ĵ��������ֵ
���ڸ���ĸ��ֵ����ӣ�����Ϊ0���ܼ�ֵΪ�����ּ�ֵ��ӣ�������ֵ��
�ַ�������<=500000.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3613
˼·:manacher.��¼����ǰ׺�͸�����׺���ɻ��Ĵ��ĳ���,Ȼ��ö��
ԭʼ�ַ����ķָ��,�ۼ�ǰ׺��׺���ɻ��Ĵ��ļ�ֵ,��¼����ֵ��.
*/
//ac 124ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
#define INF -0x3f3f3f3f
using namespace std;

char s1[N],s2[N<<1];
//st[i]��ʾ��iΪ�Գ����ĵĻ��Ĵ�����ʼ���±�
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
        len=strlen(s1+1);//���±�1��ʼ,����ͳ��sum����,����Ӱ��manacher�㷨,����s2�����±���Ȼ��0��ʼ
        for(int i=1;i<=len;i++)
            sum[i]=sum[i-1]+val[s1[i]-'a'];
        n=len;
        manacher();
        cnt1=cnt2=0;
        for(int i=2;i<len;i++){
            if(p[i] == i)//ǰ׺���ɻ��Ĵ�
                pre[p[i]-1]=1;
            if(i+p[i] == len)//��׺���ɻ��Ĵ�
                sufix[p[i]-1]=1;
        }
        int s;
        for(int i=1;i<n;i++){
            s=0;
            if(pre[i])//����Ϊi��ǰ׺ ���ɻ��Ĵ�
                s+=sum[i];
            if(sufix[n-i])//����Ϊn-i�ĺ�׺���ɻ��Ĵ�.
                s+=sum[n]-sum[i];
            ans=max(ans,s);
        }
        printf("%d\n",ans);
    }
    return 0;
}
