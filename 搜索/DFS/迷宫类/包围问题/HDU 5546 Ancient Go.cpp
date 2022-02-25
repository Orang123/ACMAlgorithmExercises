/*
����:8*8������,'x'��'o'�ֱ���������˵��壬��Ϸ
�������Χ��,'.'����������ĸ���,��x����һ����
�ܲ���ɱ��o������һ������,����˵'X'Ҫ���ܹ�Χ������
'O'��ȫΧס,XΧס�Ĳ��ֲ�����'.'�հ׸���.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5546
˼·:���Կ���ö��ÿ��'O',��'O'��ʼdfs,����'O'��������,
����'.'ֹͣ,ͳ������'.'����Ŀ,���������1��,�򲻻ᱻ1��'X'
Χס,�������'.'����ǡ�õ���1��,����Ա�Χס.
*/
//ac 15ms dfs
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
char mp[11][11];
int vis[11][11],cnt,num;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct Node{
    int x,y;
}node[100];
int judge(int x,int y){
    if(x>=1 && x<=9 && y>=1 &&y<=9) return 1;
    else return 0;
}
//�ж���'o'���ӵ���ͨ����Χ�Ƿ���ֻ��һ��'.'��˵������
int dfs(int x,int y){
    int x0,y0;
    for(int i=0;i<4;i++){
        x0=x+dir[i][0];
        y0=y+dir[i][1];
        if(judge(x0,y0)){
            if(mp[x0][y0]=='o' && !vis[x0][y0]){
                vis[x0][y0]=1;
                if(dfs(x0,y0)) return 1;
            }
            if(mp[x0][y0]=='.' && !vis[x0][y0]){//ͬһ����ͨ�鲻����������ͬһ����.'
                vis[x0][y0]=1;
                cnt++;
            }
            if(cnt>1) return 1;
        }
    }
    return 0;
}

int main(){
    int T,num,cas=0,flag;
    scanf("%d",&T);
    while(T--){
        cas++;
        num=0;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cin >> mp[i][j];
                if(mp[i][j] == 'o') node[num].x=i,node[num++].y=j;
            }
        }
        flag=0;
        for(int i=0;i<num;i++){
            cnt=0;
            //����ÿ�ζ�Ҫ��ʼ��vis,��Ϊ�ϴλ��'.'���Ϊ�ѷ���,��Ӱ����һ�ζ�'.'��ͳ��
            memset(vis,0,sizeof(vis));
            vis[node[i].x][node[i].y]=1;
            dfs(node[i].x,node[i].y);
            if(cnt == 1){
                flag=1;
                break;
            }
        }
        if(flag)
            printf("Case #%d: Can kill in one move!!!\n",cas);
        else
            printf("Case #%d: Can not kill in one move!!!\n",cas);
    }
    return 0;
}
/*
//ac 0ms bfs�汾
#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
char mp[11][11];
int vis[11][11],cnt;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct Node{
    int x,y;
}node[100];
int judge(int x,int y){
    if(x>=1 && x<=9 && y>=1 &&y<=9) return 1;
    else return 0;
}
int bfs(int x,int y){
    queue<Node> Q;
    Node now,tmp;
    tmp.x=x,tmp.y=y;
    Q.push(tmp);
    int x0,y0;
    while(!Q.empty()){
        tmp=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            x0=tmp.x+dir[i][0];
            y0=tmp.y+dir[i][1];
            if(judge(x0,y0)){
                if(mp[x0][y0]=='o' && !vis[x0][y0]){
                    vis[x0][y0]=1;
                    now.x=x0,now.y=y0;
                    Q.push(now);
                }
                if(mp[x0][y0]=='.' && !vis[x0][y0]){
                    vis[x0][y0]=1;
                    cnt++;
                    if(cnt>1) return 1;
                }
            }
        }
    }
    return 0;
}

int main(){
    int T,num,cas=0,flag;
    scanf("%d",&T);
    while(T--){
        cas++;
        num=0;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cin >> mp[i][j];
                if(mp[i][j] == 'o') node[num].x=i,node[num++].y=j;
            }
        }
        flag=0;
        for(int i=0;i<num;i++){
            memset(vis,0,sizeof(vis));
            cnt=0;
            vis[node[i].x][node[i].y]=1;
            bfs(node[i].x,node[i].y);
            if(cnt == 1){
                flag=1;
                break;

            }
        }
        if(flag)
            printf("Case #%d: Can kill in one move!!!\n",cas);
        else
            printf("Case #%d: Can not kill in one move!!!\n",cas);
    }
    return 0;
}
*/
