#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;
//ac 374ms ����ƥ�� ��slack�Ż� O(V^4)
//2008 Asia Hangzhou Regional Contest Online
//https://blog.csdn.net/qq_21057881/article/details/50682525 ����������ڱߺ͸�Ȩ��Ҳ����ͼ��������ʼ��mpֻ����-INF,��-1�ʹ�֪Ϊ��
/*
KM�㷨������֮�����Ȩ��С��ֵd������dfs������ƥ���м���,�����Ӹ��Ӷ�,��ʱ�϶� 876ms
������KM() while(1)ÿ��dfs����ѭ��������forѭ������Ч��,���ӶȾͻή��,��ʱ���� 374ms.
����ֱ������,��Ӧ���ǲ�ֵd����dfs��������ֱ�Ӽ���һ�θ�����,���������Ϊ�ݹ�
��dfs�� ��Ϊ��Ҫ�жϲ�ֵd��Ϊ0ʱ,����d=min(d,tp),���ݹ�if else d=min(d,tp)����
���ָ� ��ø�����һЩ,���Ի�����ʱ�Ͷ���Щ,��ʵ��Ҳ������500ms,���ֵ�Ҳ�����Ǻܲ�.
//���񵥵�ֻ������� ��С��ֵd������dfs������ƥ���м����ʱ�϶�,������ĿЧ��ʱ���slack�Ż����
������ʱ���ý���ֵd����KM while(1)������������
*/

/*
����:n��ѧ��m������,ÿ��ѧ����һЩ(����ȫ��)�������
����,����Ϊ��˵������������,����Ϊ0����������������,
����Ϊ�������������ϲ�,ѧ����ϲ��ס�������ϲ�ķ�����,
����Ҫ��ÿ��ѧ�����䵽һ���������ַ���,һ������ֻ��סһ��ѧ��,
���ܽ�ѧ�����䵽��δ���ֵķ���,��Ϊѧ����Ϊ����ԭ����ס�����������.
Ҫ�����ѧ���Ծ�ס���������֮�����,�������������֮��.
�������������ѧ�����ܷ��䵽�Լ����ֵķ���,���-1.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2426
˼·:����ѧ�������ͷ����������ܲ��Ե�,��n<m n=m n>m���п���,
����ѧ������Ϊ����δ���ֵķ��䶼��Ӧ����,ֻ����Ȩֵw>=0�ı�,
��KM�㷨��Ӧ�ж���Ч��.���ڴ���ѧ�����ܷ��䵽��������,
Ӧ����ÿ���������㷨������,�����������ͼ�ıߵĲ�ֵ
d=lx+ly-mp[x][y]���ж�,ÿ�γ�ʼ��d=INF,�������������d��Ȼ����INF,
˵������ƥ��Ĺ���,����ĳ����uû����Ч�߿�ƥ��(u�����Ǳ�����ޱ�����,
Ҳ���������ӱ߶�����ĵ�ƥ��,û��ʣ����Ч��),���Ȼu���ѧ�����ܷ��䵽����.
���-1.
*/
int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(mp[u][v] == -1 || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
//O(V^4) ��Ϊ��¼��С��ֵd��while(1)������������ѭ��
int KM(){
    for(int i=0;i<n;i++){//��ʼ��x����
        for(int j=0;j<m;j++){
            if(mp[i][j] == -1) continue;//�����ڵı߲���Ҫ�Ƚ�����Ȩ
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)//��ʼ��y����
        ly[i]=0;
    for(int i=0;i<n;i++){//O(V)
        while(1){//O(V)
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;//O(E)
            for(int j=0;j<n;j++){//��Ҫ����dfs���������¼��С��ֵ O(V^2)
                if(!visx[j]) continue;
                for(int k=0;k<m;k++){
                    //�������ڵı߶�Ӧ��visy[k]ҲΪ0,����Ҫ�ų�,�������û����Ч��ƥ��ʱ,
                    //��Ӧ��Y����δƥ��ĵ�visy[k]Ҳ��0,��ͻᵼ��d�����²��ܽ�����ѭ��
                    if(mp[j][k] == -1) continue;
                    if(!visy[k])
                        d=min(d,lx[j]+ly[k]-mp[j][k]);
                }
            }
            if(d == INF) return -1;//X���ϴ��ڵ�û����Ч�߿���� �˳�����-1 ���n>m�����
            //����ʧ��,�����ʹ��ĵ�(��������ʧ�ܵĵ�)�γɵ�����Ϊ������.
            //���������������������ͼ�з��ʵ��Ľ������е㶥��ֵ,lx����,ly����.
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;//ֻ�ۼ�Y����ƥ����Ӧ��Ȩ
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));//��Ϊ��ı���Ǵ�0��ʼ��,���link��ʼ��-1
    memset(mp,-1,sizeof(mp));//�������ȨֵΪ0��Ȩֵ����0�ı�,��˳�ʼ��-1
    memset(lx,-1,sizeof(lx));//��Ϊʵ�ʽ����Ķ���ͼ�б�Ȩ��>=0,���lx��ʼ��Ϊ-1
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)//ֻ������Ȩ���ڵ���0�ı�
                mp[u][v]=w;
        }
        printf("Case %d: %d\n",cas,KM());
    }
    return 0;
}

