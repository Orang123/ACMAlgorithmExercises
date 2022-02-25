/*
����:ĳ�ط���һ�ײ�Ʊ����Ʊ��д��1��M��M����Ȼ����
�����������M����������ѡȡN����ͬ������Ȧ��ÿ��
����ֻ����һ�Ų�Ʊ����ͬ�Ĳ���Ĳ�Ʊ�ϵ�ѡ��ͬ��
ÿ�γ齱�����������Ȼ��X��Y�����ĳ���õ��Ĳ�Ʊ�ϣ�
��ѡN����Ȼ���ĵ����ͣ�ǡ�õ���X/Y�����������һ��
����Ʒ����֪�齱���X��Y�����ڵ������ǣ�����׼������
����Ʒ�����ܱ�֤֧�����л��ߵĽ�Ʒ��

����:��Ŀ������1~m����ȡn�����ж�������ϵĵ���֮�͵���x/y,
��Ϊ���ж���ÿ�Ų�Ʊÿ�������ѡ��ͬ��

1<=X,Y<=100. 1<=N<=10,1<=M<=50.
����:https://www.luogu.com.cn/problem/P2236
˼·:dfs+��׺��֦.
*/
//ac 3.99s dfsѭ������ö��
#include<cstdio>
#include<cmath>
const double eps=1e-10;
int n,m,vis[60],cnt;
double val,x,y;

void dfs(int st,int num,double sum){
    if(sum>val+eps) return;//��֦��ǰ�ʹ���sumʱ ����
    //��֦ ����ǰ�ͼ��Ϻ��� ��ÿһλ������1/st(��ĸԽСֵԽ��) ��(n-num+1)*1.0/st��С��Ҫ��ֵʱ ���ݷ���
    if(sum+(n-num+1)*1.0/st+eps<val) return;//��Ϊ�о��Ȳ�������߻�Ҫ�ټ���eps
    //��֦ ����ǰ�ͼ��Ϻ��� ��ÿһλ������1/m(��ĸԽ��ֵԽС) ��(n-num+1)*1.0/m����Ҫ��ֵʱ ���ݷ���
    if(sum+(n-num+1)*1.0/m>val+eps) return;//��Ϊ�о��Ȳ������ұ߻�Ҫ�ټ���eps
    if(num == n+1){
        if(fabs(val-sum)<eps) cnt++;//����sum��Ϊ����ԭ�� ���ܻ��val��
        return;
    }
    if(st == m+1) return;
    for(int i=st;i<=m;i++){//������Ҫ��O^2�Ų���TLE
        if(vis[i]) continue;
        vis[i]=1;
        dfs(i+1,num+1,sum+1.0/i);
        vis[i]=0;
    }
}

int main(){
    scanf("%d%d%lf%lf",&n,&m,&x,&y);
    val=x/y;
    dfs(1,1,0);
    printf("%d\n",cnt);
	return 0;
}

/*
//ac 3.59s dfsö��ÿ����Ʒȡ��ȡ
#include<cstdio>
#include<cmath>
const double eps=1e-10;
int n,m,vis[60],cnt;
double val,x,y,sum[60];

//��ǰ��ʼ��sum ��1~m�ĵ���ǰ׺��Ч�ʻ��һ��
void dfs(int st,int num,double sum0){
    if(sum0>val+eps) return;
    double maxs=sum0+sum[st+n-num]-sum[st-1];//ȡ��ǰst���n-num�ĸ���λ����֮�� Ϊ���ֵ
    double mins=sum0+sum[m]-sum[m-(n-num+1)];//ȡ��m�Ӻ���ǰȡn-num�ĸ���λ����֮�� Ϊ��Сֵ
    if(maxs+eps<val) return;
    if(mins>val+eps) return;
    if(num == n+1){
        if(fabs(val-sum0)<eps) cnt++;
        return;
    }
    if(st == m+1) return;
    dfs(st+1,num+1,sum0+1.0/st);
    dfs(st+1,num,sum0);
    //forѭ����Ҫ��O^2�Ż����ܹ�,�����TLE
}

int main(){
    scanf("%d%d%lf%lf",&n,&m,&x,&y);
    val=x/y;
    for(int i=1;i<=m;i++)
        sum[i]=sum[i-1]+1.0/i;
    dfs(1,1,0);
    printf("%d\n",cnt);
	return 0;
}
*/
