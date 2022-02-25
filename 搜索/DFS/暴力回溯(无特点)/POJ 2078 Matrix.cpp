/*
����:ժ������
һ��n*n�����־���ÿ�β������Զ�����һ�л���һ�н���ѭ���ƶ���
�����������⡣��ÿ�����ÿһ�е����ֵ����Сֵ��
n<=7.
����:http://poj.org/problem?id=2078
˼·:ö��ÿһ���ƶ����Ӧ�ľ����״̬,ÿһ����n���ƶ�����,
��ô��n��,���ݳ˷�ԭ�� ������ܵ�����״̬ ��n^n=7^7=823543.
1s�ڿ��Խ���.
*/
//ac 329ms dfs
#include<cstdio>
#define INF1 -0x3f3f3f3f
#define INF2 0x3f3f3f3f
int map[8][8];
int min_sum,n;
void shift(int row){
    int tmp=map[row][n];
    for(int i=n;i>=2;i--)
        map[row][i]=map[row][i-1];
    map[row][1]=tmp;
}

void dfs(int row){
    if(row == n+1){
        int sum,max_sum=INF1;
        bool flag=true;
        //ͳ�Ƶ�ǰ�ƶ�n�к��Ӧ���������е�ֵ����Сֵ�Ƿ�����
        for(int i=1;i<=n;i++){
            sum=0;
            for(int j=1;j<=n;j++)
                sum+=map[j][i];
            //���ĳһ�е�ֵ������֮ǰ��min_sumС ��û�б�Ҫȥ�����������ˣ���Ϊmax_sumֻ��ȡ��Щ��������
            if(sum>=min_sum){
                flag=false;
                break;
            }
            max_sum=(sum>max_sum?sum:max_sum);
        }
        if(flag)//ֻ�е� ������û�б�min_sum���ڵ��ڵ�ʱ��Ż����
            min_sum=(max_sum<min_sum?max_sum:min_sum);
        return;
    }
    for(int i=1;i<=n;i++){//ö�ٵ�row����λ�Ŀ�����,����n�ֿ���,�����ƶ�n�κ�,��ǰ�оͻ�ص� ��ʼ״̬
        shift(row);
        dfs(row+1);
    }
}
int main(){
    while(scanf("%d",&n)&&n!=-1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&map[i][j]);
            }
        }
        min_sum=INF2;
        dfs(1);
        printf("%d\n",min_sum);
    }
    return 0;
}

/*
//ac 391ms dfs
#include<cstdio>
#define INF1 -0x3f3f3f3f
#define INF2 0x3f3f3f3f
int map[8][8];
int min_sum,n;
void shift(int row){
    int tmp=map[row][n];
    for(int i=n;i>=2;i--)
        map[row][i]=map[row][i-1];
    map[row][1]=tmp;
}

void dfs(int row){
    if(row>n) return;
    int sum,max_sum=INF1;
    bool flag=true;
    for(int i=1;i<=n;i++){
        shift(row);
        for(int i=1;i<=n;i++){
            sum=0;
            for(int j=1;j<=n;j++){
                sum+=map[j][i];
            }
            if(sum>min_sum){
                flag=false;
                break;
            }
            max_sum=(sum>max_sum?sum:max_sum);
        }
        if(flag)
            min_sum=(max_sum<min_sum?max_sum:min_sum);
        else
            flag=true;
        dfs(row+1);
    }
}
int main(){
    while(scanf("%d",&n)&&n!=-1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&map[i][j]);
            }
        }
        min_sum=INF2;
        dfs(1);
        printf("%d\n",min_sum);
    }
    return 0;
}
*/