/*
//ac 873m ����ƥ�� ��ֵd(ȫ�ֱ���)����dfs�����,ÿ��dfs�����ʼ��d=INF ��ʱ�϶� ��ʡȥ��slack����,
//����������Ժ�ʱ�϶� HDU 2255������С��ֵd����dfs�����,��ʱ�ȷ���KM() while��Ҫ��,�����������й�
//����KM���ӶȰ�����ֻ��O(V^2*E) ���������slack�����¼Y����ÿ������С��ֵ,������������������.
//һ��������˵����ԭ��:https://www.cnblogs.com/fzl194/p/8848061.html
//��ȫ�ֱ�����ͬ����,ȫ�ֱ�����ÿ��whileѭ���ж���Ҫ��ֵ��INF,
//ÿ������������е����Сֵ,��slack������ÿ��while����ͳ�ʼ����,
//ÿ��whileѭ��slack�����ÿ��ֵ�����õ�,һ������·�������slackֵ���׼ȷ,
//ѭ��������ȫ�ֱ�������,why"ѭ��������ȫ�ֱ�������"???
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(mp[u][v] == -1 || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            d=min(d,tp);
    }
    return 0;
}
//O(V^2*E)
int KM(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mp[i][j] == -1) continue;
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)
        ly[i]=0;
    for(int i=0;i<n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            if(d == INF) return -1;
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));
    memset(mp,-1,sizeof(mp));
    memset(lx,-1,sizeof(lx));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                mp[u][v]=w;
        }
        printf("Case %d: %d\n",cas,KM());
    }
    return 0;
}
*/

