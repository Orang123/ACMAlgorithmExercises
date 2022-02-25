/*
����:n��Ŀγ�,ÿ����m��ʱ�䵥λ.�����n��m������01�ַ���,0����
��i�ǰʱ���û��,1�����п�.ÿ����ѧУ��ѧϰʱ��Ϊ�����һ�ڿ�
��ʱ���i�����һ�ڿ�ʱ��j��ʱ���,��j-i+1.�����������k�ڿ�,������
����ѧУ������ʱ��.
����:https://codeforces.ml/problemset/problem/946/D
˼·:���鱳��.��������Ϊ���̿εĴ�������k,��ÿһ�쵥����Ϊһ��,ÿ��
����Ʒ�ֱ�Ϊ�ڸ����ڿ����̿δ�����Ӧ����ܽ�ʡ��ʱ��.��dp֮ǰ��ҪԤ
�����ÿ������̿δ���������ܽ�ʡ��ʱ��,��ôʵ�ʼ����i��Ҫ��k�ſ�,
��ôֻ��ѡ���õ�ȫ�������˵��Ե�Ŀγ̲���ʹ�ý�ʡ�������ʱ��.����
������������ö��Ҫ�̿εĴ���j,��ö�پ����������l�ſ�,��ô�Ҷ˾�����
j-l�ſ�.֮����鱳������ǰn�����̿δ������Ϊk������ܽ�ʡ��ʱ�伴��,
���մ𰸾���n*m-dp[k].������������Ż���һά�ռ临�Ӷ�.

ע��:����dp[i][j]����ǰi����j�ſ�����ܽ�ʡ��ʱ�������ʱ,���Ҫ��һά
���������Ż�,����ÿһ����̿δ��� ����������ö��0..num���ܱ�֤,dp[j-k]
��ǰi-1�� dp[i-1][j-k]��״̬,�������,��ô�����������̿δ���Ϊ0ʱ,
dp[j-0]=dp[j],dp[j] �Ѿ���ǰ���i���̿δ��� num..1 ���¹���,���̿δ���
Ϊ0ʱ,dp[j]�Ѿ���ǰi���̿ε�״̬��.
*/
//ac 62ms һά����ʵ�� �Ż��ռ����� Ԥ����+���鱳��
//dp[i][j]����ǰi����j�ſ�����ܽ�ʡ��ʱ�� ʵ�ʹ�����������Ż�һά�ռ�dp[j]
//dp[j]=max(dp[j],dp[j-t]+val[i][t]);
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 510
#define M 510
#define INF 0x3f3f3f3f
using namespace std;

//val[i][j]�����i����j�ſ�����ܽ�ʡ��ʱ��
//pos[i][j]=t�����i���j+1�ſ��ڵ�i��ĵ�t��ʱ�����
//dp[i][j]����ǰi����j�ſ�����ܽ�ʡ��ʱ�� ʵ�ʹ�����������Ż�һά�ռ�dp[j]
int n,m,k,w[N][M],val[N][M],dp[M];
vector<int> pos[N];

int main(){
    char str[N];
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",str+1);
        for(int j=1;j<=m;j++){
            if(str[j] == '1')
                //��i���j��ʱ������Ͽ�ʱ��
                pos[i].push_back(j);
        }
    }
    //����val[i][j] ö�ٵ�i��
    for(int i=1;i<=n;i++){
        //��i�칲��siz�ſ�
        int siz=pos[i].size();
        //���̿δ�������Ϊkʱ,�������num�ſ�
        int num=min(k,siz);
        int mint=INF;
        //ö�ٵ�i����j�ſ�
        for(int j=0;j<=num;j++){
            if(j == siz){//��i���ȫ����,����ܽ�ʡmʱ���,��Ҫ�������� pos[i][siz-r-1]-pos[i][l]+1��ʽ�����,siz-r-1=-1.
                val[i][j]=m;
                break;
            }
            //m�ַ��������l�ſ�,�Ҷ���r=j-l�ſ�
            for(int l=0;l<=j;l++){
                int r=j-l;
                //�Ҷ��õ�r�ſ�,ʵ�ʵ�i���ϵ����һ�ſ�ʱ�����pos[i][siz-r-1]
                //����õ�l�ſ�,ʵ�ʵ�i���ϵĵ�һ�ſ�ʱ�����pos[i][l]
                //���ʵ���Ͽ�ʱ��Ϊpos[i][siz-r-1]-pos[i][l]+1
                //mint ��¼��i����j�ſ�����������Ͽ�ʱ��
                mint=min(mint,pos[i][siz-r-1]-pos[i][l]+1);
            }
            //ʵ�ʵ�i����j�ſ�����ܽ�ʡʱ����� mʱ����ȥ�����Ͽ�ʱ��
            val[i][j]=m-mint;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=k;j>=0;j--){//k�̿δ�������Ϊ0,j�½���0
            //��i��������̿δ���Ϊj�������Ͽ�������Сֵ num
            int num=min(j,(int)pos[i].size());
            //������������Ż� ���뱣֤t����,���ܱ�֤dp[j-k]��ǰi-1���״̬,����t=0ʱ,dp[j-0]�Ѿ���ǰi���̿ε�״̬��
            for(int t=0;t<=num;t++)
                //ע��������Ȼ��dp[j-t],��Ϊn��������Ͽ����� ���ܱ�kС,�����Ǿ����ܶ��װ������
                dp[j]=max(dp[j],dp[j-t]+val[i][t]);
        }
    }
    printf("%d",n*m-dp[k]);
    return 0;
}

