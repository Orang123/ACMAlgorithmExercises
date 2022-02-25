/*
����:ũ�� John ��ӵ���������������ţΪ������֪��ÿ����������������ţ
�������͵�ά�������Ƕ��١��������ũ��ι������ţ���Ա������ǵĽ�����
ʹι��ţ�����ϵ��������١�����ţ�������͵�ά�����������ι��ţ��Ҫ��Щ
��������ϣ�����������ϼ������١�ά��������������ʾ��ÿ���������ֻ�ܶ�
ţʹ��һ�Σ����ݱ�֤���ڽ⡣
ά��������<=25,��������<=15.
˵��:ʵ�ʴ𰸲�û��Ҫ���ڸ�����ͬʱ ��������.
����:https://www.luogu.com.cn/problem/P1460
˼·:
�ⷨ1:dfs
dfs,ֻ�����ǽ����ϵ��ṩ��ά�����ֿ�����һ������,�жϵ�����������ά����
�������Ƿ���.

�ⷨ2:bfs.
״̬�����ö�����λ�����ʾ�Ѿ�ѡȡ������,ÿ����չֻѡȡһ����δѡȡ������(�����ֵ���),
Ȼ������������ǵ�ǰ����ά������ָ���Ѿ����,��һ�����ľ���������С,�ֵ�����С�ķ���.
bfs���ķѿռ�.
*/
//ac dfs
#include<cstdio>
#include<algorithm>
using namespace std;
int a[20][30],b[30],c[20],ans[20];
int v,g,cnt,num=100;
/*
����ֻ�Ƕ���ÿ������ ѡȡ��ѡȡ(��ѡȡ��˳���޹�,֮����Ͼ���������й�,��������ٿ���ǰ��ȡ���ı��),
����Ҫ��vis�����,˳��u+1��˳�� ����ʱ ������ܸ����������,������ȫ�������� ��ѡȡĳ��λ�ú�,
ѡȡĳ����˳��Ҳ�Խ����Ӱ��ʱ,��ȱ���Ҳ��Ҫ����ǰ��ȡ���ı����.
*/
void dfs(int u,int k){
    int flag=0;
    for(int i=1;i<=v;i++){
        if(b[i]>a[0][i]){
            flag=1;
            break;
        }
    }
    if(!flag){
        if(k-1<num){
            num=k-1;
            //ֻ�е��и�������������������ʱ�Ÿ��´�,dfs������ǰ����ֵ���ȥͳ�ƽ����,�����ϸ�����ͬ�����,������������Ľ�� �ֵ����С
            for(int i=1;i<=num;i++)
                ans[i]=c[i];
        }
        return;
    }
    if(u == g+1) return;
    for(int j=1;j<=v;j++)
        a[0][j]+=a[u][j];
    c[k]=u;
    dfs(u+1,k+1);
    for(int j=1;j<=v;j++)
        a[0][j]-=a[u][j];
    dfs(u+1,k);//֮������Ҫ��ѡu��� �������,����Ϊ�п����ֵ���ϴ� ����ѡȡ�������������.
}

int main(){
    scanf("%d",&v);
    for(int i=1;i<=v;i++)
        scanf("%d",&b[i]);
    scanf("%d",&g);
    for(int i=1;i<=g;i++)
        for(int j=1;j<=v;j++)
            scanf("%d",&a[i][j]);
    dfs(1,1);
    printf("%d",num);
    for(int i=1;i<=num;i++)
        printf(" %d",ans[i]);
    printf("\n");
    return 0;
}

/*
//ac ������ö��ѡȡ״̬
//ժ���������
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int v,need[30],g,a[20][30],ans,minn=0x7fffffff,t[30];

int count(int x);

int main()
{
    int i,j,k;
    bool flag;

    cin>>v;

    for (i=0;i<v;++i)
    {
        cin>>need[i];
    }

    cin>>g;

    for (i=1;i<=g;++i)
    {
        for (j=0;j<v;++j)
        {
            cin>>a[i][j];
        }
    }

    for (i=(1<<g)-1;i>=0;--i) //������ö���Ӽ�
    {
        if (count(i)<minn) //����ǰ�Ӽ������������ڵ��ڵ�ǰ�����Ž���ǰ�Ӽ�һ�����Ǵ�
        {
            memset(t,0,sizeof(t));
            for (j=0;j<g;++j)
            {
                if ((1<<j)&i) //i��������j+1λΪ1��������g-j�ڵ�ǰö�ٵ��Ӽ���
                {
                    for (k=0;k<v;++k)
                    {
                        t[k]+=a[g-j][k];
                    }
                }
            }
            flag=true;
            for (j=0;j<v;++j) //�жϵ�ǰ�����Ƿ�Ϸ�
            {
                if (t[j]<need[j])
                {
                    flag=false;
                    break;
                }
            }
            if (flag) //��Ϊ�Ѿ��жϹ���ǰ�Ӽ�������С�ڵ�ǰ���Ž⣬����ǰ�����Ϸ���ֱ�Ӹ������Ž�
            {
                minn=count(i);
                ans=i;
            }
        }
    }

    cout<<minn;

    for (i=g-1;i>=0;--i) //�������
    {
        if ((1<<i)&ans)
        {
            cout<<" "<<g-i;
        }
    }

    return 0;
}

int count(int x) //��1�ĸ���
{
    int out=0;
    while (x)
    {
        out+=x&1;
        x>>=1;
    }
    return out;
}
*/

/*
//ac BFS�汾
//�������ժ����һ���汾
#include<iostream>
#include<queue>
using namespace std;
int a[30][30],b[30];
int n,m;
struct node{
	int wss[30];
	int num[30];
	int ans;
}q;
void bfs()
{
	queue<node>que;
	q=que.front();
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			q.wss[j]=a[i][j];//��һ��ѡ������� ����1��mһ��ö�����
		q.num[1]=i;//num�ǽ�����Ҫѡ�����ϴ��ĸ��±꿪ʼ
		q.ans=1;//ans��ѡ�����ϵĴ���
		que.push(q);
	}
	while(!que.empty())
	{
		node s,t;
		s=que.front();
		t=que.front();
		que.pop();
		bool w=1;
		for(int i=1;i<=n;i++)
		{
			if(s.wss[i]<b[i])
			{
				w=0;
				break;
			}
		}
		if(w==1)
		{
			cout<<s.ans<<' ';
			for(int i=1;i<=s.ans;i++)cout<<s.num[i]<<" ";
			return;
		}
//��s.num[s.ans]+1��ʼö�ٳ���Ϊs.ans+1�����������(��s.ans+1��������num+1��m֮����κ�һ��,�ֱ����),
//�����ͱ�֤�˶��г��ӵ�˳�� �ǰ����������� ���Ұ����ֵ��������,��ô��һ����������ľ�����Ҫ��ĵĽ� ��ֱ���˳�
		for(int i=s.num[s.ans]+1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
				t.wss[j]=s.wss[j]+a[i][j];
			t.ans=s.ans+1;
			t.num[t.ans]=i;
			que.push(t);
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b[i];
	cin>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	bfs();
	return 0;
}
*/
