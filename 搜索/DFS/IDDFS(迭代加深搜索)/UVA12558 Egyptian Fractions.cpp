/*
����:��������
����һ������a/b,Ȼ�����k����q[i],Ҫ���a/b��Ϊ������ͬ�ķ���Ϊ1��������,
Ҫ��ֳɵķ����ķ�ĸ�в��ܳ���q[i].���ж�������������ֳ��������ٵ�һ��.
������ж������,Ӧʹ��һ��ķ�ĸ��С,���������,�ڶ�����С,�Դ�����.
ע��:���������еķ�ĸ�ǵ���������.
2<=a<b<=876,gcd(a,b)=1,2<=q[i]<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4003
˼·:���ȶ���ö�ٵķ�ĸ������û����ȷ�Ͻ��,����޷�ʹ��bfsȥö��ÿһ����
���п���״̬ ��MLE,��Ϊ��ĸ�������ϸ������,����bfs��״̬�ǲ����ظ���.
���Ե������������������ӷ�������,ö��ÿһλ�ϵķ�ĸ.Ϊ�˷����֦���ۺ���,
dfsʱ ��ʾ����ʣ�������ֵ,����Ҫ��ȥ��ǰ����.
*/
//ac 2.25s IDA*
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define N 1100
typedef long long ll;
using namespace std;

ll res[N],ans[N];
//��Ϊdfs���õ���ʣ�������ֵ,��ȥ�жϵ�ǰ���������Ƿ�Ϊ1,
//�Լ���ĸ�Ƿ��� k�������õ�,����ĸ��ֵ���ܴܺ�,��vis���������Խ��.
set<ll> vis;

ll gcd(ll a,ll b){
    return !b?a:gcd(b,a%b);
}

int check(int d){
    for(int i=d;i>=0;i--){//������������ͬʱ,�Ӻ���ǰ�ж�,��������ʱ,�����ǰ��ĸֵ��С �����.
        if(res[i]!=ans[i])//����������ܶ�
            return ans[i] == -1 || res[i]<ans[i];
    }
    return 0;//ԭ���� �ǲ�����ֺ�֮ǰ��ȫ��ȵ� �����
}

int dfs(int d,int dep,ll a,ll b,ll st){
    if(d == dep){
        if(a == 1 && !vis.count(b)){//ʣ��ķ��� ���Ӹպ�Ϊ1,��ĸ���ڲ���ʹ�÷�Χ�ڼ���
            res[d]=b;//��d+1��������1/b
            if(check(d)){//�ж��Ƿ��֮ǰ��ĸ��С
                for(int j=0;j<=d;j++)//ʵ����d+1������ ��Ϊ�±�0..d
                    ans[j]=res[j];
                return 1;
            }
        }
        return 0;
    }
    int ok=0;
    st=max(st,b/a+1);//stҪȡ��ĸ��������һ�� ��Ҫ��ʵ��ʣ�����a/b b/a+1ȡ���ֵ,�п���1/(i+1)Ҫ����b/a
    for(ll i=st;;i++){
        if(vis.count(i))//i ����ʹ��
            continue;
        //��֦:�������dep+1-d����ȫ����1/i С�ڵ���ʣ�µ�a/b�򷵻�,��������Ϊʵ�ʷ�ĸ�����ǵ�����
        //1/i * (dep-d+1)<=a/b
        if(b*(dep-d+1)<=a*i)//��Ϊʵ�ʷ���������dep+1����,��Ϊ����С���Ǵ�0..d
            break;
        ll bb=b*i;//��ĸͨ��
        ll aa=a*i-b;//����Ҫ��ȥb,��ʾ����1/i��ʣ�µķ���
        ll g=gcd(aa,bb);
        res[d]=i;
        //����Ҫ�����g,��ĸ�����������i+1
        if(dfs(d+1,dep,aa/g,bb/g,i+1))//��Ϊ ��������һ��ʱ,Ҫ����Ӻ���ǰ��ĸ�ϴ�Ľ�,������ﲻ��ֱ�ӽ���
            ok=1;
    }
    return ok;
}

int main(){
    int T,k,cas=0;
    ll a,b,x;
    scanf("%d",&T);
    while(T--){
        cas++;
        vis.clear();
        memset(ans,-1,sizeof(ans));
        scanf("%lld%lld%d",&a,&b,&k);
        while(k--){
            scanf("%lld",&x);
            vis.insert(x);
        }
        for(int i=1;;i++){
            //b/a+1��ʾ a/b�ķ����� ����ʼ����ȡ����С��ĸ���½�
            if(dfs(0,i,a,b,b/a+1)){
                printf("Case %d: %lld/%lld=",cas,a,b);
                for(int j=0;j<=i;j++){
                    printf("1/%lld",ans[j]);
                    if(j!=i)
                        printf("+");
                }
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

/*
//RE TLE ����dfs
//RE ����Ϊʵ�����������ķ���,���������ܶ�,û����ȷ�Ͻ�,TLE Ҳ�ǿ϶���,������������ͱȽ�����
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define N 1100000
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int num;
ll res[N],ans[N];
set<ll> vis;

ll gcd(ll a,ll b){
    return !b?a:gcd(b,a%b);
}

int check(int d){
    for(int i=d;i>=0;i--){
        if(res[i]!=ans[i])
            return res[i]<ans[i];
    }
}

void dfs(int d,ll a,ll b,ll st){
    if(a == 1 && !vis.count(b) && d<=num){
        res[d]=b;
        if(d<num || (d==num && check(d))){
        	num=d;
            for(int j=0;j<=d;j++)
                ans[j]=res[j];
		}
        return;
    }
    st=max(st,b/a+1);
    for(ll i=st;;i++){
        if(vis.count(i))
            continue;
        if(b*(num-d+1)<=a*i)
            break;
        ll bb=b*i;
        ll aa=a*i-b;
        ll g=gcd(aa,bb);
        res[d]=i;
        dfs(d+1,aa/g,bb/g,i+1);
    }
}

int main(){
    int T,k,cas=0;
    ll a,b,x;
    scanf("%d",&T);
    while(T--){
        cas++;
        vis.clear();
        num=INF;
        scanf("%lld%lld%d",&a,&b,&k);
        while(k--){
            scanf("%lld",&x);
            vis.insert(x);
        }
        dfs(0,a,b,b/a+1);
        printf("Case %d: %lld/%lld=",cas,a,b);
        for(int j=0;j<=num;j++){
            printf("1/%lld",ans[j]);
            if(j!=num)
                printf("+");
        }
        printf("\n");
    }
    return 0;
}
*/
