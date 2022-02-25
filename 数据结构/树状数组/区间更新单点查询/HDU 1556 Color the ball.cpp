/*
����:n�������ų�һ�ţ����������α��Ϊ1,2,3....N.
ÿ�θ���2������a b(a <= b),lele��Ϊ�������ġ�С�ɸ�"
�Ƶ綯��������a��ʼ������b���θ�ÿ������Ϳһ����ɫ��
����N���Ժ�lele�Ѿ������˵�I�������Ѿ�Ϳ��������ɫ�ˣ�
���ܰ������ÿ������Ϳ��������ɫ��
n<=100000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1556
˼·:��״����������µ����ѯ����.
*/
//ac 483ms
#include<cstdio>
#include<cstring>
#define N 100010

//c[x]��¼����1~x�������屻��ת�Ĵ���
int n,c[N];

int lowbit(int x){
    return x & -x;
}

void update(int x,int d){
    while(x<=n){
        c[x]+=d;
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    int a,b;
    while(scanf("%d",&n) && n){
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);
            update(a,1);
            update(b+1,-1);//b���Ƚڵ����ϵĽڵ�������1,�ټ���1
        }
        //���������µ���[1,4]�����ѯ ����8����ڵ�,�����Ӻ����,����0
        //����7 6 5�����Ľڵ�ڵ㱾����-1,���Ƕ��ӽڵ�C[4]��1,�ۼӺ���Ȼ��0
        for(int i=1;i<=n;i++){
            if(i!=1)
                printf(" ");
            printf("%d",getsum(i));
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 436ms �������
//�ο�����:https://blog.csdn.net/tianwei0822/article/details/81879644
#include<cstdio>
#include<cstring>
#define N 100010

int n,x[N],y[N];

int main(){
    int a,b;
    while(scanf("%d",&n) && n){
        memset(x,0,sizeof(x));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);
            x[a]++;
            x[b+1]--;
        }
        for(int i=1;i<=n;i++)
        	y[i]=y[i-1]+x[i];
        for(int i=1;i<=n;i++){
            if(i!=1)
                printf(" ");
            printf("%d",y[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
