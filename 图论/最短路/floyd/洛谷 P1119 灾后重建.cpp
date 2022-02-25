#include<iostream>
#include<cstdio>
#define N 205
using namespace std;
int n,m;
int a[N];
int f[N][N];//邻接矩阵存边
inline void updata(int k){
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	if(f[i][j]>f[i][k]+f[j][k])
	f[i][j]=f[j][i]=f[i][k]+f[j][k];//用这个新的更新所有前面的
	return;
}
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
	scanf("%d",a+i);//依次输入每一个村庄建立完成时需要的时间
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++){
		f[i][j]=1e9;//初始化为保证它不爆炸范围内的最大值
	}
	for(int i=0;i<n;i++)
	f[i][i]=0;
	int s1,s2,s3;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&s1,&s2,&s3);
		f[s1][s2]=f[s2][s1]=s3;//初始化边长
	}
	int q;
	cin>>q;
	int now=0;
	for(int i=1;i<=q;i++){//处理各询问
		scanf("%d%d%d",&s1,&s2,&s3);
		while(a[now]<=s3&&now<n){
			updata(now);//依次更新点，使它可以被用来更新其他的点
			now++;
		}
		if(a[s1]>s3||a[s2]>s3)cout<<-1<<endl;
		else {
			if(f[s1][s2]==1e9)cout<<-1<<endl;
			else cout<<f[s1][s2]<<endl;
		}
	}
	return 0;
}
