/*
����:ժ������
��������������������У���������Ϊ1�ĵ���
��������<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5904
˼·:LCIS.
*/
//ac 343ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

//a[x]��ʾa�������е���+1����ֹ����ֵx����󳤶�
//b[x]��ʾb�������е���+1����ֹ����ֵx����󳤶�
int n,m,a[N],b[N],ans;

int main(){
    int T,x;
    scanf("%d",&T);
    while(T--){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        ans=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            a[x]=a[x-1]+1;
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&x);
            b[x]=b[x-1]+1;
            //min(a[x],b[x])����Сֵ��ʾ�ڵ����������й����������е���󳤶�
            ans=max(ans,min(a[x],b[x]));
        }
        printf("%d\n",ans);
    }
    return 0;
}
