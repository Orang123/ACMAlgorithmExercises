/*
����:ժ������
��һ��r*c�����������������ܷ�ʽ��һ��3*3�ľ��󣬡�*����ʾ��������.����ʾ����
����������������һ���������൱�ڰ����������Ӧ��3*3�����м�İ�������
Ȼ���Ӧ��*'��λ�õĵƶ�������������������ľͻ������������찴��Щ��ť
����ʹ��������ÿ�������ĵƶ�����
0<r,c<=5.
����:https://www.luogu.com.cn/problem/UVA10318
˼·:��Ҫ��3*3�ľ���İ���Ӱ�췽ʽ��¼����,��¼��ʽ�Ǵ��±�Ϊ0��ʼ,��¼
Ϊ'*'�����ĵط�(i,j),��(i-1,j-1)�������(i,j)����Ҫ�仯�ľ��뷽��.
��Ҫö��r*c������,����ÿ��������˵���װ����ǲ���,����r*c�Ƶĵ������
�ı�ʾ,�����ö�����״ѹ(���ֻ��25������),����������־�����еƶ�������,
״̬Ϊ (1<<r*c)-1��ö�������а���ʱ.
��������֦:
��֦1:����ö�ٵİ���λ�ó����ڶ���ʱ,�жϵ�ǰ��-2����,�Ƿ񶼱�����,���������û
������ ��ô����Զ�޷�������,��Ϊ����ֻ��Ӱ��ǰһ��,�޷�Ӱ�쳬��һ�����ϵ�λ��.
��֦2:��ǰ�������µİ�����������Ѿ�����֮ǰ��¼����С��Ŀ,�ͷ���.

ʵ�ʲ���������֦Ҳ��800msac.
*/
//ac 0ms ״ѹ+ö��λ��ѡȡ���+��֦
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int r,c,cnt,s[25],tp[25],res[25],ans;
char mp[3][3];
vector<pair<int,int> > dir;

void dfs(int cur,int sta,int k){
    if(k>ans)//��֦2:��ǰ�������µİ�����������Ѿ�����֮ǰ��¼����С��Ŀ,�ͷ���.
        return;
    if(sta == (1<<cnt)-1){
        if(k<ans){
            ans=k;
            memcpy(res,tp,ans*4);
        }
        return;
    }
    if(cur == cnt)
        return;
    int x=cur/c;
    //��֦1:����ö�ٵİ���λ�ó����ڶ���ʱ,�жϵ�ǰ��-2����,�Ƿ񶼱�����,���������û
    //������ ��ô����Զ�޷�������,��Ϊ����ֻ��Ӱ��ǰһ��,�޷�Ӱ�쳬��һ�����ϵ�λ��.
    if(x>=2){//û�������֦ 780ms
        int tx=x-2;
        for(int i=0;i<c;i++){
            if(!(sta & 1<<(tx*c+i)))
                return;
        }
    }
    tp[k]=cur+1;
    dfs(cur+1,sta^s[cur],k+1);
    dfs(cur+1,sta,k);
}

int main(){
    int x,y,nx,ny,cas=0;
    while(scanf("%d%d",&r,&c) && r+c){
        cas++;
        cnt=r*c;
        ans=INF;
        memset(s,0,sizeof(s));
        dir.clear();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf(" %c",&mp[i][j]);
                if(mp[i][j] == '*')
                    dir.push_back(make_pair(i-1,j-1));
            }
        }
        for(int i=0;i<cnt;i++){
            x=i/c;
            y=i%c;
            for(pair<int,int> &tp : dir){
                nx=x+tp.first;
                ny=y+tp.second;
                if(nx<0 || nx>=r || ny<0 || ny>=c)
                    continue;
                s[i]|=1<<(nx*c+ny);
            }
        }
        dfs(0,0,0);
        printf("Case #%d\n",cas);
        if(ans == INF)
            printf("Impossible.\n");
        else{
            printf("%d",res[0]);
            for(int i=1;i<ans;i++)
                printf(" %d",res[i]);
            printf("\n");
        }
    }
    return 0;
}

/*
//ac 0ms ��״ѹ
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int r,c,cnt,tp[25],res[25],ans,vis[N][N];
char mp[3][3];

int check(){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(!vis[i][j])
                return 0;
        }
    }
    return 1;
}

void update(int x,int y){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(mp[i][j] == '*' && x+i-1>=0 && x+i-1<r && y+j-1>=0 && y+j-1<c)
                vis[x+i-1][y+j-1]^=1;
        }
    }
}

void dfs(int cur,int k){
    if(k>ans)
        return;
    if(check()){
        if(k<ans){
            ans=k;
            memcpy(res,tp,ans*4);
        }
        return;
    }
    if(cur == cnt)
        return;
    int x=cur/c;
    int y=cur%c;
    if(x>=2){
        int tx=x-2;
        for(int i=0;i<c;i++){
            if(!vis[tx][i])
                return;
        }
    }
    tp[k]=cur+1;
    update(x,y);
    dfs(cur+1,k+1);
    update(x,y);
    dfs(cur+1,k);
}

int main(){
    int cas=0;
    while(scanf("%d%d",&r,&c) && r+c){
        cas++;
        cnt=r*c;
        ans=INF;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                scanf(" %c",&mp[i][j]);
        }
        dfs(0,0);
        printf("Case #%d\n",cas);
        if(ans == INF)
            printf("Impossible.\n");
        else{
            printf("%d",res[0]);
            for(int i=1;i<ans;i++)
                printf(" %d",res[i]);
            printf("\n");
        }
    }
    return 0;
}
*/
