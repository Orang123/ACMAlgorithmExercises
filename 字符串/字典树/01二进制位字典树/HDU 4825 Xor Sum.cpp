/*
����:ժ������
����n������m��ѯ�ʣ�ÿ��ѯ�ʸ���һ����x��
����n�������ĸ�����x���ֵ���.
n,m<=100000.ÿ������С<=2^32.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4825
˼·:01�ֵ���.���Խ�ÿ������Ӧ�Ķ�����λ��01���Ӹ�λ
����λ��һ���ֵ���.���������������x,���԰����ֵ�����
��λ���λȥ����,����x�ĵ�iλ,ֵ��son,�жϵ�ǰ�������Ƿ�
����son^1���ӽڵ�,������ڵ�iλ�����ֵ�Ϳ���Ϊ1,������
�Ӹ�λ���λ̰��ȡ��,��ȡ����1�����ܶ�ȡ��,���������,��
��iλֻ��Ϊ0��,�ͼ������յ�ǰson�Ľڵ�������������ж�.

ע��:�����x���2^32�η�,ʵ�ʶ�����λ��33λ,�Ѿ�������int�ķ�Χ,
���Ҫ��long long,����λ�����ʱ������.
*/
//ac 265ms ����ʱ,�����¼ÿһλ��ֵ
#include<cstdio>
#include<cstring>
#define N 3200010
typedef long long ll;

int n,m,tr[N][2],cnt;
ll val;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(){
    int son,rt=0;
    //�����λ��32λ��ʼ���λ�����ֵ���,��Ϊ�Ƚ���
    //̰��ѡȡ�����ϸ�λ���ֵΪ1�����,�����������
    for(int i=32;i>=0;i--){
        son=val>>i & 1;//val ��iλΪson(0��1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

ll findWord(){
    int son,rt=0;
    ll res=0;
    for(int i=32;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){//����ֵ����е�iλ����son^1�Ķ���,���iλ���ֵ�Ϳ���ȡ1
            res|=(son^1)<<i;//��¼�ֵ�����ѡȡ�ĵ�iλ��ֵΪson^1
            rt=tr[rt][son^1];
        }
        else{//�����iλ�����ֵֻ����0
            res|=son<<i;//��¼�ֵ�����ѡȡ�ĵ�iλ��ֵΪson
            rt=tr[rt][son];
        }
    }
    return res;
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        while(n--){
            scanf("%d",&val);
            insertWord();
        }
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%d",&val);
            printf("%lld\n",findWord());
        }
    }
    return 0;
}

/*
//ac 390ms ��01�ֵ�������ʱ��Ӧ��10������ֵ��¼����
#include<cstdio>
#include<cstring>
#define N 3200010
typedef long long ll;

int n,m,tr[N][2],cnt;
ll word[N],val;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=-1;
    return cnt;
}

void insertWord(){
    int son,rt=0;
    for(int i=32;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son] == -1)
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    word[rt]=val;
}

ll findWord(){
    int son,rt=0;
    for(int i=32;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]!=-1)
            rt=tr[rt][son^1];
        else
            rt=tr[rt][son];
    }
    return word[rt];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        while(n--){
            scanf("%d",&val);
            insertWord();
        }
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%d",&val);
            printf("%lld\n",findWord());
        }
    }
    return 0;
}
*/