/*
//ac 249ms slack�����ɳ��Ż� O(V^2*E)
//����ɳ��Ż���Ҫ����ÿ�θ��¶���,ȷ����С��ֵʱ,��Ϊ��slack[i]�����¼��Y������ÿ����i��Ϊ��������бߵĶ˵�i��Ҫ����С��ֵ
//���������ڱȽ�����Y��������Ϊ��������б߶˵�Ĳ�ֵʱ,����һ��forѭ���ͱȽϳ�Y��������С�Ĳ�ֵ.
//������slack����ͻᵼ��,������Ҫ����forѭ���ȿ���x������vis[x]=1�ĵ�,�ٿ���x���ߵ�Y����visy[y]=0�ĵ�.
//��������Ͳ���slack����ֱ����dfs���¼�����С��ֵd �о�ûɶ����,Ϊɶ�������slack�������.

//ժ�Բ���:https://blog.csdn.net/c20182030/article/details/73330556?locationNum=3&fps=1
//ò�Ƽ���slack����� ��Ȩֵ��С����Ӱ��������
//�������������˵,ʱ�临�Ӷ�ԼΪO(V^2*E),����
//������ǿ��Ǽ�������,��ÿ���ߵı�Ȩmp[i][j]=i*j,���Կ���,��������   "��ܺ�ʱ��,�ҵ����"
//ֻ����漴����O(n^3),���ڼ������ݣ�w[i][j]�ܴ�slack�Ż����ò�����

//ժ�Բ���:https://www.cnblogs.com/Iking123/p/11300885.html
//����Ż��ƺ��Ǻ�����,�������ܰ�KM�Ż���O(n^3).����ʵ��ԭ�㷨���,
//����ҪΪ��n����ƥ��,ÿ��ƥ�仹�����Ҫ����n��,ÿ�����㻹��O(n+m).
//�������ȫͼ,���ҳ�������΢����һ������,��Ȼ��O(n^4).
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(mp[u][v] == -1 || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}
//O(V^2*E)
int KM(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mp[i][j] == -1) continue;
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)
        ly[i]=0;
    for(int i=0;i<n;i++){
        //����while(1)֮���ԭ����ÿ����������·ʱlx+ly!=w(x,y)��Ӧ��Y�����еĵ�Ӧ�ö��ǲ�ͬ��,
        //����ֻ���ʼ��һ�η��ڿ���i����Ե�while(1)ѭ����
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=0;j<m;j++){//ֱ�ӿ���Y�����еĵ�,��Ϊslack�����Ѿ���¼��Сֵ���������С��ֵ,һ��forѭ������
                if(!visy[j])//����ʵ�ʲ����ڵ���Ч��slack[j]��INF,����������j����Ϊδ����δ���,����d�Ծɻ���INF
                    d=min(d,slack[j]);
            }
            if(d == INF) return -1;
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
                //else slack[j]-=d;// ������Ϊɶ slack[j]Ҫ��d ��ʵ�ϲ���slack����Ҳû����
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));
    memset(mp,-1,sizeof(mp));
    memset(lx,-1,sizeof(lx));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                mp[u][v]=w;
        }
        printf("Case %d: %d\n",cas,KM());
    }
    return 0;
}
*/

/*
//ac 124ms slack�����Ż�+��ʽǰ���� ��ͼ O(V^2*E)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cnt,head[N];
int cas,n,m,e,link[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;
struct Edge{
    int from,to,next,w;
}edge[N*N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

int dfs(int u){
    visx[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-edge[i].w;
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}
//O(V^2*E)
int KM(){
    int u,v;
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        lx[u]=max(lx[u],edge[i].w);
        ly[v]=0;
    }
    for(int i=0;i<n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=0;j<m;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            if(d == INF) return -1;
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(link[v] == u)
            sum+=edge[i].w;
    }
    return sum;
}

void init(){
    cas++;
    cnt=0;
    memset(link,-1,sizeof(link));
    memset(head,-1,sizeof(head));
    memset(lx,-1,sizeof(lx));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                addEdge(u,v,w);
        }
        printf("Case %d: ",cas);
        if(n>m) printf("-1\n");
        else printf("%d\n",KM());
    }
    return 0;
}
*/

/*
//ac 327ms mp��ʼ��-1,-2��wa,��ʼ��-3���С�ĸ����Ͷ���,��֪ɶԭ��,�е���ѧ.Ҳ������������linux���������й�?
//�������Ĳ�������ʵ�� �Ͳ����ڻ�ѡ�����ڱ߻�����Ϊ�����ıߵ�����,ȫ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

int KM(){
    for(int i=0;i<n;i++){
    	lx[i]=-3;
        for(int j=0;j<m;j++){
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)
        ly[i]=0;
    for(int i=0;i<n;i++){
    	memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=0;j<m;j++)
            if(!visy[j])
            d=min(d,slack[j]);
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;
        //if(mp[link[i]][i] == -1) return -1;//��������ʵ�� �Ͳ����ڻ�ѡ�����ڱ߻�����Ϊ�����ıߵ�����,ȫ������
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));
    memset(mp,-1,sizeof(mp));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        for(int i=0;i<n;i++){
        	for(int j=0;j<m;j++)
        		mp[i][j]=-3;
		}
        int num=e;
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                mp[u][v]=w;
        }
        printf("Case %d: ",cas);
        if(!num)//����Ϊ0ʱ,��Ҫ�������0,����KM��һֱwhile(1)����ѭ��.
        	printf("-1\n");
        else
        	printf("%d\n",KM());
    }
    return 0;
}
*/
