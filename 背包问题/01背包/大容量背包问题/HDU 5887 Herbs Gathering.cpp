#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//ac 109ms ̰������+����+��֦
/*
����:n����Ʒ,ʱ������m,����ÿ����Ʒ�ļ�ֵ��ʱ��,����m������,���ļ�ֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5887
˼·:
����ʵ�ʾ��Ǵ�������01��������,����Ϊ��ʱ�������10^9,����ֵ���Ҳ��10^9,
����Ҳ�޷�����ֵ�ͱ��������������õ���ͬ��ֵʱ��Сʱ�� �����ж�����ֵ.
����ֻ��̰������+dfs��������+��׺��֦
��n m����Сʱ,������01�������ܽ��������,����01����Ч�����Աȱ���Ҫ��.
��n�ϴ�m��Сʱ,���������ᳬʱ,��01�������ɺܸ�.
��Ϊʱ��͵÷� ���ϴ�,����Ҳ�����ñ�������¼���Ž���м�֦
*/
int n,m;
ll all[120],ans;
struct Node{
    int cost,score;
    bool operator <(const Node &x)const{
        /*
        ������Ҫ����ʱ�����ĴӴ�С����,������������,����ʱ��϶��,�����÷�Ҳ�϶�,
        ����dfsʱ������ѡȡ�÷ֽ϶����Ʒ,��ô������dfs���ݱ���,
        ����sum+all[num]<ans returnҲ���Ա��������������.����ֱ�Ӹ��ݵ÷ֽ������лᳬʱ,��̫��...
        ��֮���̰��Ԥ��������Ҳ����ѧ��,һ����Ʒ������ͼ�ֵ������û��ֱ�������,֮�䰴�������
        ��ֵ����,��֦��Ч��Ҳ�����.
        */
        return cost>x.cost;
    }
}node[120];

//109ms Ч�ʽϸ� ����
void dfs(int num,int time,ll sum){
    if(sum>ans) ans=sum;
    if(sum+all[num]<ans) return;//����ǰѡ�����Ʒ�ܵ÷ּ��Ϻ������еĵ÷ֻ�С��֮ǰ�����õ������÷�ʱ,��֦,��������.
    if(num == n+1) return;
    if(node[num].cost<=time)
        dfs(num+1,time-node[num].cost,sum+node[num].score);
    dfs(num+1,time,sum);
}

/*//592ms
ò�ƶ���������Ϸ���������(����Ҫvis���)��dfsѭ���ķ�ʽ��ȽϺ�ʱ.
������ѭ���ṹ��,Ҫ˵������������dfs���ô�������,����ջҲԽ��.
void dfs(int st,int time,ll sum){
    if(sum+all[st]<ans) return;
    if(sum>ans)
        ans=sum;
    for(int i=st;i<=n;i++){
        if(node[i].cost<=time)
            dfs(i+1,time-node[i].cost,sum+node[i].score);
    }
}
*/

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(all,0,sizeof(all));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&node[i].cost,&node[i].score);
        sort(node+1,node+1+n);
        for(int i=n;i>=1;i--)//�����׺��
            all[i]=all[i+1]+node[i].score;
        ans=-1;
        dfs(1,m,0);
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 15ms ���յ÷�*ʱ��Ļ��Ӵ�С������ �Ƚ�ǿ�ļ�֦
https://www.cnblogs.com/TnT2333333/p/7695729.html 0ms val/ti�����֦
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
const int N = 108;

struct data{
    LL w, val;
    bool operator<(const data &tp)const{
        return val * tp.w > tp.val * w;
    }
}pk[N];

int n;
LL lim,ans;

void dfs(int d, LL w, LL val){
    if(val > ans) ans =  val;
    if(d >= n) return;
    //�����������ǰ��ֵ+�������������Ʒ���ǵ�ǰ��d����Ʒ�ļ�ֵ ��������֮ǰ���ż�ֵ �ͼ�֦
    //����lim-w�ǻ�ʣ�¶���ʱ��(lim - w)/(LD)pk[d].w �ǻ���ѡ������d����Ʒ ����d����Ʒ���ٶ�Ϊ��d����Ʒ��ʱ�䡢��ֵ
    //��Ϊ����ʱ��ͼ�ֵ�˻�����,��ǰ��d�� ��ʱ��ͼ�ֵ���ص�ƽ������������ һ��������,���Ժ�����Ʒ�����������������������d����Ʒ
    if(val + (LD)pk[d].val / (LD)pk[d].w * (lim - w)<= ans) return;
    if(w + pk[d].w <= lim) dfs(d + 1, w + pk[d].w, val + pk[d].val);
    dfs(d + 1, w, val);

}

int main(){
    while(~scanf("%d %I64d", &n, &lim)){
        for(int i = 0; i < n; i++) scanf("%I64d %I64d", &pk[i].w, &pk[i].val);
        sort(pk, pk + n);
        ans = 0;
        dfs(0, 0, 0);
        printf("%I64d\n", ans);
    }
    return 0;
}
*/

