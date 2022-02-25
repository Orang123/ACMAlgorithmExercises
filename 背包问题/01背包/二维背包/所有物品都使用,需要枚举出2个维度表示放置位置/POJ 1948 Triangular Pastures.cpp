#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 850
using namespace std;
//ac 219ms ��ά01����
//��UVA12099 ����
/*
����:������n��Χ����,����Ҫ����ЩΧ����ƴ�ճ�����,������ʣ��
ʹ�����γ����ܹ���һ��������,���ܹ��ɵ�������,���ܹ���������
���-1.
����:http://poj.org/problem?id=1948
˼·:����UVA 12099,ֻҪȷ����2���ߵĳ���,�������߾���ȷ��.
dp[i][j][k]����ǰi��Χ����ƴ�ճ���һ���߳���Ϊj,�ڶ����߳���
Ϊk,�����������߾���(Χ�����ܳ���-j-k),ע���ʱdp[i][j][k]��
���ܴ�����������ܹ��ɺϷ���������,����Ҫ�ٴ��ж�.ʵ�ʹ�������
�Ż����˵�һά��i,ֻ�ж�άdp[j][k].
*/
int n,li[N],dp[M][M],sum;

//��������֮�������ڵ����� ���ܹ���������
int check(int a,int b,int c){
    return a+b>c && b+c>a && a+c>b;
}

int cal(int a,int b,int c){
    double p=sum/2.0;//���׹�ʽ �ܳ���һ�� Ҫ�ø�������ȷֵ ��int��wa
    return sqrt(p*(p-a)*(p-b)*(p-c))*100;
}

int main(){
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        scanf("%d",&li[i]);
        sum+=li[i];
    }
    int len=sum/2;
    dp[0][0]=1;//ǡ��װ������
    for(int i=1;i<=n;i++){
        //ע��j k�����뽵�� ���ܱ�֤dp[j-li[i]][k] dp[j][k-li[i]]��ǰi-1��Χ���ε�״̬
        // j k���½綼��0 �����Ż��������ʼ״̬dp[0][0]
        for(int j=len;j>=0;j--){
            for(int k=len;k>=0;k--){
                //��i��Χ����ƴ�ӵ���1���߻��2���� ֻҪ����һ������ ��dp[i][j][k]�Ϸ�
                if((j>=li[i] && dp[j-li[i]][k]) || (k>=li[i] && dp[j][k-li[i]]))
                    dp[j][k]=1;
            }
        }
    }
    int ans=-1;
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len;j++){
            if(dp[i][j] && check(i,j,sum-i-j))
                ans=max(ans,cal(i,j,sum-i-j));
        }
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 532ms ���仯����+��֦
//������ظ��׶εı��,�ϸ���˵����˵�ɼ��仯����,��Ϊ��ֻ��˵��ǰ�׶�֮ǰ��������,
//��������������ĳ���µķ�����������,����˵��û��dp�׶���,�����⹹�ɴ�������������뷨
//���������ϵļ��仯����,�����ǰ��ص�������ķ�����ֵ ��¼����,�ȵ��ظ���������ʱ��ֱ�ӷ������ֵ,���߱�dp�������ӽṹ����.
//������ֻ�ǵ����Ķ������ظ�״̬�ļ�֦.
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 550
using namespace std;
int n,li[N],sum,ans;
bool vis[N][M][M];

int check(int a,int b,int c){
    return a+b>c && b+c>a && a+c>b;
}

int cal(int a,int b,int c){
    double p=sum/2.0;
    return p*(p-a)*(p-b)*(p-c);
}

void dfs(int k,int a,int b,int c){
    if(vis[k][a][b]) return;//��k����Ʒ �Ѿ�ѡ��2���ߵĳ��� a��b���״̬֮ǰ�Ѿ�������,��ô֮���Ȼ���ظ������� ����
    vis[k][a][b]=1;//�������״̬�ѷ��ʹ�
    //��֦ ������ÿ���ߵĳ��� �����ܳ����ܳ���һ��
    //�����Ը��ݾ�ֵ����ʽ��֦ ��ֻ�ж�a>sum/3,��Ϊ�����������������������߳���ӽ���ʱ�� ֤���ڴ�:https://www.zybang.com/question/58b4e6b1be64233113578c3d1e1a9c99.html
    //��ע��ֻ���ж�һ����a>sum/3.���������߲�����,��Ϊʵ�ʿ��ܲ����ܸպôճ��ȱ�������,��Ȼ������1��2���߶�����sum/3,����ᵼ�²��ܱ������������
    if(a>sum/2 || b>sum/2 || c>sum/2) return;
    if(k == n+1){//���е�Χ����ѡ�� �ж��Ƿ񹹳�������
        if(check(a,b,c))
            ans=max(ans,cal(a,b,c));//����ע�����ú��׹�ʽ����ʱ�ȱ�ֱ�ӿ�������̩�ռ���չ��,ֻ��¼Ҫ���������ֵ,�ܼ��ٸ��Ӷ�
        return;
    }
    dfs(k+1,a+li[k],b,c);//����k��Χ��ƴ����1����
    dfs(k+1,a,b+li[k],c);//����k��Χ��ƴ����2����
    dfs(k+1,a,b,c+li[k]);//����k��Χ��ƴ����3����
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&li[i]);
        sum+=li[i];
    }
    ans=-1;
    dfs(0,0,0,0);
    if(ans!=-1)//�кϷ�������
        printf("%d",(int)(sqrt(ans)*100));
    else
        printf("-1");
    return 0;
}
*/
