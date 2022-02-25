/*
����:
һ������Ϊn���ַ���������h��1������ȫΪ0��,����ȫ���У�ע��Ҫ�����ֵ���
0<n<=16,0<h<=16.
����:https://www.luogu.com.cn/problem/UVA729
˼·:
����1:dfsö��ÿһλȡ0����1,��¼01�������Ƿ����Ҫ��.
����2:ֱ�Ӵӳ�ʼ�ֵ�������ö�ٲ����ظ���ȫ����.
*/
//ac 10ms dfsö��ÿһλȡ0����1,��¼01�������Ƿ����Ҫ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;

int n,h,vis[N];
char a[N];

void dfs(int k,int num){
    if(k == n+1){
        a[k]='\0';
        printf("%s\n",a+1);
        return;
    }
    if(k-num<=n-h){
        a[k]='0';
        dfs(k+1,num);
    }
    if(num+1<=h){
        a[k]='1';
        dfs(k+1,num+1);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&h);
        dfs(1,0);
        if(T)
            printf("\n");
    }
    return 0;
}

/*
//ac 20ms ö�ٲ����ظ�����,�жϵ�kλö�ٲ��ܺ�֮ǰö�ٵ��ظ�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;

int n,h,vis[N];
char a[N],b[N];

void dfs(int k){
    if(k == n+1){
        b[k]='\0';
        printf("%s\n",b+1);
        return;
    }
    for(int i=1;i<=n;i++){
    	if(!vis[i] && b[k]!=a[i]){
    		vis[i]=1;
    		b[k]=a[i];
    		dfs(k+1);
    		vis[i]=0;
		}
	}
	b[k]='\0';
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&h);
        for(int i=1;i<=n;i++){//��ʼ���б��뱣֤���ֵ���
        	if(i<=n-h)
        		a[i]='0';
        	else
        		a[i]='1';
		}
        dfs(1);
        if(T)
            printf("\n");
    }
    return 0;
}
*/
