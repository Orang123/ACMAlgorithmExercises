/*
����:ժ������
����һ����,Ҫ���ڴ�ͷ��β������ٵ��ַ�,ʹ�øô�������2��ѭ����,
����������Ҫ�Ӽ����ַ�.
plen<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3746
˼·:k=len-next[len]��ѭ���ڳ���,���next[len]Ϊ0,��˵��,
��Ҫ��ԭ������������һ��,������2��ѭ����.
���len%(k)��Ϊ0,��˵�������ܹ���ѭ����,��Ҫ���
���ַ�����Ϊk-len%k.
���len%kΪ0,��˵��ԭ�ȱ�����ܹ���������ѭ����,�Ҹ�������Ϊ2.
���沩������ϸ�ķ���,��û̫����:
https://blog.csdn.net/u013480600/article/details/22954037
*/
//ac 124ms
#include<cstdio>
#include<cstring>
#define N 100010

int plen,nxt[N];
char p[N];

void getNext(){
    plen=strlen(p);
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int T,k;
    scanf("%d",&T);
    while(T--){
        scanf("%s",p);
        getNext();
        k=plen-nxt[plen];
        if(!nxt[plen])//��Ҫ���������ٸ���һ��
            printf("%d\n",plen);
        else if(plen%k)//������ ԭ����������������ѭ����,��Ҫ����ַ�
            printf("%d\n",k-plen%k);
        else if(plen%k == 0)//���� ������ܹ�������2��ѭ����
            printf("0\n");
    }
    return 0;
}
