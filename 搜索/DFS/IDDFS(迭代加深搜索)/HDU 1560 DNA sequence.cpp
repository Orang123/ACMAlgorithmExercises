/*
����:
n��DNA���У����һ������n�����е�����,Ҫ�󳤶����,�����̳���.
n<=8,ÿ��DNA���еĳ�����1~5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1560
˼·:ö��������е�ÿһλ,������"AGCT"�е���һ��,֮����n�����п�ʼƥ�䣬
��¼ÿ������ƥ���λ��,ֱ��n������ƥ����ɺ�,��¼��ǰ��̳���.ʵ��
�����е�������,ֱ�ӵ�dfs���ϼ�֦ ʱ����4368ms,ö����̳��Ƚ��е�������
ʱ����889ms.
*/
//ac 889ms IDA*(iterative deepening A*)  (IDDFS iterative deepening depth-first search)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
using namespace std;

int n,len[N],pos[N];
char str[N][6],a[5]="AGCT";

int check(){
    for(int i=1;i<=n;i++){
        if(len[i]-pos[i])
            return 0;
    }
    return 1;
}

int minLen(){
    int tp=len[1]-pos[1];
    for(int i=2;i<=n;i++)
        tp=max(tp,len[i]-pos[i]);
    return tp;
}

int dfs(int k,int maxDep){
    if(check())
        return 1;
    if(k+minLen()>maxDep)//û�������֦��TLE
        return 0;
    int tp[N];
    memcpy(tp,pos,sizeof(pos));
    int flag;
    for(int i=0;i<4;i++){
        flag=0;
        for(int j=1;j<=n;j++){
            if(pos[j]<len[j] && str[j][pos[j]+1] == a[i]){//��j������ δƥ����,pos[j]+1��λ�ú�a[i]�ַ�ƥ��
                pos[j]++;
                flag=1;
            }
        }
        if(flag){
            if(dfs(k+1,maxDep))
                return 1;
            memcpy(pos,tp,sizeof(tp));
        }
    }
    return 0;
}

int main(){
    int T,dep;
    scanf("%d",&T);
    while(T--){
        memset(pos,0,sizeof(pos));
        dep=1;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
            len[i]=strlen(str[i]+1);
            dep=max(dep,len[i]);
        }
        while(1){
            if(dfs(0,dep)){
                printf("%d\n",dep);
                break;
            }
            dep++;
        }
    }
    return 0;
}

