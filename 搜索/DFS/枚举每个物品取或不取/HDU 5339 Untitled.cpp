/*
����:ժ������
����һ��a,����n������b[1..n];
Ȼ���n��������ѡ��r������;
Ҫ��a % c1 % c2 % c3......%cr = 0;
������ѡ����;
n<=20,a<=10^6
����:https://acm.hdu.edu.cn/showproblem.php?pid=5339
˼·:����ȡ��,�����������a,ȡ���Ľ�����Ǳ�����
����,���Ҫ�ѳ�������a�õ�ֵɾȥ,��ȡ������������
�Խ�С��ȡ��,�ٶԽϴ���ȡ����û�������,��Ϊ��С��
ȡ��Ľ��һ��С�ں���ϴ������,����ȡ��Ľ��һ����
���������,������.���ȡ��ֻҪ�ӽϴ�����ʼȡ��,�ٶԽ�С��
ȡ��,��b���鰴�մӴ�С����,��ÿ��b[1..n]�е�b[i]�������������
Ҫôȡ��Ҫô��ȡ��,�������ܱ�������ȡ����������.
*/
//ac 0ms dfs���ݴӽϴ�b[i]��ʼȡ��
//���Ӷ�O(2^20)=1048576
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,a,b[N],ans,cnt;

void dfs(int i,int k,int val){
    if(k>=ans)
        return;
    if(!val){
        if(k<ans)
            ans=k;
        return;
    }
    if(i == n+1)
        return;
    dfs(i+1,k+1,val%b[i]);
    dfs(i+1,k,val);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        scanf("%d%d",&n,&a);
        for(int i=1;i<=n;i++){
            scanf("%d",&b[i]);
            if(b[i]>a){
                n--;
                i--;
            }
        }
        sort(b+1,b+1+n,greater<int>());
        dfs(1,0,a);
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}

/*
//ac 15ms dfs���� ö������,���������ڱ����������Ҫ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,a,b[N],vis[N],cnt,ans;

void dfs(int k,int val){
    if(k>=ans)
        return;
    if(!val){
        if(k<ans)
            ans=k;
        return;
    }
    if(k == cnt+1)
        return;
    for(int i=1;i<=cnt;i++){
        if(!vis[i] && val>=b[i]){
            vis[i]=1;
            dfs(k+1,val%b[i]);
            vis[i]=0;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&a);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        sort(b+1,b+1+n);
        cnt=n;
        for(int i=1;i<=n;i++){
            if(b[i]>a){
                cnt=i-1;
                break;
            }
        }
        dfs(0,a);
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}
*/
