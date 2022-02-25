/*
����:����һ���ַ�������˵�Ӵ��У�ѭ������Ϊk����󳤶�Ϊ���١�
�ַ�������<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3163
˼·:ö�ٸ����Ӵ������,��next����,��ö��ÿ���Ӵ���ǰ׺����,Ȼ��ѭ���ж��Ƿ�
����ѭ����,�������j������(j-nxt[tp]),˵������ѭ����,ѭ������Ϊx=j/(j-nxt[tp]),
�����ans[x]=max(ans[x],j/(j-nxt[tp]));
ans[1]���ִ���Ϊ1 ����ԭʼ��������Ϊһ��ѭ������Զ����󳤶�,�������.
ans[x]=j,ѭ������Ϊx��ѭ���ڶ�Ӧ������Ӵ�����Ϊj.

ע��j-nxt[j]��������ѭ���ڵĳ���,j/(j-nxt[j])������ѭ������.
��j-nxt[tp],nxt[tp]<nxt[j],j-nxt[tp]��õĲ������ѭ����,ѭ���ڽϴ�,ѭ����������.
*/
//ac 60ms
//ans[x]=j,ѭ������Ϊx��ѭ���ڶ�Ӧ������Ӵ�����Ϊj.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int nxt[N],pplen,ans[N];
char p[N];

void getNext(char *p,int plen){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int T,len,tp,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(ans,0,sizeof(ans));
        scanf("%s",p);
        pplen=strlen(p);
        ans[1]=pplen;//ѭ������Ϊ1,ԭʼ������������
        //O(10^6)
        for(int i=0;i<pplen;i++){//ö����� �Ӵ�
            len=strlen(p+i);
            getNext(p+i,len);//��p+i��ʼ��ĩβ���Ӵ�nxt����ֵ
            for(int j=2;j<=len;j++){//ö���Ӵ�����,��ͬ�Ӵ�
                tp=j;
                while(nxt[tp]){//nxt[tp]��Ϊ0,Ϊ0ʱ ֻ��һ��ѭ���� ���ø���
                    if(j%(j-nxt[tp]) == 0){//��������Ϊѭ����
                        int x=j/(j-nxt[tp]);
                        ans[x]=max(ans[x],j);
                    }
                    tp=nxt[tp];
                }
            }
        }
        printf("Case #%d:",cas);
        for(int i=1;i<=pplen;i++)
            printf(" %d",ans[i]);
        printf("\n");
    }
    return 0;
}
