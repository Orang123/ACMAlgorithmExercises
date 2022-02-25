/*
����:n�����һ������ÿһ�������һ���ַ�������һ���ַ���S��
�����ܷ���һ��A,B��ʹ��A->B�����·���Ǹ��ַ���S��ʾ�ġ�
n,|s|<=10^4.
ע��:��ͬ�����ĸ�п�����ͬ.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5469
˼·:����dp.ö��ÿ������ĸ���ַ�����һ����ĸs[1]��ȵĵ�,
��ʼdfs����������֧ƥ���ַ�.��һ����֦.
����Ԥ�������1λ���ڵ��ÿ��������֧�Ķ��Ӹ������������,
������ƥ�䵽��ǰ�ַ�����stλʱ,���ʣ��δƥ����ַ��ȵ�ǰ�ڵ�v��
��ķ�֧����������,��ƥ��϶����ɹ�������������ǰ��֧.��Ҫע��
�����֦Ӧ�õ�������Ԥ������u�ĸ��ڵ㲻����v,����v������֧���
�ǳ��ŵ�ǰ���ص����Ƚڵ�ķ���.
*/
//ac 780ms ����dp
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define N 10100
using namespace std;

int n,cnt,head[N],len,dep[N],fa[N];
char C[N],S[N];
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//��¼��v������������·������
void dfs1(int u,int fath){
    dep[u]=1;
    fa[u]=fath;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fath) continue;
        dfs1(v,u);
        if(dep[v]+1>dep[u]) dep[u]=dep[v]+1;
    }
}
//����S�ַ����ĳ��ֵ���ĸ˳���Ӧ�ĵ�ȥ����
int dfs2(int u,int fath,int st){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //��¼���������������Ǹõ������ַ���S�ַ���˳�������
        if(v == fath || C[v]!=S[st+1]) continue;
        /*
        ��Ϊdfs1�м�¼�Ľ�����������������1�����Ϊ���ڵ��,
        ��ÿ��dfs2���ڵ㲻һ����������1Ϊ���ڵ��,�����ڼ�֦֮ǰ
        Ҫ�ж�v����u���ĸ���,����dep[v]�ʹ���v��֮ǰ�Ѿ�������
        ��������,������δ������.���S��δ�ȶԵ��ַ�����v��㿪ʼ�����������Ȼ���,
        �򲻿����ҵ�·��,��֦.
        */
        if(v!=fa[u] && len-st>dep[v]) continue;
        if(st+1 == len)
            return 1;
        if(dfs2(v,u,st+1)) return 1;//ֻҪ����һ����ȵ����·���ͽ���
    }
    return 0;
}

int main(){
    int T,a,b,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;//ǰ���������±�Ҫ��ʼ��0,���������Խ���쳣,����ֵ��¼����û��-1��־,����dfs�޷���������,Runtime Error(STACK_OVERFLOW)
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        //memset�ǰ�1�ֽ�(8 bit)��ֵ��,ֻ��0��-1��Ч��Ϊ��Ӧ��8bit��0(00000000) -1(11111111) ��չ��32λ����0��-1��32λ����
        scanf("%s",C+1);
        scanf("%s",S+1);
        len=strlen(S+1);
        dfs1(1,0);
        int flag=0;
        /*
        �ַ��������10^4��,����ĸֻ��26��,���Բ�ͬ��������ĸ������ͬ,
        S�ַ�����Ҳ�����ظ�����,����Ҫ����������ַ�ΪS[1]�ĵ㿪ʼ����,
        ֻҪ����һ��·���ͽ���.
        */
        for(int i=1;i<=n;i++){
            if(C[i] == S[1]){
                if(dfs2(i,0,1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) printf("Case #%d: Find\n",cas);
        else printf("Case #%d: Impossible\n",cas);
    }
    return 0;
}
/*u����v����Ҳ�ܼ�֦,��2�ּ�֦
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define N 10100
using namespace std;
int n,cnt,head[N],len,dep[N],fa[N];
char C[N],S[N];
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs1(int u,int fath){
    dep[u]=1;
    fa[u]=fath;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fath) continue;
        dfs1(v,u);
        if(dep[v]+1>dep[u]) dep[u]=dep[v]+1;
    }
}

int dfs2(int u,int fath,int st){
    if(st == len) return 1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fath || C[v]!=S[st+1]) continue;
        if(fa[v] == u && len-st<=dep[v]){
            if(dfs2(v,u,st+1)) return 1;
        }
        //n-dep[v]��δ������v���Ҳ������ȥ��,+1�Ǽ���v���,
        //n-dep[v]+1����v����ܽ���ȥ�Ѿ��������������е�������,
        //ʣ��Ϊ���������������Ľ����,��Ȼ�����֦ʵ�����ò�����ô��.
        else if(fa[v]!=u && len-st<=n-dep[v]+1){
            if(dfs2(v,u,st+1)) return 1;
        }
    }
    return 0;
}

int main(){
    int T,a,b,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            addEdge(b,a);
        }
        //memset�ǰ�1�ֽ�(8 bit)��ֵ��,ֻ��0��-1��Ч��Ϊ��Ӧ��8bit��0(00000000) -1(11111111) ��չ��32λ����0��-1��32λ����
        scanf("%s",C+1);
        scanf("%s",S+1);
        len=strlen(S+1);
        dfs1(1,0);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(C[i] == S[1]){
                if(dfs2(i,0,1)){
                    flag=1;
                    break;
                }
            }
        }
        if(flag) printf("Case #%d: Find\n",cas);
        else printf("Case #%d: Impossible\n",cas);
    }
    return 0;
}
*/
