/*
����:ժ������
һ����n���ڵ������ͼ��Ҫ���ÿ���ڵ����Ⱦɫ��
ʹ�����������ڵ���ɫ����ͬ����������Ҫ��������ɫ��
n<=26.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1373
˼·:̰��,��ʼ������ɫ��ĿΪ1,ֻ�е���ǰ�ڵ�Ⱦɫʱ,����
��ɫ��������������ڽڵ���ɫ��ͬʱ,����һ����ɫ,ֱ����
���нڵ�Ⱦɫ���,��ǰ��ɫ����Ŀ�������ٵ�.
ʵ��������� ֱ��2��ѭ��Ҳ����,������Ҫdfs����.
��Ϊdfs(cur+1,num) ʵ�ʲ��������
*/
//ac 0ms dfs����ö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
using namespace std;

int n,mp[N][N],col[N],flag,ans;
char str[N];

int check(int cur,int x){
    for(int i=0;i<n;i++){//����ʵ��Ӧ����i<cur,��Ϊi>cur�Ĳ��ֻ�δȾɫ
        if(mp[cur][i] && col[i] == x)
            return 0;
    }
    return 1;
}

void dfs(int cur,int num){
    if(cur == n){
        flag=1;
        return;
    }
    //��ǰ���Ľڵ��num�ǽ��ٵ�,��������i == num��ʱ��,ֻ���� ������ɫ��ͻ��ʱ�� �Ż�����һ����ɫ
    for(int i=1;i<=num;i++){
        if(check(cur,i)){//�ж����ڽڵ��Ƿ��� Ⱦi��ɫ��,��û�������Ⱦ
            col[cur]=i;
            dfs(cur+1,num);//ʵ�����ﲻ���л���(����Ҳû����,��Ϊǰ���ڵ�Ҳû�б����ɫ��ѡ),ֻ��û����ɫ�������ڲ�ͬɫʱ,�������������һ����ɫdfs(cur,ans)
            if(flag) return;//Ⱦɫ�ɹ���ֱ�� ����
        }
    }
    //�����ǵ�ǰnum����ɫ����������cur��cur���ڽڵ���ɫ��ͬʱ,������һ����ɫ.
    //ʵ�����ﲢ���ǻ��ݻ�����,���������dfs(cur+1,num) û����������ʱ�Ż�������ɫ��Ŀdfs(cur,ans)
    ans++;
    dfs(cur,ans);
}

int main(){
    int u,v,len;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        memset(col,0,sizeof(col));
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            u=str[0]-'A';
            len=strlen(str);
            for(int j=2;j<len;j++){
                v=str[j]-'A';
                mp[u][v]=1;
            }
        }
        flag=0;
        ans=1;//������Ҫһ����ɫ.
        dfs(0,1);
        if(ans == 1)
            printf("1 channel needed.\n");
        else
            printf("%d channels needed.\n",ans);
    }
    return 0;
}

/*
//ac 0ms �ǵݹ�,2��ѭ�� ̰��+����ö��.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
using namespace std;

int n,mp[N][N],col[N],flag,ans;
char str[N];

int check(int cur,int x){
    for(int i=0;i<n;i++){
        if(mp[cur][i] && col[i] == x)
            return 0;
    }
    return 1;
}

int main(){
    int u,v,len;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        memset(col,0,sizeof(col));
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            u=str[0]-'A';
            len=strlen(str);
            for(int j=2;j<len;j++){
                v=str[j]-'A';
                mp[u][v]=1;
            }
        }
        ans=1;//������Ҫһ����ɫ.
        for(int i=0;i<n;i++){
        	flag=0;
        	for(int j=1;j<=ans;j++){
        		if(check(i,j)){
        			col[i]=j;
        			flag=1;
        			break;
				}
			}
			if(!flag){//û��һ����ɫ�������ڽڵ� ��ɫ��ͬ,����һ����ɫ,�����жϸõ�i Ⱦɫ���
				i--;
				ans++;
			}
		}
        if(ans == 1)
            printf("1 channel needed.\n");
        else
            printf("%d channels needed.\n",ans);
    }
    return 0;
}
*/

/*
//��ɫ����
//ժ�Բ���:https://blog.csdn.net/lyy289065406/article/details/6647986
//Memory Time
//184K   0MS

#include<iostream>
using namespace std;

typedef class
{
	public:
		int next[27];  //ֱ�Ӻ��
		int pn;   //next[]ָ�루��̸�����
}point;

int main(int i,int j,int k)
{
	int n;
	while(cin>>n)
	{
		if(!n)
			break;

		getchar();  //n�Ļ��з�

		point* node=new point[n+1];  //���


		for(i=1;i<=n;i++)
		{
			getchar();  //������
			getchar();  //ð��

			if(node[i].pn<0)   //��ʼ��ָ��
				node[i].pn=0;

			char ch;
			while((ch=getchar())!='\n')
			{
				j=ch%('A'-1);   //�ѽ����ĸת��Ϊ��Ӧ�����֣���A->1  C->3
				node[i].next[ ++node[i].pn ]=j;
			}
		}

		int color[27]={0};  //color[i]Ϊ��i����㵱ǰȾ����ɫ��0Ϊ��ɫ����Ⱦɫ��
		color[1]=1;  //���A��ʼ��Ⱦ��1��ɫ
		int maxcolor=1;  //��ǰ��ʹ�ò�ͬ��ɫ������

		for(i=1;i<=n;i++)  //ö��ÿ������
		{
			color[i]=n+1;  //�ȼ�����iȾ������ɫ
			bool vist[27]={false};  //��ǵ�i����ɫ�Ƿ��ڵ�ǰ�������ڽ��Ⱦ��
			for(j=1;j<=node[i].pn;j++) //ö�ٶ���i�����к��
			{
				int k=node[i].next[j];
				if(color[k])  //����i�ĵ�j��ֱ�Ӻ����Ⱦɫ
					vist[ color[k] ]=true;  //��Ǹ�����ɫ
			}
			for(j=1;i<=n;j++)  //����С����ɫ��ʼ��ö��ÿ����ɫ
				if(!vist[j] && color[i]>j) //ע��Ⱦɫ�Ĺ�����һ�����ϵ����Ĺ��̣����ܻ���ʱ���ִ���4����ɫ
				{                          //��˲��ܵ���ö��4��ɫ����Ȼ��WA
					color[i]=j;
					break;
				}

			if(maxcolor<color[i])
			{
				maxcolor=color[i];
				if(maxcolor==4)   //����ɫ����֪���������Ⱦɫ��ͼ�����ֻ��������ɫ
					break;        //��˵�Ⱦɫ���̳��ֽ�����ɫΪ4ʱ���Ϳ��Զ϶�����Ҫ��4����ɫȾɫ
			}
		}

		if(maxcolor==1)
			cout<<1<<" channel needed."<<endl;
		else
			cout<<maxcolor<<" channels needed."<<endl;

		delete node;
	}
	return 0;
}
*/
