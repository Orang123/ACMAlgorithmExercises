#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;
//ac 0ms match�ö�ά����
//�����������ȥ��
/*
����:n���˷ַ�5�ֳߴ����͵��·�,�ֱ���"S M L X T",
�ֱ����С��,�к�,���,�ش��,�ش��ش��.ÿ���˶�Ҫ
�Լ�����ĳߴ����ͷ�Χ,��MX����M��X֮��ĳߴ�M��L��X
���ֳߴ綼�ʺ��Լ�,ÿ�ֳߴ����͵��·���һ������,
���ڰ���Щ�·��ַ�����n����,�ܷ�ÿ���˶��ֵܷ��ʺ��Լ�
�ߴ���·�,����������"T-shirts rock!",
�������"I'd rather not wear a shirt anyway...".
ע��:�����20��,ÿ�������·��������20��.
����:http://poj.org/problem?id=2584
˼·:�������ͼ����ƥ��.
*/
char str[10],siz[6]={'S','M','L','X','T'};
int n,st,ed,vis[6],num[6],cnt[6],match[6][N];
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(cnt[v]<num[v]){
            match[v][++cnt[v]]=u;
            return 1;
        }
        else{
            for(int j=1;j<=cnt[v];j++){
                if(dfs(match[v][j])){
                    match[v][j]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}
//ȷ��ĳ�����봩���·��ߴ緶Χ "SMLXT"�ֱ��Ӧ�ߴ���"12345"
void siz_range(){
    for(int i=0;i<5;i++){
        if(str[0] == siz[i]){
            st=i+1;
            break;
        }
    }
    for(int i=0;i<5;i++){
        if(str[1] == siz[i]){
            ed=i+1;
            break;
        }
    }
}

void init(){
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%s",str) && strcmp(str,"ENDOFINPUT")){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            siz_range();
            for(int j=st;j<=ed;j++)
                G[i].push_back(j);
        }
        for(int i=1;i<=5;i++)
            scanf("%d",&num[i]);
        scanf("%s",str);
        int flag=0;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(!dfs(i)){
                flag=1;
                break;
            }
        }
        if(!flag) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}

/*
//ac 0ms match��vector����������
#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;

char str[10],siz[6]={'S','M','L','X','T'};
int n,st,ed,vis[6],num[6];
vector<int> G[N],match[6];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(num[v]){
            num[v]--;
            match[v].push_back(u);
            return 1;
        }
        else{
            //��Ϊ�ݹ�Ὺ���ܶ�dfs ���������ܷ���ȫ��,����ᵼ��itָ��ָ��λ�ô���.
            vector<int>::iterator it;
            for(it=match[v].begin();it!=match[v].end();it++){
                if(dfs(*it)){
                    match[v].erase(it);//ɾ��ԭ��v����Եĵ�
                    match[v].push_back(u);//����v������Եĵ�
                    return 1;
                }
            }
        }
    }
    return 0;
}

void siz_range(){
    for(int i=0;i<5;i++){
        if(str[0] == siz[i]){
            st=i+1;
            break;
        }
    }
    for(int i=0;i<5;i++){
        if(str[1] == siz[i]){
            ed=i+1;
            break;
        }
    }
}

void init(){
    for(int i=1;i<=5;i++) match[i].clear();
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%s",str) && strcmp(str,"ENDOFINPUT")){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            siz_range();
            for(int j=st;j<=ed;j++)
                G[i].push_back(j);
        }
        for(int i=1;i<=5;i++)
            scanf("%d",&num[i]);
        scanf("%s",str);
        int flag=0;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(!dfs(i)){
                flag=1;
                break;
            }
        }
        if(!flag) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}
*/

/*
//ac 0ms ����ƥ��ת��Ϊ���ƥ�������,�����·��ĳߴ�,�����·����������·����,
//ÿ�������·����б��,��ͬ�ߴ��·��ж��ʱ,����Ҳ�ǲ�һ��,����˺������ʺϵ��·�����
//������Ϊ������������С,��HDU 3605 n<=100000,�������߽�����ƥ��ת��Ϊ���ƥ��϶���TLE
#include<cstdio>
#include<cstring>
#include<vector>
#define N 30
using namespace std;

char str[10],s[N][2],siz[6]={'S','M','L','X','T'};
//�����5*20=100���·�
//num[i]��ʾǰi���ߴ��·��������ۼӺ�
int n,st,ed,vis[101],num[6],match[101];
vector<int> G[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void siz_range(int id){
    for(int i=0;i<5;i++){
        if(s[id][0] == siz[i]){
            st=i+1;
            break;
        }
    }
    for(int i=0;i<5;i++){
        if(s[id][1] == siz[i]){
            ed=i+1;
            break;
        }
    }
}

void init(){
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    while(scanf("%s",str) && strcmp(str,"ENDOFINPUT")){
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]);
        for(int i=1;i<=5;i++){
            scanf("%d",&num[i]);
            num[i]+=num[i-1];//num[i]��ʾǰi���ߴ��·��������ۼӺ�
        }
        for(int i=1;i<=n;i++){
            siz_range(i);
            //num[st-1]��stǰ���·��ߴ��������,+1����st�ߴ��·�����ʼ���
            for(int j=num[st-1]+1;j<=num[ed];j++)
                G[i].push_back(j);//ÿ�����ʺϵĳߴ��·������5*20=100,�߼�������������
        }
        scanf("%s",str);
        int flag=0;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(!dfs(i)){
                flag=1;
                break;
            }
        }
        if(!flag) printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}
*/
