/*
����:����һ��n�������У�Ȼ����k��ѯ�ʣ�ÿ��ѯ��һ��t,
������n���������к͵ľ���ֵ��ӽ�t��Ϊ���٣������������������ұ߽硣
n<=100000,0<=t<=10^9.
����:http://poj.org/problem?id=2566
˼·:��ȡ.����ͳ�Ƴ�ǰ׺��,����ǰ׺�ʹ�С��������,��¼��ǰ׺�͵Ľ����±�,
�������ܱ�֤ǰ׺�͵ĵ�����,����Ӧ�ó�ȡ�������t���Ƚ�,���ƶ�����ָ��.
�������ź����,ǰ׺��֮�����Ѿ���ǰ׺�͵ľ���ֵ��,�����ٵ���ȡ����ֵ.
*/
//ac 63ms
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

pair<int,int> pp[N];

int main(){
    int n,k,t;
    int left,right,l,r,res,ans,sum;
    while(scanf("%d%d",&n,&k)&&n+k){
        pp[0]=make_pair(0,0);
        for(int i=1;i<=n;i++){
            scanf("%d",&pp[i].first);
            pp[i].first+=pp[i-1].first;
            pp[i].second=i;
        }
        sort(pp,pp+n+1);
        while(k--){
            scanf("%d",&t);
            l=0,r=1,ans=INF;//t�п���Ϊ0,���l��r��ʼ���������,����l=0,r=1,�����wa. ���в���Ϊ��
            while(r<=n){
                res=pp[r].first-pp[l].first;
                if(abs(t-res)<ans){
                    ans=abs(t-res);
                    sum=res;
                    left=pp[l].second;
                    right=pp[r].second;
                }
                if(res>t)//��t��,l++��ʹ��res��С ���ӽ�t
                    l++;
                else if(res<t)//��tС,r++��ʹ��res���� ���ӽ�t
                    r++;
                else//res == t�Ѿ���� �ͽ���
                    break;
                if(l==r)//l,r����ǰ׺�Ͳ������,������� ���в���Ϊ��
                    r++;
            }
            if(left>right)//��˵��±�Ҫ��С��
                swap(left,right);
            printf("%d %d %d\n",sum,left+1,right);//ʵ����˵���Ϊǰ׺������,�±��left+1��ʼ
        }
    }
    return 0;
}
