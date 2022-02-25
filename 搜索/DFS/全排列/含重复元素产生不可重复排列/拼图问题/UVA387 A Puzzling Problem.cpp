/*
����:ժ������
�ڶ�άƽ���ϷŲ�����ľ��ƴͼ�����������е�ƴͼ
��4��4��ƽ��ƴ����ע��ƴͼ������ת����ת������
���е�ƴͼ��Ҫ�õ���
ľ��ƴͼ�������16��,��Ϊÿ��ľ����С��1*1��������.
����:https://www.luogu.com.cn/problem/UVA387
˼·:���UVA 798 Tile Puzzle ƴͼ�Ǳ�׼�ľ���,������
ƴͼ����������ͼ��.UVA 798����ƴͼ�ķ���ֻ��2�ַ�ʽ,
Ҫô���Ҫô����,��˿��԰���dfs(x,y+1)��ʽö����(x,y)
λ�������ܷ��õ�����ƴͼ.��������Ϊƴͼ������,����˵��
�жϵ��Ƿ����(x,y)�Ѿ����ù�ƴͼ,������Ϊ��ǰҪ�ŵ�ƴͼ������,
���ʵ�����ж��ܷ��õĺϷ�λ��ʱ,��ǰ���õ�λ������'1',��Ȼ�Ѿ�
���ù����ƴͼ,���ǵ�ǰƴͼ����ռ�ݸ�λ��,������Ҫ��(x,y)���
���λ����ȷ����ƴͼ��η���,ʵ��ƴͼ��Чλ��'1'������͵�ǰ(x,y)
�ѷ��õ�ƴͼ��ͻ.
*/
//ac 30ms dfsö��ÿ��ƴͼcur���õ�λ��,��������ÿ��λ��ö�ٿ��ܷ��õ�ƴͼ
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5
using namespace std;

int n,mp[N][N];
struct A{
    int r,c;
    char a[N][N];
}shape[20];

//�ж�(x,y)Ϊ���λ���ܷ�����µ�k��ƴͼ
int check(int x,int y,int k){
    for(int i=1;i<=shape[k].r;i++){
        for(int j=1;j<=shape[k].c;j++){
            if(shape[k].a[i][j]-'0'){//��1��Чλ,���(x,y)λ��,ʵ����mp[x+i-1][y+j-1]λ��,��1����Ϊ(x,y)����ռ����һ�����еĵ�Ԫ��
                if(x+i-1>4 || y+j-1>4)
                    return 0;
                if(mp[x+i-1][y+j-1])
                    return 0;
            }
        }
    }
    return 1;
}

//�����ù�ƴͼ��λ������ ����Ϊƴͼ��Ż����ʱ�ָ�Ϊ0
void update(int x,int y,int k,int val){
    for(int i=1;i<=shape[k].r;i++){
        for(int j=1;j<=shape[k].c;j++){
            if(shape[k].a[i][j]-'0')
                mp[x+i-1][y+j-1]=val;
        }
    }
}

int dfs(int cur){
    if(cur == n+1){//n��ƴͼ�������,�ж�4*4�����Ƿ�ȫ������
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(!mp[i][j])
                    return 0;
            }
        }
        return 1;
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            //���������ж�mp[x][y]�Ƿ��Ѿ����ù�ƴͼ,��Ϊ��ǰcurƴͼ����Чλ1 ���ܲ���ռ�ݵ�ǰ(x,y)λ��
            if(check(i,j,cur)){
                update(i,j,cur,cur);
                if(dfs(cur+1))
                    return 1;
                update(i,j,cur,0);
            }
        }
    }
    return 0;
}

int main(){
    int flag=0;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&shape[i].r,&shape[i].c);
            for(int j=1;j<=shape[i].r;j++){
                for(int k=1;k<=shape[i].c;k++)
                    scanf(" %c",&shape[i].a[j][k]);
            }
        }
        if(flag)
            printf("\n");
        if(dfs(1)){
            for(int i=1;i<=4;i++){
                for(int j=1;j<=4;j++)
                    printf("%d",mp[i][j]);
                printf("\n");
            }
        }
        else
            printf("No solution possible\n");
        flag=1;
    }
    return 0;
}

/*
//ac 30ms �±��0��ʼ
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 4
using namespace std;

int n,mp[N][N];
struct A{
    int r,c;
    char a[N][N];
}shape[20];

int check(int x,int y,int k){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0'){
                if(x+i>=4 || y+j>=4)
                    return 0;
                if(mp[x+i][y+j])
                    return 0;
            }
        }
    }
    return 1;
}

void update(int x,int y,int k,int val){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0')
                mp[x+i][y+j]=val;
        }
    }
}

int dfs(int cur){
    if(cur == n+1){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(!mp[i][j])
                    return 0;
            }
        }
        return 1;
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(check(i,j,cur)){
                update(i,j,cur,cur);
                if(dfs(cur+1))
                    return 1;
                update(i,j,cur,0);
            }
        }
    }
    return 0;
}

int main(){
    int flag=0;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&shape[i].r,&shape[i].c);
            for(int j=0;j<shape[i].r;j++){
                for(int k=0;k<shape[i].c;k++)
                    scanf(" %c",&shape[i].a[j][k]);
            }
        }
        if(flag)
            printf("\n");
        if(dfs(1)){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++)
                    printf("%d",mp[i][j]);
                printf("\n");
            }
        }
        else
            printf("No solution possible\n");
        flag=1;
    }
    return 0;
}
*/

/*
//wa ��ÿ��λ��ö�����ܷ��õ�ƴͼ,�����������(x,y)��ռ�ݵ���������������(x,y+1)�ж�,�����
//��������������ܹ�,���ǽ���ȥ��wa,��֪��ԭ��
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5//N����Ϊ4 �������ͻ��,�����������,��֪��ԭ��
using namespace std;

int n,mp[N][N],vis[N];
struct A{
    int r,c;
    char a[N][N];
}shape[20];

int check(int x,int y,int k){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0'){
                if(x+i>=4 || y+j>=4)
                    return 0;
                if(mp[x+i][y+j])
                    return 0;
            }
        }
    }
    return 1;
}

void update(int x,int y,int k,int val){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0')
                mp[x+i][y+j]=val;
        }
    }
}

int dfs(int x,int y){
	if(y == 4){
		x++;
		y=0;
	}
	if(x == 4){
		for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(!mp[i][j])
                    return 0;
            }
        }
        return 1;
	}
    for(int i=1;i<=n;i++){
    	if(!vis[i] && check(x,y,i)){
    		vis[i]=1;
    		update(x,y,i,i);
    		if(dfs(x,y+1))
    			return 1;
    		update(x,y,i,0);
    		vis[i]=0;
		}
	}
	if(dfs(x,y+1))//������(x,y)�Ƿ���ù�ƴͼ,ֱ�����½����ж�
		return 1;
    return 0;
}

int main(){
    int flag=0;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&shape[i].r,&shape[i].c);
            for(int j=0;j<shape[i].r;j++){
                for(int k=0;k<shape[i].c;k++)
                    scanf(" %c",&shape[i].a[j][k]);
            }
        }
        if(flag)
            printf("\n");
        if(dfs(0,0)){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++)
                    printf("%d",mp[i][j]);
                printf("\n");
            }
        }
        else
            printf("No solution possible\n");
        flag=1;
    }
    return 0;
}
*/
