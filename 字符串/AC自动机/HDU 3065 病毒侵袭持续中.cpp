/*
����:��n��ģʽ��,1���ı���,�������ı����г��ֵ�ģʽ��,
�������ֵĴ���.��Ŀ��֤n��ģʽ�����ǲ�ͬ��.
n<=1000,ģʽ������<=50,�ı�������<=2000000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3065
˼·:��ģʽ����ƥ������,AC�Զ���.
*/
//ac 202ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 50010
#define M 2000010
using namespace std;

int n,tr[N][128],fail[N],wordId[N],cnt,num[1100];
char p[1100][55],str[M];

int newNode(){
    cnt++;
    for(int i=0;i<128;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,len=strlen(p[id]);
    for(int i=0;i<len;i++){
        if(!tr[rt][p[id][i]])
            tr[rt][p[id][i]]=newNode();
        rt=tr[rt][p[id][i]];
    }
    wordId[rt]=id;
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<128;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<128;i++){
            son=tr[node][i];
            if(son){
                fail[son]=tr[fail[node]][i];
                Q.push(son);
            }
            else
                tr[node][i]=tr[fail[node]][i];
        }
    }
}

void query(){
    int rt=0,len=strlen(str);
    for(int i=0;i<len;i++){
        rt=tr[rt][str[i]];
        for(int j=rt;j;j=fail[j]){
            if(wordId[j])//����ǰ��׺�Ӵ���ģʽ��
                num[wordId[j]]++;//���Ӧģʽ����Ŀ+1
        }
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){//�����Ƕ�����,��������wa
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",p[i]);
            insertWord(i);
            num[i]=0;
        }
        scanf("%s",str);
        build();
        query();
        for(int i=1;i<=n;i++){
            if(num[i])
                printf("%s: %d\n",p[i],num[i]);
        }
    }
    return 0;
}
