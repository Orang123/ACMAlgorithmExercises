#include<cstdio>
#include<cstring>
#include<vector>
#define N 30//Adam�� Eveһ�������ֻ��26��ֽ��
using namespace std;
//ac 0ms �˿�����ֵ�ۼӱȽϴ�С
/*
����:Adam��Eve����,�����˶�����n����,����13������,
2��3��4��5��6��7��8��9��T��J��Q��K��A,��С���ε���,����A���,
��4�ֻ�ɫ ���ҡ����ҡ���ʯ��÷���ֱ���H��S��D��C����ʾ,
��������ͬ���������ɻ�ɫ��������С,��H>S>D>C,����Adam��EveҪ
ͬʱ��n����,Ӯ��һ����һ��,������Eve�����ܵü���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1528
˼·:���˴���ӵ�е��Ƹպÿ��Է�Ϊ��������,��ÿ�γ���һ����,�Ѿ�������
�ͱ�Ȼ�������֮ǰһ�������ֻ�ɫ,Ҳ����ÿ�γ���������֮��û�й�������,
����ÿ�γ����Ÿպù�����һ��ƥ��,����ֻ��Ҫ����Eveֽ��i����Adamֽ��j��
��������������i->j,Ȼ�����Eve�����е��Ƶ�Adamֽ�Ƽ������Ƶ����ƥ�伴��.
*/
int n,vis[N],match[N],val1[N],val2[N],ans;
char Adam[N][5],Eve[N][5];
vector<int> G[N];

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
//C<D<S<H ��ɫ��С��ϵ
int cal(char x){
    /*
    ��Ϊ��������Ϊ��Ҫ�����д�С������,��ֻ�е�������ͬʱ,�Ż��û�ɫȥ�жϴ�С,
    ������ֵ���ֵҪԶԶ���ڻ�ɫ����ֵ����������ֵ���ֵ�ͻ�ɫ��������,
    ��ô5H����ֵ�;��п��ܴ���6C,����������ֵ���ֵ�ǳ�10,����ɫ��ֵ������10.
    */
    if(x>='2' && x<='9') return (x-'0')*10;
    else if(x == 'T') return 100;
    else if(x == 'J') return 110;
    else if(x == 'Q') return 120;
    else if(x == 'K') return 130;
    else if(x == 'A') return 140;

    if(x == 'C') return 1;
    else if(x == 'D') return 2;
    else if(x == 'S') return 3;
    else if(x == 'H') return 4;
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            scanf(" %c%c",&Adam[i][0],&Adam[i][1]);
            val1[i]=cal(Adam[i][0]);
            val1[i]+=cal(Adam[i][1]);
        }
        for(int i=1;i<=n;i++){
            scanf(" %c%c",&Eve[i][0],&Eve[i][1]);
            val2[i]=cal(Eve[i][0]);
            val2[i]+=cal(Eve[i][1]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(val2[i]>val1[j])//Eve�Ƶĵȼ�����Adam �ͽ������i->j
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms ���ջ�ɫ����Ƚ�ֽ�ƴ�С
#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;

int n,vis[N],match[N],ans;
char Adam[N][5],Eve[N][5];
vector<int> G[N];

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

int cal(char x){
    if(x>='2' && x<='9') return x-'0';
    else if(x == 'T') return 10;
    else if(x == 'J') return 11;
    else if(x == 'Q') return 12;
    else if(x == 'K') return 13;
    else if(x == 'A') return 14;
    return 0;
}

void init(){
    ans=0;
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf(" %c%c",&Adam[i][0],&Adam[i][1]);
        for(int i=1;i<=n;i++)
            scanf(" %c%c",&Eve[i][0],&Eve[i][1]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(cal(Eve[i][0])>cal(Adam[j][0]))//����ֽ�Ƶ����ִ�Сһ��Ҫӳ�����ֵ,����ֱ�Ӱ���ASCII��Ƚ� T��������
                    G[i].push_back(j);
                else if(Eve[i][0] == Adam[j][0]){//�������,�Ƚϻ�ɫ C<D<S<H ��ɫ��С��ϵ
                    if(Eve[i][1] == 'H' &&  Adam[j][1] != 'H')//H��ɫ���
                        G[i].push_back(j);
                    else if(Eve[i][1] == 'S' && (Adam[j][1] == 'D' || Adam[j][1] == 'C'))//Eve��Sʱ,Adam��D��C,Eve��Ӯ
                        G[i].push_back(j);
                    else if(Eve[i][1] == 'D' && Adam[j][1] == 'C')//Eve��Dʱ,Adam��C,Eve��Ӯ
                        G[i].push_back(j);
                }
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
