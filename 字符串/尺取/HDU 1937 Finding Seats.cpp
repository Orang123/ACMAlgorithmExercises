/*
����:ժ������
����һ��n*m�ľ���ѡ��һ�������С���Ӿ���ʹ�����ڲ���.���ĸ���>=k��
n,m<=300.k<=n*m.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1937
˼·:�����ݳ�ԭ�����ֱ��ö������,��ҪO(n^4)���Ӷ�,��ȻTLE.
�����ó�ȡ�Ż��л��г�����ʱ��.
*/
//ac 483ms
//��ȡ����ʱ��ö����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define INF 0x3f3f3f3f
using namespace std;

//sum[i][j]��ʾ(1,1)��(i,j)����'.'�ĸ���.
int n,m,k,sum[N][N],ans;

int main(){
    char x;
    int l,r;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        memset(sum,0,sizeof(sum));//����ʼ��sum��wa,�������ǲ��ó�ʼ����
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '.')
                    sum[i][j]=1;
                else
                    sum[i][j]=0;
                sum[i][j]+=sum[i][j-1];//�ۼ�ͬһ������'.'�ĸ���
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                sum[i][j]+=sum[i-1][j];//�ۼ�ͬһ������'.'�ĸ���
        }
        ans=n*m;
        for(int i=1;i<=n;i++){//ö����
            for(int j=i;j<=n;j++){
                l=r=1;//Ӧ�ó�ȡ ����ʱ��ö����
                while(r<=m){
                    //�������ݳ�ԭ�� sum[i-1][l-1]�������һ�����Ҫ�ټ���
                    //�����kС,�������еķ�Χr �����������
                    while(r<=m && sum[j][r]-sum[j][l-1]-sum[i-1][r]+sum[i-1][l-1]<k)
                        r++;
                    if(sum[j][r]-sum[j][l-1]-sum[i-1][r]+sum[i-1][l-1]>=k)
                        ans=min(ans,(j-i+1)*(r-l+1));
                    l++;//������߽��еķ�Χ������С����
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 592ms
//��ȡ����ʱ��ö����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
using namespace std;

int n,m,k,sum[N][N],ans;

int main(){
    char x;
    int l,r;
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
    	memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '.')
                    sum[i][j]=1;
                else
                    sum[i][j]=0;
                sum[i][j]+=sum[i][j-1];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                sum[i][j]+=sum[i-1][j];
        }
        ans=n*m;
        for(int i=1;i<=m;i++){//ö����
            for(int j=i;j<=m;j++){
                l=r=1;//Ӧ�ó�ȡ ����ʱ��ö����
                while(r<=n){
                    while(r<=n && sum[r][j]-sum[r][i-1]-sum[l-1][j]+sum[l-1][i-1]<k)
                        r++;
                    if(sum[r][j]-sum[r][i-1]-sum[l-1][j]+sum[l-1][i-1]>=k)
                        ans=min(ans,(j-i+1)*(r-l+1));
                    l++;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
