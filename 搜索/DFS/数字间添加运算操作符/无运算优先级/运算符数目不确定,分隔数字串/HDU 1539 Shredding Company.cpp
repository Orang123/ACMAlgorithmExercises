/*
����:ժ������
����һ����n,��һ��������str��Ҫ��str��ֳ����ɶΣ�����Ҫʹ��
���ɶ�֮����ӽ���n�����ֻ��һ�ֲ𷨣���������ֲ𷨡�
�������ͬһ����ӽ��ĺͣ��ж��ֲ𷨣������rejected��
������в𷨵õ��ĺͶ���n����ô�����error��
�ַ����������6λ.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1539
˼·:dfs����ö�� ��������str�еķָ���,��¼��С��ֵ.
һ����֦,�ڷָ������ ��� ����Ѿ�����n��,�ͷ���.
*/
//ac 0ms dfs����ö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6
#define INF 0x3f3f3f3f
using namespace std;

int n,len,ans,num,a[N],b[N],flag;
char str[N];

void dfs(int st,int k,int sum){
    if(sum>n)//�������Ѿ�����n��, �ͷ���
        return;
    if(st == len){
        if(n-sum<ans){//�պõ���nʱ Ҳ����ֱ�ӷ���,�����ж��Ƿ��� ��ķָ����ʹ�ò�ֵΪ0
            ans=n-sum;
            flag=0;
            memcpy(b,a,sizeof(a));
            num=k;
        }
        else if(n-sum == ans)
            flag=1;
        return;
    }
    int tp=0;
    for(int i=st;i<len;i++){
        tp=tp*10+str[i]-'0';
        a[k]=tp;
        dfs(i+1,k+1,sum+tp);
    }
}

int main(){
    while(scanf("%d%s",&n,str)){
        if(!n && str[0] =='0')
            break;
        ans=INF;
        len=strlen(str);
        dfs(0,0,0);
        if(ans == INF)//������С�ڵ���n�Ľ��
            printf("error\n");
        else{
            if(!flag){//��С��ֵ ֻ��һ�����
                printf("%d",n-ans);
                for(int i=0;i<num;i++)
                    printf(" %d",b[i]);
                printf("\n");
            }
            else//��С��ֵ �ж������
                printf("rejected\n");
        }
    }
    return 0;
}

/*
//������� Ϊʲô��RE,�о�6λ���� �ָ����͵Ľ�����ᳬ��1000000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,len,res[M],ans,num,a[N],b[N];
char str[N];

void dfs(int st,int k,int sum){
    if(sum>n)
        return;
    if(st == len){
        if(sum<=n && n-sum<=ans){
            ans=n-sum;
            res[ans]++;
            memcpy(b,a,sizeof(a));
            num=k;
        }
        return;
    }
    int tp=0;
    for(int i=st;i<len;i++){
        tp=tp*10+str[i]-'0';
        a[k]=tp;
        dfs(i+1,k+1,sum+tp);
    }
}

int main(){
    while(scanf("%d%s",&n,str)){
        if(!n && str[0] =='0')
            break;
        memset(res,0,sizeof(res));
        ans=INF;
        len=strlen(str);
        dfs(0,0,0);
        if(ans == INF)
            printf("error\n");
        else{
            if(res[ans] == 1){
                printf("%d",n-ans);
                for(int i=0;i<num;i++)
                    printf(" %d",b[i]);
                printf("\n");
            }
            else
                printf("rejected\n");
        }
    }
    return 0;
}
*/