/*
//ac 77ms ��ά����ʵ�� Ԥ����+���鱳��
//֮���Բ����ù��������Ż�����Ϊ,����������Сֵ,ʵ��k=0ʱ,һ�ڿβ���,dp[i][0]�Ͽ�ʱ��Ҳ��һֱ�ۼ������
//dp[i][j]����ǰi����j�ſ����ٵ��Ͽ�ʱ��
//dp[i][j]=min(dp[i][j],dp[i-1][j-t]+val[i][t]);
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 510
#define M 510
#define INF 0x3f3f3f3f
using namespace std;

//val[i][j]�����i����j�ſ�����ܽ�ʡ��ʱ��
//pos[i][j]=t�����i���j+1�ſ��ڵ�i��ĵ�t��ʱ�����
//dp[i][j]����ǰi����j�ſ����ٵ��Ͽ�ʱ��
int n,m,k,val[N][M],dp[N][M];
vector<int> pos[N];

int main(){
    char str[N];
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",str+1);
        for(int j=1;j<=m;j++){
            if(str[j] == '1')
                pos[i].push_back(j);
        }
    }
    memset(val,0x3f,sizeof(val));
    for(int i=1;i<=n;i++){
        int siz=pos[i].size();
        int num=min(k,siz);
        for(int j=0;j<=num;j++){
            if(j == siz){
                val[i][j]=0;
                break;
            }
            for(int l=0;l<=j;l++){
                int r=j-l;
                val[i][j]=min(val[i][j],pos[i][siz-r-1]-pos[i][l]+1);
            }
        }
    }
    memset(dp,0x3f,sizeof(dp));
    //ʵ����Ȼ�Ǿ����ܶ��װ������,��Ϊʵ��k�̿δ��������е��Ͽ���������,����ʣ��
    //��˳�ʼ״̬dp[0][0..k]���Ϸ�
    for(int i=0;i<=k;i++)
        dp[0][i]=0;
    //֮���Բ����ù��������Ż�����Ϊ,����������Сֵ,ʵ��k=0ʱ,һ�ڿβ���,dp[i][0]�Ͽ�ʱ��Ҳ��һֱ�ۼ������
    //���Ե�i���״̬����ȫ��INF��������.
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            int num=min(j,(int)pos[i].size());//��i������̿δ���
            for(int t=0;t<=num;t++)
                dp[i][j]=min(dp[i][j],dp[i-1][j-t]+val[i][t]);
        }
    }
    printf("%d",dp[n][k]);
    return 0;
}
*/

/*
//ac 140ms Ԥ����+���鱳��
//��һ��Ԥ���� �Ͽ�ʱ���ǰ׺��
//ժ�Բ���:https://blog.csdn.net/noone0/article/details/79466057
//dp[i][j]����ǰi����j�ſ����ٵ��Ͽ�ʱ��
//dp[i][j]=min(dp[i][j],dp[i-1][j-t]+val[i][t]);
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e2+5,inf=0x3f3f3f3f;
int f[N][N],d[N][N];
int n,m,k,p[N];
char s[N][N];
int main()
{
//	ios::sync_with_stdio(false);
//	cin.tie(0);
	cin>>n>>m>>k;
	memset(d,inf,sizeof(d));
	memset(f,inf,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		p[0]=0;
		for(int j=1;j<=m;j++)
			p[j]=p[j-1]+(s[i][j]=='1');
		f[i][p[m]]=0;
		for(int l=1;l<=m;l++)
		{
			for(int r=l;r<=m;r++)
			{
				int tot=p[l-1]+(p[m]-p[r]);
				if(p[r]-p[l-1])
					f[i][tot]=min(f[i][tot],r-l+1);
				else
					f[i][tot]=0;
			}
		}

	//	for(int j=0;j<=m;j++)
	//		cout<<i<<' '<<j<<' '<<f[i][j]<<'\n';
	}
	for(int j=0;j<=k;j++)
		d[0][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			for(int p=0;p<=j;p++)
				d[i][j]=min(d[i][j],d[i-1][p]+f[i][j-p]);
	cout<<d[n][k]<<'\n';
	return 0;
}
*/
