/*
����:m*n�ľ���,,����0����յĵذ�,1����ǽ,2�������ӵ���ʼλ��,
3��������Ҫ����ȥ��λ��,4������˹�����ʼλ��.���˹��Ĺ�������
�������Ƶ�ָ����λ��,ע��,���˹�ֻ�������Ӷ�����������,������
���ӱ��Ƶ�һ������(��ͼ2)��ô���ӾͲ����ٱ��ƶ���,������ӱ��Ƶ�
һ��ǽ��,��ô����ֻ������ǽ�ƶ�,�����������˹�Ҫ�������Ƶ�3λ��,
����Ҫ�ƶ����Ӷ��ٸ�.��������Ƶ�ָ��λ�������-1.
2<=m,n<=7.
ע��:�˿�����Ҫ���������ظ�������ͬ��λ��,����Ϊ�˵��������ӵķ���,
ʹ�������ܳ���Ŀ��λ��3ǰ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1254
˼·:���ֽⷨ.

�ⷨ1:��Ϊ�˿������������Բ�ͬ���򵽴���ͬλ��,���Խ�״̬����Ϊ4ά��
vis[bx][by][px][py],����(bx,by)�����ӵ�λ��,(px,py)���˵�λ��.ö���˳�
�ĸ�������,��������ߵ���ǰ״̬�����ӵ�λ��,��ô����Ҳ�������ߵķ�����һ��,
����+1,������߲�������λ��,��ô���Ӿʹ���ԭλ�ò���,ֻ��¼���ߵ�λ��,��������,��Ϊ�µ�״̬���.

ע��:����ʵ������ӵ��������ߵĲ������ٵ�,���������ߵĲ�����һ�������ٵ�,
ʵ���������ߵ���̲���,Ӧ����������Ϊ����,�������ӵ�Ŀ��λ�õ���������پ���,
Ȼ����Ӧ�þ������ߵ������ƶ�������ƶ�����ķ���������Ƶ����Ӽ���,�����������
�������ӵ������˼���.���Ӧ��ʹ�����ȶ����ȳ��������ƶ��������ٵ�״̬,��ô��һ��
����Ŀ��λ��3��״̬�����ƶ�����һ�������ٵ�.

�ⷨ2:���Խ�״̬����Ϊvis[bx][by][4],����4���������λ�õ�4������.������Ϊ
�ƶ�������,�����ƶ�ʱ�ж����Ƿ����ƶ��������ƶ��ķ�����ĺ�һ��λ��,�����˲���
����������.��Ϊbfs��չ״̬�������������Ϊ����,ʹ����ͨ�����Ƚ��ȳ�,������һ��
����Ŀ��λ��3ʱ��״̬����һ�������ٵ�.�ж����Ƿ����ߵ����ӷ�����ĺ�һ��λ����
dfs/bfs�Կ�,�����ƶ���bfs.ͬ��vis�������ά�ķ������Ϊ�˱���������ߵõ���ǰλ��
����һ��������,4�������һ���ߵ��Ĳ�����̵�.
*/
//ac 0ms bfs vis[bx][by][px][py]4ά������ (����λ��,�˵�λ��)��Ϊһ��Ԫ��
//����Ϊ������չ,���ߵ���ǰ����λ��ʱ,�˲������������ƶ�.
//ʱ�临�Ӷ�O(m*n*m*n)=7^4=2401 �ռ临�Ӷ�O(m*n*m*n)=7^4=2401
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
using namespace std;

int m,n,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N],vis[N][N][N][N];
struct State{
    int bx,by,px,py,t;
    State(int bx=0,int by=0,int px=0,int py=0,int t=0):bx(bx),by(by),px(px),py(py),t(t){}
    bool operator < (const State &a)const{
        //��Ϊ������Ϊ������չ��,�ȳ��ӵ������߸��ӽ��ٵ�,���������ƶ��������ٵ�,
        //�п��ܺ���ӵ�ʵ�����ߵĶ��,�������ƶ���������,��������ȶ���.
        return t>a.t;
    }
};

int check(int x,int y){
    if(x<1 || x>m || y<1 || y>n || mp[x][y] == 1)
        return 1;
    return 0;
}

int bfs(int bx,int by,int px,int py){
    priority_queue<State> Q;
    vis[bx][by][px][py]=1;
    Q.push(State(bx,by,px,py,0));
    State tp;
    int nbx,nby,npx,npy,ok;
    while(!Q.empty()){
        tp=Q.top();
        if(mp[tp.bx][tp.by] == 3)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            nbx=tp.bx;
            nby=tp.by;
            npx=tp.px+dir[i][0];
            npy=tp.py+dir[i][1];
            if(check(npx,npy))
                continue;
            ok=0;
            if(npx == tp.bx && npy == tp.by ){//�ж����Ƿ����ߵ���ǰ���ӵ�λ��,���ߵ��Ļ� ���Ӳų������ߵķ����ƶ�,�����ƶ�������+1
                if(check(nbx+dir[i][0],nby+dir[i][1]))
                    continue;
                nbx+=dir[i][0];
                nby+=dir[i][1];
                ok=1;
            }
            if(!vis[nbx][nby][npx][npy]){
                vis[nbx][nby][npx][npy]=1;
                Q.push(State(nbx,nby,npx,npy,tp.t+ok));
            }
        }
    }
    return -1;
}

