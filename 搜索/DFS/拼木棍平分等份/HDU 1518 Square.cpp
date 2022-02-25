/*
����:ժ������
n�����ӣ�Ҫ�����еĹ��Ӷ����ϣ�ƴ��һ�������Ρ�
n<=20.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1518
˼·:��Ҫö��ÿ��������Щ����ƴ��,�����������˵,ͬһ��
���ϵĹ��� ��ѡȡ˳���޹�,ֻ���ھ���ѡ����Щ����,��˶���
��ͬ�ı�����ϵĹ�������������,������ͬһ�����ϵĹ�����
�౳��ѡȡ��������,���Զ����µı�(����Ϊ0ʱ)ö�ٵ��½�
�Ǵӵ�һ�����ӿ�ʼ,������һ����������ö�ٵĹ���Ӧ���ǽ�����һ��
ö�ٵĹ��ӵ�.
��4����֦:
1.�������ܳ���������4ʱ,���ܹ���������.
2.����Ĺ��Ӵ��ڱ߳�ʱ,���ܹ���������.
3.����ͬһλ��ö����ͬ���ȵĹ���ʱ �����ظ�����Ҫȥ��.
��ǰ���Ⱥ�ǰһ��һ����ǰһ����ʹ�ã���ǰҲ��ʹ��
4.���ܴճ������Ϸ���ʱ,ʣ��һ����һ���ܴճ���.

����2����֦ͬUVA 307 Sticks
1.!len ��ʼ��0��ʼʧ�� ֱ�ӷ���0
2.a[i]+len == b ����ʧ�� ֱ�ӷ���0
*/
//ac 483ms dfs����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],vis[N],sum,b;

int dfs(int len,int pos,int k){
    if(k == 3)//���ܴճ������Ϸ���ʱ,ʣ��һ����һ���ܴճ���.
        return 1;
    for(int i=pos;i<=n;i++){
        if(!vis[i]){
            //��ǰ���Ⱥ�ǰһ��һ����ǰһ����ʹ�ã���ǰҲ��ʹ��
            if(a[i] == a[i-1] && !vis[i-1])//��i-1�����ӱ���δʹ��,���ڵ�ǰdfsѭ����,�����ǰһ����dfs��i-1��ʹ�õ� ���ǿ��Ե�.
                continue;
            if(len+a[i]>b)//���ӳ����������,�����ǰ��i�����ϴ��ڱ߳�,ʣ�µ�Ҳ��Ȼ���ڱ߳�,ֱ�ӷ���
                break;
            vis[i]=1;
            if(len+a[i]<b){//ͬһ�����ϼ��� ���������Ĺ���i+1��� �ۼ�
                if(dfs(len+a[i],i+1,k))
                    return 1;
            }
            else if(len+a[i] == b){//��ǰ���Ѿ��ճ���,Ҫ���µı�,ö�ٹ��ӵ�˳��ӵ�һ�����ӿ�ʼ
                if(dfs(0,1,k+1))
                    return 1;
            }
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        b=sum/4;
        if(sum%4 || a[n]>b){
            printf("no\n");
            continue;
        }
        if(dfs(0,1,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}

/*
//ac 343ms dfs+4��֦
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],vis[N],sum,b;

int dfs(int len,int pos,int k){
    //��֦1
    if(k == 3)//���ܴճ������Ϸ���ʱ,ʣ��һ����һ���ܴճ���.
        return 1;
    for(int i=pos;i<=n;i++){
        if(vis[i]) continue;
        vis[i]=1;
        if(a[i]+len<b){//ͬһ�����ϼ��� ���������Ĺ���i+1��� �ۼ�
            if(dfs(len+a[i],i+1,k))
                return 1;
        }
        else if(a[i]+len  == b){//��ǰ���Ѿ��ճ���,Ҫ���µı�,ö�ٹ��ӵ�˳��ӵ�һ�����ӿ�ʼ
            if(dfs(0,1,k+1))
                return 1;
        }
        vis[i]=0;
        //��֦2��3
        if(!len || a[i]+len == b)
            return 0;
        //��֦4
        while(i+1<=n && a[i] == a[i+1])
            i++;
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        b=sum/4;
        if(sum%4 || a[n]>b){
            printf("no\n");
            continue;
        }
        if(dfs(0,1,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
*/

/*
//ac 608ms dfs+4��֦
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

int n,a[N],vis[N],sum,b;

int dfs(int len,int i,int k){
    //��֦1
    if(k == 3)//���ܴճ������Ϸ���ʱ,ʣ��һ����һ���ܴճ���.
        return 1;
    if(i == n+1)
        return 0;
    if(!vis[i]){
        vis[i]=1;
        if(a[i]+len<b){//ͬһ�����ϼ��� ���������Ĺ���i+1��� �ۼ�
            if(dfs(len+a[i],i+1,k))
                return 1;
        }
        else if(a[i]+len  == b){//��ǰ���Ѿ��ճ���,Ҫ���µı�,ö�ٹ��ӵ�˳��ӵ�һ�����ӿ�ʼ
            if(dfs(0,1,k+1))
                return 1;
        }
        vis[i]=0;
        //��֦2��3
        if(!len || a[i]+len == b)
            return 0;
        //��֦4
        while(i+1<=n && a[i] == a[i+1])
            i++;
    }
    if(dfs(len,i+1,k))
        return 1;
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        b=sum/4;
        if(sum%4 || a[n]>b){
            printf("no\n");
            continue;
        }
        if(dfs(0,1,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
*/
