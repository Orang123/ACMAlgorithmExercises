/*
����:���������������������,������ʿ�õ�һ��NԪ�ĳ�Ʊ(��ס,ֻ��һ�ų�Ʊ),
Ϊ�˷�ֹ�Լ���ս����Ƶ��������,���������Լ���һЩ����,�����������˵ؾ��̵�ǰ.
������ʿ:"��Ҫ�����!"
�ؾ�����:"�������������ֵ���,Ѫƿ150��һ��,ħ��ҩ200��һ��,�޵�ҩˮ350��һ��.
"������ʿ:"�õ�,����һ��Ѫƿ."˵�����ͳ�����NԪ�Ĵ󳮵ݸ��ؾ�����.
�ؾ�����:"��������������,��������û���ҿ���Ǯ��ϰ�ߵ�,���Ǯ���Ƕ���С�����˵�,�ٺ�."
������ʿ:"......"
������ʿ��,�����Ǯ��С���͸����������Լ�����һ�����,�����Ժ�Ҫ���,������˷��ڼ���Ҳ��,
����Ҫ����������׬С��.����������ʿϣ�����ܰ�������һ��,������Ҫ���ؾ����˶���С��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1248
˼·:��ȫ��������.��Ʒ��ֵ������ֱ�Ϊ150��200��350.���������ܶ��װ,��Ǯ��������ʣ��.
*/
//ac 0ms ��ȫ�������� һά���� ��ǰdp
#include<bits/stdc++.h>
#define M 10100
using namespace std;
int n,dp[M],val[4]={0,150,200,350};
int main(){
    int T;
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=3;i++)
        for(int j=val[i];j<M;j++)
            dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("%d\n",n-dp[n]);//����Ҫ�ҵ�Ǯ,����Ķ���Ҫ�����ܶ໨Ǯ
    }
    return 0;
}

/*
//ac 0ms ��ȫ�������� һά����
#include<bits/stdc++.h>
#define M 10100
using namespace std;
int n,dp[M],val[4]={0,150,200,350};
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=3;i++)
            for(int j=val[i];j<=n;j++)
                dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
        printf("%d\n",n-dp[n]);//����Ҫ�ҵ�Ǯ,����Ķ���Ҫ�����ܶ໨Ǯ
    }
    return 0;
}
*/

/*
//ac 15ms ��ά����
#include<bits/stdc++.h>
#define N 4
#define M 10100
using namespace std;
int n,dp[N][M],val[N]={0,150,200,350};
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=3;i++){
            for(int j=0;j<=n;j++){
                if(j>=val[i])
                    dp[i][j]=max(dp[i-1][j],dp[i][j-val[i]]+val[i]);
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",n-dp[3][n]);//����Ҫ�ҵ�Ǯ,����Ķ���Ҫ�����ܶ໨Ǯ
    }
    return 0;
}
*/

/*
//ac 15ms ����ö������dfs ʱ�临�Ӷ�O(n^(n/min(w[i])))
//����vis���仯�������� ��tle
#include<bits/stdc++.h>
#define N 4
#define M 10100
using namespace std;

int n,ans,vis[M];

//O(n^(�ܼ�Ǯ/min(w[i]))) ����nΪ��Ʒ������,ʵ�ʵ��ܼ�Ǯ����3000ʱ,����������Ӷ��Ѿ��ܸ���.
void dfs(int sum){
    if(sum>n)
        return;
    if(vis[sum])
        return;
    vis[sum]=1;
    if(sum>ans)
        ans=sum;
    //��Ϊÿ����Ʒ����������,ÿһ����Ʒ����3��ȡ�� �ֱ���150��200��350
    //O(3^(�ܼ�Ǯ/150))
    dfs(sum+150);
    dfs(sum+200);
    dfs(sum+350);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        dfs(0);
        printf("%d\n",n-ans);
    }
    return 0;
}
*/

/*
//ac 15ms ����ö��3����Ʒ����������� ��¼����ܻ��ѵ�Ǯ
//һ���Ż��޵�ҩˮ�ļ�Ǯ(350)���õ���Ѫƿ(150)+ħ��ҩƷ(200)�ļ�Ǯ
//��˿���ֻö��Ѫƿ��ħ��ҩƷ�ļ�Ǯ,���Ӷȱ����2��ѭ��,��O((n/w[1])*(n/w[2]))
//��������ֻ������Ʒ����Ƚ���,���n�ϴ�,ʵ�ʸ��Ӷ���O(num1*num2*..*numn),��Ȼ���Ǹ�����ʽʱ��
#include<bits/stdc++.h>
#define N 4
using namespace std;

int n,ans,w[4]={0,150,200,350};

int main(){
    int T,num1,num2,num3;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        num1=n/w[1];
        num2=n/w[2];
        //num3=n/w[3];
        //for(int i=0;i<=num1;i++){//O(num1*num2*num3)
            //for(int j=0;j<=num2;j++){
                //for(int k=0;k<=num3;k++){
                    //int tp=i*w[1]+j*w[2]+k*w[3];
                    //if(tp<=n && tp>ans)
                        //ans=tp;
                //}
            //}
        //}
        for(int i=0;i<=num1;i++){//O(num1*num2)
            for(int j=0;j<=num2;j++){
                //for(int k=0;k<=num3;k++){
                int tp=i*w[1]+j*w[2];
                if(tp<=n && tp>ans)
                    ans=tp;
                //}
            }
        }
        printf("%d\n",n-ans);
    }
    return 0;
}
*/

/*
//ac 0ms �������bfsö�ٿ��ܵ�״̬�� ����ʣ��Ǯ����С���
//����vis���ػ�MLE,��ȻҲ��TLE
//ÿ��״̬����n�ֿ��ܵ�ת��,������,ÿ����Ʒ���Ϊ1,�ʱ�临�Ӷ� �о�Ҳ���Ǹ�����ʽʱ��
//����n=2,�Ƚ�С ���Կ���bfs�������
#include<bits/stdc++.h>
#define N 4
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

int n,ans,vis[M];

//���Ӷ��� �����������ӵ�Ԫ�ظ���,����ÿ����Ʒ�۸�1Ԫ,��ô�ܼ�ǮnԪ,��ô�����������n��Ԫ��
//���ʱ�临�Ӷ�������ʱ��O(n)
void bfs(){
    queue<int> Q;
    Q.push(n);
    int tp;
    while(!Q.empty()){
        tp=Q.front();
        if(ans>tp)
            ans=tp;
        Q.pop();
        //���֮ǰö�ٹ�tp-150����״̬ ��:vis[tp-150]=1,�Ͳ���ö��
        if(tp-150>=0 && !vis[tp-150]){
            Q.push(tp-150);
            vis[tp-150]=1;
        }
        if(tp-200>=0 && !vis[tp-200]){
            Q.push(tp-200);
            vis[tp-200]=1;
        }
        //��Ϊ�޵�ҩˮ350������ Ѫƿ150��ħ��ҩ200��϶���,��˲���ö�����״̬��
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        ans=n;
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms ��ѧ���� ���Ӷ��ǳ���ʱ��
//����ҩƷ��Ǯ150,200,����С��150����ֱ�Ӿ����Ǹ���,����300�Ķ����ᳬ��50,
//���Դ�������ֱ��%50.����֮�������ж�%200��%150�ĸ�С,�ĸ�Сȡ�ĸ�.
#include<bits/stdc++.h>
using namespace std;

int n,ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        if(n>=150){
            if(n>=300)
                n%=50;
            else{
                if(n%150<n%200)
                    n%=150;
                else
                    n%=200;
            }
        }
        printf("%d\n",n);
    }
    return 0;
}
*/
