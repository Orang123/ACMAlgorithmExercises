/*
����:ժ������
����һ�����󣬳�ʼ��Ϊ0�����ڿ��Խ������ֲ�����һ���ǲ�ѯĳ�����ֵ��0����1��
��һ��������������һ���Ӿ����ڵ�ֵȡ����
����:http://poj.org/problem?id=2155
˼·:��ά��״����,�������ղ�ѯ���ͨ���ۼӺ�ȡģ����.
��ά��״���鵥����� �����ѯ����ѧϰ:https://blog.csdn.net/qq_41837216/article/details/85041511
*/
//ac 563ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,c[N][N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int y,int d){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=n;j+=lowbit(j)){//����j ÿ�ζ��ǳ�ʼ��Ϊy��,֮ǰ��while һֱwa����jû�г�ʼ��
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
    int T,p,x1,y1,x2,y2;
    char q;
    scanf("%d",&T);
    while(T--){
        memset(c,0,sizeof(c));
        scanf("%d%d",&n,&p);
        while(p--){
            scanf(" %c",&q);
            if(q == 'C'){
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                //����Ҫ��4���Ǹ���,update(x1,y1,1);��Ѷ��������ת,
                //���(x2+1,y1) (x1,y2+1) (x2+1,y2+1)Ҫ�Ѷ��෭ת�������ٷ�ת��ȥ
                update(x1,y1,1);//ÿ�θ����ۼ�1 ��ʾ��ǰ��ת������1
                update(x2+1,y1,1);
                update(x1,y2+1,1);
                update(x2+1,y2+1,1);
            }
            else{
                scanf("%d%d",&x1,&y1);
                printf("%d\n",getsum(x1,y1)%2);//c[x][y]����Ǿ���[1..x][1..y]����ת�Ĵ���,����ż�����ص���ʼ0״̬,��������1״̬
            }
        }
        if(T)
            printf("\n");
    }
    return 0;
}
