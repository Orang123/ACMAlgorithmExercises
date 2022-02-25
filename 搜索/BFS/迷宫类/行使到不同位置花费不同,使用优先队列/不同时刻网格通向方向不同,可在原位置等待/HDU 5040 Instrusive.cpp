/*
//����ժ������
����:��һ��n*n����ͼ��MattҪ��M�ƶ���Tȡ͵������N��W��S��E��ʾ��Щλ�ü�صĳ�ʼ����Ϊ
���������ϡ����ļ������'M'��ʼλ��,'#'��ʾ�ϰ���,'T'��ʾĿ�ĵأ�'.'��ʾ�յ�,����ÿһ��
˳ʱ����ת90��,ÿ������ͷ�Ĺ۲췶ΧΪ�����ڵĵ㣬�͵�ǰ��������Ǹ��㣬����Mattÿ�ƶ�һ��
��Ҫ��һ�룬���������ǰ�����ڵ�λ�û�����Ҫȥ��λ�ñ���������ӣ���ô�����Ҫ�ƶ����ͱ���
�����������ƶ���ʱ����Ҫ����3�롣����Ҳ����ѡ���ƶ�������������1�룬��˵Matt���ٻ��Ѷ���ʱ���ƶ���T��
1<=n<=500.
ע��:�����жϵ�ǰλ�ú���һλ���Ƿ񱻼�ؼ�ص�ʱ�䶼�ǰ��յ�ǰʱ��tp.tȥ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5040
˼·:bfs,��Ϊ������������ֻ��1s�ƶ�һ��,����ؼ�ص���Ҫ3s�ƶ�,
��˲������ȶ���.ֻ��ÿ��һ����Ҫ�жϵ�ǰλ�ú����ߵ���һλ���Ƿ�
�ᱻ��Χ��������4�������Ƿ񱻼�ؼ�ص�.λ�ñ������ά����vis[x][y][t%4]���,
��Ϊ����ӵ�״̬ ��Ȼʱ��ϴ�,���ǵ�ǰ���������ʱС,���ܲ��ᱻ��ط���.
2��������¼ÿ��������ܼ�ص���λ��.
��ʽ1:posһά�����¼.pos['N']=k��ʾ�������ʼ��ط���Ϊ������������ܼ�ص���Matt����
λ����������ʱ���ߵ��ü����,�������������dir�����е��±�Ϊk.
pos��¼��������ط���ķ�������dir����������±�,����Ҫ��֤pos['N'],pos['E'],pos['S'],pos['W]
��¼�ķ����±�һ��Ҫ��������,��Ϊ����ʱ��t����Ҫȡģ,��pos['N']��¼���±겻һ��Ҫ����0,������1��2��3
ֻ��Ҫpos��¼��ֵһ��Ҫ����.

��ʽ2:pos��ά�����¼pos[x][y][t%4]=0/1��ʾ(x,y)λ����ʱ��t���Ƿ��ܱ��������ص�.
Ԥ�����'N'��'E'��'S'��'W'������ڸ�����������ʱ��ȡģt%4���Ƿ��ܱ����pos[x+/-1][y+/-1][0..3].

*/
//ac 390ms bfs
//�������������posһά�����¼
//��ʽ1:posһά�����¼.pos['N']=k��ʾ�������ʼ��ط���Ϊ������������ܼ�ص���Matt����
//λ����������ʱ���ߵ��ü����,�������������dir�����е��±�Ϊk.
//pos��¼��������ط���ķ�������dir����������±�,����Ҫ��֤pos['N'],pos['E'],pos['S'],pos['W]
//��¼�ķ����±�һ��Ҫ��������,��Ϊ����ʱ��t����Ҫȡģ,��pos['N']��¼���±겻һ��Ҫ����0,������1��2��3
//ֻ��Ҫpos��¼��ֵһ��Ҫ����.
#include<cstdio>
#include<queue>
#include<cstring>
#define N 510
using namespace std;

//pos�����±�Ϊ'N'��д��ĸ,���ȡ��'Z'����ASCII��
//dir�洢�ķ����Ǹ���pos��¼�ķ���Ԥ��� Ϊ�ϡ�����������
int n,dir[4][2]={{1,0},{0,-1},{-1,0},{0,1}},pos[90],vis[N][N][4];
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>n || mp[x][y] == '#')
        return 1;
    return 0;
}

