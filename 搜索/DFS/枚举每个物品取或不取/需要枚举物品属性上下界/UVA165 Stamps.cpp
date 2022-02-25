/*
����:ժ������
������Ʊ����h������Ʊ��ֵ����k��Ҫ����ѡ��k����ֵ����Ʊ��
ͨ����Щ1 ~ h����Ʊ����ɵ���ֵ���������������ָ��1��ʼ�����ܵõ�����������ֵ.
���磺ѡ��1 �� 2������h= 3ʱ)������ɵ���ֵ����1��2��3��4��5��6�����Դ�ʱ�����������Ϊ6
�����ѡ��1 ��3 �Ļ�������ɵ���ֵ������1��2��3��4��5��6��7��  9��ע�⣬û��8����������������Ϊ7.
����:https://www.luogu.com.cn/problem/UVA165
˼·:��Ҫö����Ʊ��ֵ������,������޾���ǰcur��ѡ������Ʊ������������ֵ+1,
�����Ϳ���ʹ��cur+1����Ʊ����ֵ���ɵ��µ���ֵ�ܺ�ǰ�������.
��ǰ��cur����Ʊ�� �½��ǵ�cur����Ʊ����ֵ+1,ͬ����Ϊ��ʹ�õõ�����������ֵ��
��Ʊ.
*/
//ac 10ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10
#define M 200
using namespace std;

//a[cur]��ʾ��cur����Ʊ����ֵ
//b[cur]��ʾǰcur����Ʊ��ɵ������������Ʊ����ֵ
//vis[sum]=1��ʾ�ܹ���sum��ֵ����Ʊ
int h,k,a[N],b[N],vis[M],ans,res[N];

//����ѡ����ǰcur����Ʊ ���ܵõ���Щ��ֵ
void cal(int cur,int num,int sum){
    //���ﲻ����vis[sum]��ۼ�֦,��Ϊ��ֵ��ͬ Ҳ��������ͬ,
    //������Ҳ���ܽ��俪�ɶ�άvis[num][sum]���,���������ж����������ֵ,��Ϊ��֪������
    vis[sum]=1;
    if(num == h)
        return;
    for(int i=0;i<=cur;i++)
        cal(cur,num+1,sum+a[i]);
}

void dfs(int cur){
    if(cur == k){
        if(b[cur-1]>ans){
            ans=b[cur-1];
            memcpy(res,a,sizeof(a));
        }
        return;
    }
    for(int i=a[cur-1]+1;i<=b[cur-1]+1;i++){//ö�ٵ�cur����Ʊ�Ŀ�����ֵ �½���a[cur-1]+1,�Ͻ���b[cur-1]+1
        a[cur]=i;
        memset(vis,0,sizeof(vis));
        cal(cur,0,0);
        int j=1;
        while(vis[j])//��j=1��ʼ�ж�����������ֵ,��һ��vis[j]==0��ֵ����,�������ֵ����j-1
            j++;
        b[cur]=j-1;
        dfs(cur+1);
    }
}

int main(){
    while(scanf("%d%d",&h,&k) && h+k){
        ans=0;
        a[0]=1;
        b[0]=h;
        dfs(1);
        for(int i=0;i<k;i++)
            printf("%3d",res[i]);
        printf(" ->%3d\n",ans);
    }
    return 0;
}
