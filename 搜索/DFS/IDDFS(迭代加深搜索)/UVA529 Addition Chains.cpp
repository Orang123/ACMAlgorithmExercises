/*
����:
a[0]=1 a[m]=n,a����Ϊ�ϸ��������, ����������±�k��[1��m]�ڣ�
������1<=j<=i<=k-1ʹ�� a[i]+a[j]=a[k],�ҳ�m��С�ķ������������У�
��������С�����С�
n<=10000.
����:https://www.luogu.com.cn/problem/UVA529
˼·:ͬUVA1374 Power Calculus,��ͬ����ö����һ����a[k+1]��ʱ��,�Ǵ�[1,k]��
ѡ������������,�����Ƕ������ѭ��.
*/
//ac 0ms IDA*
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100
using namespace std;

int n,a[N];

int dfs(int k,int dep){
    if(a[k] == n)
        return 1;
    if(a[k] << (dep-k) < n)
        return 0;
    for(int i=k;i>=1;i--){
        for(int j=i;j>=1;j--){
            a[k+1]=a[i]+a[j];
            if(a[k+1]<=a[k] || a[k]>n)
                continue;
            if(dfs(k+1,dep))
                return 1;
        }
    }
    return 0;
}

int main(){
    a[1]=1;
    while(scanf("%d",&n) && n){
        for(int i=1;;i++){
            if(dfs(1,i)){
                for(int j=1;j<=i;j++){
                    if(j == 1)
                        printf("%d",a[j]);
                    else
                        printf(" %d",a[j]);
                }
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

/*
����bfs����ģ��״̬,���ö�״̬��������
*/

/*
//ac 230ms dfs����+��֦
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],b[N],ans;

void dfs(int k){
    if(a[k] == n){
    	if(k<ans){
    		ans=k;
    		for(int i=1;i<=k;i++)
    			b[i]=a[i];
		}
        return;
	}
	//��ǰ��a[k] ����(ans-k)�������ۼ�ĩβ������ͬ��a[k]  �õ��Ľ����n��С�� ����
	if(a[k] << (ans-k) < n)//�����֦�кܴ�ȷ����,��������������ĳ��Ƚϴ� �����֦�ĸ�Ч��Ҳ�޷���֤
		return;
    for(int i=k;i>=1;i--){
        for(int j=i;j>=1;j--){
            a[k+1]=a[i]+a[j];
            if(a[k+1]<=a[k] || a[k]>n)
                continue;
            dfs(k+1);
        }
    }
}

int main(){
    a[1]=1;
    while(scanf("%d",&n) && n){
    	ans=INF;
    	dfs(1);
    	for(int i=1;i<=ans;i++){
        	if(i == 1)
                printf("%d",b[i]);
            else
                printf(" %d",b[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