//�ж��Ƿ�Ϊ�����
int isCamera(int x,int y){
    if(mp[x][y] == 'N' || mp[x][y] == 'E' || mp[x][y] == 'S' || mp[x][y] == 'W')
        return 1;
    return 0;
}

//�ж�(x,y)λ����ʱ��tʱ�Ƿ�ᱻ�������ص�
int judge(int x,int y,int t){
    if(isCamera(x,y))
        return 1;
    int nx,ny;
    char ch;
    for(int i=0;i<4;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(check(nx,ny) || !isCamera(nx,ny))
            continue;
        //�������ط���Ϊch
        ch=mp[nx][ny];
        //��ط�����ʱ��t��ʵ�� �ܼ�ص���λ�÷�������dir���±�Ϊ(pos[ch]+t)%4
        //���(pos[ch]+t)%4 == i˵��,��ǰ(x,y)��(nx.ny)�������ط�����
        if((pos[ch]+t)%4 == i)
            return 1;
    }
    return 0;
}

int bfs(int sx,int sy){
    priority_queue<State> Q;
    vis[sx][sy][0]=1;//��ʼ״̬λ�� 0ʱ�̱����
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny,nt,flag;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y] == 'T')
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            flag=0;
            //�жϵ�ǰλ��(tp.x,tp.y)�ͼ���Ҫ�ߵ�λ��(nx,ny)�ڵ�ǰʱ��tp.t�Ƿ��ܱ��������ص�
            //ע�����ﵱǰλ�ú���һλ�ö��ǵ�ǰʱ��tp.t
            //���ܼ�ص� ����������3s��(tp.x,tp.y)�ƶ���(nx,ny)
            if(judge(tp.x,tp.y,tp.t) || judge(nx,ny,tp.t)){
                nt=tp.t+3;
                flag=1;
            }
            else//���򲻻ᱻ��ص� ֻ��1s���ܴ�(tp.x,tp.y)�ƶ���(nx,ny)
                nt=tp.t+1;
            //�ж�ʱ��nt�µ�(nx,ny)�Ƿ��Ѿ��߹�,û�߹����
            //ʵ�����ȶ��к���ӵ�ʱ��ϴ�,����ʱ��㲻ͬ,�п��ܴ�(tp.x,tp.y)��(nx,ny)�Ͳ��ᱻ�������ص�,ԭ����3s,����ӵ�״ֻ̬����1s
            //������ʱ��������
            if(!vis[nx][ny][nt%4]){
                vis[nx][ny][nt%4]=1;
                Q.push(State(nx,ny,nt));
            }
            //��ǰλ��(tp.x,tp.y)��Ҫ�ߵ�λ��(nx,ny)�ᱻ��ؼ�ص�,ѡ���ڵ�ǰλ�ö���������1s.
            if(flag && !vis[tp.x][tp.y][(tp.t+1)%4]){
                vis[tp.x][tp.y][(tp.t+1)%4]=1;
                Q.push(State(tp.x,tp.y,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int cas=0,T,sx,sy;
    pos['N']=0;//N��Ӧ�ķ�����S ��Ӧdir�±�0
    pos['E']=1;//N��Ӧ�ķ�����W ��Ӧdir�±�1
    pos['S']=2;//N��Ӧ�ķ�����N ��Ӧdir�±�2
    pos['W']=3;//N��Ӧ�ķ�����E ��Ӧdir�±�3
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'M')
                    sx=i,sy=j;
            }
        }
        printf("Case #%d: %d\n",cas,bfs(sx,sy));
    }
    return 0;
}