int main(){
    int T,bx,by,px,py;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&mp[i][j]);
                if(mp[i][j] == 2)//���ӳ�ʼλ��
                    bx=i,by=j;
                else if(mp[i][j] == 4)//�˳�ʼλ��
                    px=i,py=j;
            }
        }
        printf("%d\n",bfs(bx,by,px,py));
    }
    return 0;
}

/*
//ac 124ms bfs������Ϊ����������,dfs�ж����Ƿ����ߵ������ӷ������λ��(fx,fy)
//״̬�������άvis[bx][by][4],�������ӿ�����4����ͬ�ķ����ߵ�(bx,by)λ��,ÿ������ֻ��һ��,��һ������̵�.
//ʱ�临�Ӷ�O(m*n*4)*O(���Ƿ����ߵ������ƶ��ķ�����(ʱ��粻ȷ��)) �ռ临�Ӷ�O(m*n*m*4)=7^2*4=196
#include<cstdio>
#include<queue>
#include<cstring>
#define N 10
using namespace std;

int m,n,dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},mp[N][N],vis[N][N][4];
struct State{
    int bx,by,px,py,t;
    State(int bx=0,int by=0,int px=0,int py=0,int t=0):bx(bx),by(by),px(px),py(py),t(t){}
};

int check(int x,int y){
    if(x<1 || x>m || y<1 || y>n || mp[x][y] == 1)
        return 1;
    return 0;
}

//dfs�ж����Ƿ����ߵ������ӷ�����ĺ�һ��λ��(ex,ey),�����˲�������������,�����߲��ǺϷ���
//O(n*m)=49 ����ǳ�ʼ�˵�λ�õ�(ex,ey)�������پ���
int dfs(int px,int py,int ex,int ey){
	if(px == ex && py == ey)
		return 1;
	int npx,npy,flag;
	for(int i=0;i<4;i++){
		npx=px+dir[i][0];
		npy=py+dir[i][1];
		if(!check(npx,npy)){
			flag=mp[npx][npy];
			mp[npx][npy]=1;
			if(dfs(npx,npy,ex,ey)){
				mp[npx][npy]=flag;
				return 1;
			}
			mp[npx][npy]=flag;
		}
	}
	return 0;
}

//O(n*m*4)=196
int bfs(int bx,int by,int px,int py){
    queue<State> Q;
    //ע�������ʼʱ��������λ�� �����,��Ϊ���ӻ�δ���κ�һ�ַ��򵽴�(bx,by)��ʼλ��
    //vis[bx][by][]=1;
    Q.push(State(bx,by,px,py,0));
    State tp;
    int nbx,nby,fx,fy;
    while(!Q.empty()){
        tp=Q.front();
        if(mp[tp.bx][tp.by] == 3)
            return tp.t;
        Q.pop();
        for(int i=0;i<4;i++){
            //(nbx,nby)�����ƶ���λ��
            nbx=tp.bx+dir[i][0];
            nby=tp.by+dir[i][1];
            //(fx,fy)��ǰ����״̬(tp.bx,tp.by)�����ƶ��ķ�����λ��
            fx=tp.bx-dir[i][0];
            fy=tp.by-dir[i][1];
            if(check(nbx,nby) || check(fx,fy) || vis[nbx][nby][i])
                continue;
            //�ж����Ƿ��ߵ������ƶ�������,�ǲ��ܾ������ӵ�ǰλ�õ�(tp.bx,tp.by),���������
            mp[tp.bx][tp.by]=1;
            mp[tp.px][tp.py]=1;
            if(dfs(tp.px,tp.py,fx,fy)){
            	vis[nbx][nby][i]=1;
            	Q.push(State(nbx,nby,tp.bx,tp.by,tp.t+1));
			}
			//ȡ��״̬���
			mp[tp.bx][tp.by]=0;
            mp[tp.px][tp.py]=0;
        }
    }
    return -1;
}

int main(){
    int T,bx,by,px,py;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&mp[i][j]);
                if(mp[i][j] == 2)
                    bx=i,by=j;
                else if(mp[i][j] == 4)
                    px=i,py=j;
            }
        }
        printf("%d\n",bfs(bx,by,px,py));
    }
    return 0;
}
*/

/*
��������:
input
3

7 4
0 0 0 0
0 0 1 0
0 2 0 3
1 4 1 0
1 0 1 0
1 0 1 0
1 0 0 0

4 4
0 0 1 1
0 0 1 1
0 2 3 1
1 4 1 1

5 6
0 0 0 0 0 3
1 0 1 4 0 1
0 0 1 0 0 1
1 0 2 0 0 1
0 0 0 0 0 1

output
2
3
6
*/
