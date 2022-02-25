/*
����:ժ������
����һ���ı���s��n��ģʽ��p��0�������ص���1�������ص���
��ÿ��ģ�洮���ı����г��ֵĴ�����
n<=100000,ģʽ������<=6,�ı�������<=100000.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367940
˼·:AC�Զ���.���ڿ����ص���,����ͳ�ƾͺ�,���ڲ����ص���,��Ҫ
��¼�ϴ�ģʽ��ƥ��ʱ�ı�����λ��,����ϴδ���λ�ü��ϵ�ǰƥ��ģʽ���ĳ���
С�ڵ��ڵ�ǰλ��,��˵�����ص�.
��Ŀ�����ģʽ���п������ظ�ģʽ��,���ͳ��ʱ,����ͬһģʽ��,
���ص��Ͳ��ص�ƥ�������ͳ�ƾͺ�.
*/
//ac 533ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 600010
#define M 100010
#define L 100010
using namespace std;

int n,tr[N][26],fail[N],wordId[N],plen[L],cnt,num[L][2],type[L],record[L],pos[N];
char p[100010][7],s[M];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    pos[cnt]=-1;
    return cnt;
}

int insertWord(int id){
    int rt=0,son,len=strlen(p[id]);
    for(int i=0;i<len;i++){
        son=p[id][i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    if(!wordId[rt])//�������ظ�ģʽ��,���ֻ��¼һ��
        wordId[rt]=id;
    return wordId[rt];
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<26;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
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
    int rt=0,len=strlen(s);
    for(int i=0;i<len;i++){
        rt=tr[rt][s[i]-'a'];
        for(int j=rt;j;j=fail[j]){
            if(wordId[j]){
                num[wordId[j]][0]++;//�ص�����
                //�ϴδ���λ�ü��ϵ�ǰƥ��ģʽ���ĳ���С�ڵ��ڵ�ǰλ��,��˵�����ص�
                if(i-pos[j]>=plen[wordId[j]]){
                    pos[j]=i;
                    num[wordId[j]][1]++;//���ص�����
                }
            }
        }
    }
}

int main(){
    for(int cas=1;scanf("%s",s)!=EOF;cas++){
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d %s",&type[i],p[i]);
            //�������ظ�ģʽ��,��˱��Ҫ��record[i]�ټ�¼һ��,��ͬrecord[i]��¼�ı�ſ�������ͬ��
            record[i]=insertWord(i);
            num[i][0]=num[i][1]=0;//num[i][0]��¼�ص�����,num[i][1]��¼���ص�����
            plen[record[i]]=strlen(p[i]);//plen��¼ģʽ������
        }
        build();
        query();
        printf("Case %d\n",cas);
        for(int i=1;i<=n;i++)
            printf("%d\n",num[record[i]][type[i]]);
        printf("\n");
    }
    return 0;
}