/*
//ac 452ms bfs
//�������������pos��ά�����¼���������ܱ���ص���ʱ��
//��ʽ2:pos��ά�����¼pos[x][y][t%4]=0/1��ʾ(x,y)λ����ʱ��t���Ƿ��ܱ���Χ�������ص�.
//Ԥ�����'N'��'E'��'S'��'W'������ڸ�����������ʱ��ȡģt%4���Ƿ��ܱ����pos[x+/-1][y+/-1][0..3].
#include<cstdio>
#include<queue>
#include<cstring>
#define N 510
using namespace std;

//pos[x][y][t%4]=0/1��ʾ(x,y)λ����ʱ��t���Ƿ��ܱ���Χ�������ص�.
int n,dir[4][2]={{1,0},{0,-1},{-1,0},{0,1}},pos[N][N][4],vis[N][N][4];
char mp[N][N];
struct State{
    int x,y,t;
    State(int x=0,int y=0,int t=0):x(x),y(y),t(t){}
    bool operator <(const State &a)const{
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>n || y<1 || y>n || mp[x][y] == '#')
        return 1;
    return 0;
}

int bfs(int sx,int sy){
    priority_queue<State> Q;
    vis[sx][sy][0]=1;
    Q.push(State(sx,sy,0));
    State tp;
    int nx,ny,nt,flag;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.x][tp.y] == 'T')
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nx=tp.x+dir[i][0];
            ny=tp.y+dir[i][1];
            if(check(nx,ny))
                continue;
            flag=0;
            //�жϵ�ǰλ�úͼ���Ҫ��λ���ڵ�ǰʱ��tp.t�Ƿ񱻼�ؼ�ص�
            if(pos[tp.x][tp.y][tp.t%4] || pos[nx][ny][tp.t%4]){
                nt=tp.t+3;
                flag=1;
            }
            else
                nt=tp.t+1;
            if(!vis[nx][ny][nt%4]){
                vis[nx][ny][nt%4]=1;
                Q.push(State(nx,ny,nt));
            }
            if(flag && !vis[tp.x][tp.y][(tp.t+1)%4]){
                vis[tp.x][tp.y][(tp.t+1)%4]=1;
                Q.push(State(tp.x,tp.y,tp.t+1));
            }
        }
    }
    return -1;
}

int main(){
    int cas=0,T,sx,sy;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(vis,0,sizeof(vis));
        memset(pos,0,sizeof(pos));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == 'M')
                    sx=i,sy=j;
                //��ط����ʼ��ط���Ϊ��
                else if(mp[i][j] == 'N'){
                    //(i,j)��ǰλ���κ�ʱ�̶��ܱ���ص�
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i-1,j))//��ǰλ��(i,j)�����Ϸ�(i-1,j)��ʱ��0�ᱻ��ص�
                        pos[i-1][j][0]=1;
                    if(!check(i,j+1))//��ǰλ��(i,j)���ҷ�(i,j+1)��ʱ��1�ᱻ��ص�
                        pos[i][j+1][1]=1;
                    if(!check(i+1,j))//��ǰλ��(i,j)�����·�(i+1,j)��ʱ��2�ᱻ��ص�
                        pos[i+1][j][2]=1;
                    if(!check(i,j-1))//��ǰλ��(i,j)����(i,j-1)��ʱ��3�ᱻ��ص�
                        pos[i][j-1][3]=1;
                }
                else if(mp[i][j] == 'E'){
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i,j+1))
                        pos[i][j+1][0]=1;
                    if(!check(i+1,j))
                        pos[i+1][j][1]=1;
                    if(!check(i,j-1))
                        pos[i][j-1][2]=1;
                    if(!check(i-1,j))
                        pos[i-1][j][3]=1;
                }
                else if(mp[i][j] == 'S'){
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i+1,j))
                        pos[i+1][j][0]=1;
                    if(!check(i,j-1))
                        pos[i][j-1][1]=1;
                    if(!check(i-1,j))
                        pos[i-1][j][2]=1;
                    if(!check(i,j+1))
                        pos[i][j+1][3]=1;
                }
                else if(mp[i][j] == 'W'){
                    pos[i][j][0]=pos[i][j][1]=pos[i][j][2]=pos[i][j][3]=1;
                    if(!check(i,j-1))
                        pos[i][j-1][0]=1;
                    if(!check(i-1,j))
                        pos[i-1][j][1]=1;
                    if(!check(i,j+1))
                        pos[i][j+1][2]=1;
                    if(!check(i+1,j))
                        pos[i+1][j][3]=1;
                }
            }
        }
        printf("Case #%d: %d\n",cas,bfs(sx,sy));
    }
    return 0;
}
*/
