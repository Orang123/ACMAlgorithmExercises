/*
����:��n��ģʽ��,��m���ı���,����ÿ���ı����г�����
��Щģʽ��,�����Ӧģʽ���ı��,������м����ı�����
������ģʽ��.
n<=500,ģʽ������<=200,m<=1000,�ı�������<=10000.
ע��:����ģʽ�����ı����е��ַ�����ASCII��ɼ��ַ�,���
�ֵ�����֧��Ϊ128,��Ŀ��֤ÿ��ģʽ�����ǲ�ͬ��.
����:https://acm.hdu.edu.cn/showproblem.php?pid=2896
˼·:��ģʽ�����ı�����ƥ������,AC�Զ���ģ����.ֻ���ֵ����ķ�֧��Ϊ
128,������26.
*/
//ac 202ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 10010
#define M 100010
using namespace std;

int n,m,tr[M][128],fail[M],wordId[M],cnt,vis[510];
char p[210],s[N];

int newNode(){
    ++cnt;
    for(int i=0;i<128;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int len=strlen(p),rt=0;
    for(int i=0;i<len;i++){
        if(!tr[rt][p[i]])
            tr[rt][p[i]]=newNode();
        rt=tr[rt][p[i]];
    }
    wordId[rt]=id;
}

void build(){
    queue<int> Q;
    int fa,son;
    for(int i=0;i<128;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        fa=Q.front();
        Q.pop();
        for(int i=0;i<128;i++){
            son=tr[fa][i];
            if(son){
                fail[son]=tr[fail[fa]][i];
                Q.push(son);
            }
            else
                tr[fa][i]=tr[fail[fa]][i];
        }
    }
}

int query(){
    int now=0,len=strlen(s),sum=0;
    for(int i=0;i<len;i++){
        now=tr[now][s[i]];
        for(int j=now;j;j=fail[j]){
            if(wordId[j]){//��ǰ��׺�Ӵ���ģʽ��
                if(!vis[wordId[j]]){
                    sum++;//���ֵ�ģʽ��������+1
                    vis[wordId[j]]=1;//������ģʽ�����ֹ�
                }
            }
        }
        if(sum == 3)//ÿ����վ��ຬ��3������
            break;
    }
    return sum;
}

int main(){
    int ans;
    ans=0;
    cnt=-1;
    newNode();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",p);
        insertWord(i);
    }
    build();
    scanf("%d",&m);
    //ʱ�临�Ӷ�O(1000*(10000+100000)),ʵ����Ϊ���������3��,���Ը��ӶȻ�Ƚϵ�
    for(int i=1;i<=m;i++){
        scanf("%s",s);
        memset(vis,0,sizeof(vis));
        if(query()){
            ans++;
            printf("web %d:",i);
            for(int j=1;j<=n;j++){
                if(vis[j])
                    printf(" %d",j);
            }
            printf("\n");
        }
    }
    printf("total: %d\n",ans);
    return 0;
}
