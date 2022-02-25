#include<cstdio>
#include<cstring>
#include<vector>
#define N 6//��������С ���Ա�������ö�����з��õﱤ���е�λ��Ҳ�ǿ��Ե�
using namespace std;
//ac 0ms ����ͼ���ƥ��
/*
����:n*n������������,�пյ�'.'��ǽ'X'���,����Ҫ�ڿյ�
�Ϸ��õﱤ,�ﱤ������ͬһ��ͬһ�����,�����ӵ��ᱻǽ��ס,
Ҳ����ǽ�Ὣͬһ�к�ͬһ�е�2���ﱤ�������������໥���,
������n*n����������ܷ��ö��ٸ��ﱤʹ������֮�����������໥�����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1045
˼·:���Խ��HDU 1281�����л���˼ά,��Ϊǽ���Ը���2���ﱤ��������֮�����,
���Կ��Խ�ǽ��'X'�ָ������ͨ�顢����ͨ����Ϊ�м��Ϻ��м����еĽڵ����ò�ͬ�ı��,
�����Ϸ��ĵﱤλ�ö�Ӧ������ͨ�������ͨ��ı��idx,idyһ���ǻ�����ͬ��,����ת��Ϊ��
ƥ������,֮��������ͼ���ƥ�伴��.
��Ϊ���ֻ����6*6����,���Ա�������ö�����з��õﱤ���е�λ��Ҳ�ǿ��Ե�
*/
int n,vis[N*N],match[N*N],row[N][N],col[N][N],idx,idy,ans;
char mp[N][N];
vector<int> G[N*N];

int dfs(int u){
    for(int &v : G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=0;
    idx=idy=1;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n*n;i++) G[i].clear();
}

int main(){
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == 'X') continue;//ֻ��'.'�յؿɷ��õﱤ
                //����������һ�л���һ��λ��mp[i][j-1]��ǽ'X'����ʱ,���������µ�����ͨ��,���idx+1
                if(j == 1 || mp[i][j-1] == 'X')
                    idx++;
                row[i][j]=idx;
            }
            for(int j=1;j<=n;j++){
                if(mp[j][i] == 'X') continue;
                //����������һ�л���һ��λ��mp[j-1][i]��ǽ'X'����ʱ,���������µ�����ͨ��,���idy+1
                if(j == 1 || mp[j-1][i] == 'X')
                    idy++;
                col[j][i]=idy;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j] == '.')//�յؿɷ��õﱤʱ ����Ӧ������ͨ�������ͨ�齨��idx->idy�������
                    G[row[i][j]].push_back(col[i][j]);
            }
        }
        for(int i=1;i<=idx;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms dfs�������� ö����ÿ���յ�'.'���õﱤ,�����������з��õĿ�����.
//��Ϊ����������õﱤ�������Ŀ(��ǰ���õ�����ƥ�䲻һ�������ƥ��),����Ҫö�����з��õﱤλ�õĿ�����
#include<cstdio>
char map[6][6];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int n,max_cnt;
//�ж�map[x][y]ͬһ�С�ͬһ���Ƿ��Ѿ������˵ﱤ.
bool judge(int x,int y){
    int xx,yy;
    for(int i=0;i<4;i++){
        xx=x,yy=y;
        while(xx>0&&xx<=n&&yy>0&&yy<=n){
            xx+=dir[i][0];
            yy+=dir[i][1];
            if(map[xx][yy]=='Y'){//����'Y'˵���÷����Ѿ������˵ﱤ map[x][y]���õﱤ���໥���
                return false;
            }
            if(map[xx][yy]=='X'){//����ǽ��˵���÷����� �ɱ�֤������� ����
                break;
            }
        }
    }
    return true;
}

//����ö���ڿյ�'.'λ�÷��õﱤ
//���ʱ�临�Ӷ�Ӧ�úͰ˻ʺ����ֲ��,O(N^N),��NP(Nondeterministic Polynomial-��ȷ���Զ���ʽ����)���� 
//�˻ʺ���NPC(Non-deterministic Polynomial Complete)������ʽ���ӳ̶ȵķ�ȷ��������,NP��ȫ��
void dfs(int row,int col,int cnt){
    if(cnt>max_cnt)
        max_cnt=cnt;
    for(int i=row;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==row&&j<col)
                continue;
            if(map[i][j]=='.'&&judge(i,j)){
                //����λ������4�����򻥲����,�ڸÿյ�'.'���õﱤ.
                map[i][j]='Y';
                if(j<n)
                    dfs(i,j+1,cnt+1);
                else
                    dfs(i+1,1,cnt+1);
                //��Ϊ����������õﱤ�������Ŀ,����Ҫö�����з��õﱤλ�õĿ�����,
                //����ʱ�ٻ�ԭmap[i][j]Ϊ�յ�,��������һ�����ܵĿյ�λ�÷��õﱤ
                map[i][j]='.';
            }
        }
    }
}

int main(){
    while(scanf("%d",&n)&&n){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&map[i][j]);
            }
        }
        max_cnt=-1;
        dfs(1,1,0);
        printf("%d\n",max_cnt);
    }
    return 0;
}
*/
