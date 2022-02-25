/*
����:ժ������
��һ��ƽ�棬����������
0 x y ��(x,y)������һ����
1 x1 y1 x2 y2 ��ѯ���½�Ϊ(x1,y1)��
���Ͻ�Ϊ(x2,y2)�ľ�������������ٸ��㣨�����߽磩
n<=1000.
����:http://lightoj.com/volume_showproblem.php?problem=1266
˼·:��ά��״���鵥�����,�����ѯ.
��ά��״���鵥����� �����ѯ�ο�����:https://blog.csdn.net/qq_41837216/article/details/85041511

*/
//ac 408ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,c[N][N],m[N][N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int y,int d){
    for(int i=x;i<N;i+=lowbit(i)){
        for(int j=y;j<N;j+=lowbit(j)){//����j ÿ�ζ��ǳ�ʼ��Ϊy��,֮ǰ��while һֱwa����jû�г�ʼ��
            c[i][j]+=d;
        }
    }
}

int getsum(int x,int y){
    int sum=0;
    for(int i=x;i;i-=lowbit(i)){
        for(int j=y;j;j-=lowbit(j)){
            sum+=c[i][j];
        }
    }
    return sum;
}

int main(){
    int T,q,p,x1,y1,x2,y2;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(c,0,sizeof(c));
        memset(m,0,sizeof(m));
        printf("Case %d:\n",cas);
        scanf("%d",&q);
        while(q--){
            scanf("%d",&p);
            if(!p){
                scanf("%d%d",&x1,&y1);
                x1++,y1++;
                //���ﲻ����c[x1][y1]�ж�(x1,y1)�Ƿ���ù���,��Ϊc[x1][y1]��ʾ���� (1,1)��(x1,y1)��Χ�ڷ��õĵ����
                if(!m[x1][y1]){
                    update(x1,y1,1);
                    m[x1][y1]=1;
                }
            }
            else{
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                x1++,y1++,x2++,y2++;
                //+getsum(x1-1,y1-1) ����Ϊ-getsum(x1-1,y2)-getsum(x2,y1-1)�Ὣ (x1-1,y1-1)���һ��
                printf("%d\n",getsum(x2,y2)+getsum(x1-1,y1-1)-getsum(x1-1,y2)-getsum(x2,y1-1));
            }
        }
    }
    return 0;
}