/*
//ac 4368ms dfs���������������,�ǵ���
//��֦:����ǰ����+ʣ�໹δƥ�����󳤶ȱ�֮ǰ��¼������ֵ��ʱ,����.���������֦�ᳬʱ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

int n,len[N],pos[N],ans;
char str[N][6],a[5]="AGCT";

int check(){
    for(int i=1;i<=n;i++){
        if(len[i]-pos[i])
            return 0;
    }
    return 1;
}

int minLen(){
    int tp=len[1]-pos[1];
    for(int i=2;i<=n;i++)
        tp=max(tp,len[i]-pos[i]);
    return tp;
}

void dfs(int k){
    if(check()){
    	if(k<ans)
    		ans=k;
        return;
	}
	//��֦:����ǰ����+ʣ�໹δƥ�����󳤶ȱ�֮ǰ��¼������ֵ��ʱ,����.���������֦�ᳬʱ
    if(k+minLen()>ans)
        return;
    int tp[N];
    memcpy(tp,pos,sizeof(pos));
    int flag;
    for(int i=0;i<4;i++){
        flag=0;
        for(int j=1;j<=n;j++){
            if(pos[j]<len[j] && str[j][pos[j]+1] == a[i]){
                pos[j]++;
                flag=1;
            }
        }
        if(flag){
            dfs(k+1);
            memcpy(pos,tp,sizeof(tp));
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	ans=INF;
        memset(pos,0,sizeof(pos));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
            len[i]=strlen(str[i]+1);
        }
        dfs(0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 1825ms bfs
//vis[6][6][6][6][6][6][6][6]��ʾ״̬
//bfs���޷�������С���ȼ�֦��,��Ϊÿһ��������������ƥ������,��ǰ���Ⱦ�����̵�
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10
#define INF 0x3f3f3f3f
using namespace std;

//vis��ʾ���8��DNA�����Ѿ�ƥ��ĸ������������Ƿ���ֹ�,�������� ����MLE
int n,len[N],vis[6][6][6][6][6][6][6][6];
char str[N][6],a[5]="AGCT";

struct State{
	int k,pos[N];
};

int check(int *pos){
    for(int i=1;i<=n;i++){
        if(len[i]-pos[i])
            return 0;
    }
    return 1;
}

int judgeState(int *pos){
	if(vis[pos[1]][pos[2]][pos[3]][pos[4]][pos[5]][pos[6]][pos[7]][pos[8]])
		return 1;
	else{
		vis[pos[1]][pos[2]][pos[3]][pos[4]][pos[5]][pos[6]][pos[7]][pos[8]]=1;
		return 0;
	}
}

int bfs(){
	queue<State> Q;
	int flag;
	State tp,next;
	tp.k=0;
	memset(tp.pos,0,sizeof(tp.pos));
	vis[0][0][0][0][0][0][0][0]=1;
	Q.push(tp);
	while(!Q.empty()){
		tp=Q.front();
		if(check(tp.pos))
			break;
		Q.pop();
		for(int i=0;i<4;i++){
			flag=0;
			next=tp;
        	for(int j=1;j<=n;j++){
            	if(next.pos[j]<len[j] && str[j][next.pos[j]+1] == a[i]){
                	next.pos[j]++;
                	flag=1;
            	}
        	}
        	if(flag){
        		if(!judgeState(next.pos)){
        			next.k++;
        			Q.push(next);
				}
			}
    	}
	}
	return tp.k;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
            len[i]=strlen(str[i]+1);
        }
        printf("%d\n",bfs());
    }
    return 0;
}
*/

/*
//ac 1497ms bfs
//vis �ǰ���6��������ʾ8��DNA�����Ѿ�ƥ���״̬
//bfs���޷�������С���ȼ�֦��,��Ϊÿһ��������������ƥ������,��ǰ���Ⱦ�����̵�
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10
#define M 1679616//6^8
#define INF 0x3f3f3f3f
using namespace std;

//vis �ǰ���6��������ʾ8��DNA�����Ѿ�ƥ���״̬
int n,len[N],vis[M];
char str[N][6],a[5]="AGCT";

struct State{
	int k,pos[N];
};

int check(int *pos){
    for(int i=1;i<=n;i++){
        if(len[i]-pos[i])
            return 0;
    }
    return 1;
}

int judgeState(int *pos){
	int val=0;
	for(int i=1;i<=n;i++)
		val=val*6+pos[i];
	if(vis[val])
		return 1;
	else{
		vis[val]=1;
		return 0;
	}
}

int bfs(){
	queue<State> Q;
	int flag;
	State tp,next;
	tp.k=0;
	memset(tp.pos,0,sizeof(tp.pos));
	vis[0]=1;
	Q.push(tp);
	while(!Q.empty()){
		tp=Q.front();
		if(check(tp.pos))
			break;
		Q.pop();
		for(int i=0;i<4;i++){
			flag=0;
			next=tp;
        	for(int j=1;j<=n;j++){
            	if(next.pos[j]<len[j] && str[j][next.pos[j]+1] == a[i]){
                	next.pos[j]++;
                	flag=1;
            	}
        	}
        	if(flag){
        		if(!judgeState(next.pos)){
        			next.k++;
        			Q.push(next);
				}
			}
    	}
	}
	return tp.k;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
            len[i]=strlen(str[i]+1);
        }
        printf("%d\n",bfs());
    }
    return 0;
}
*/
