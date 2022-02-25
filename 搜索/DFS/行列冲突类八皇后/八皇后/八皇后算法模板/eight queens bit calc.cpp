#include<cstdio>
#define N 10
int n=8,cnt,a[N];
/*
c:����ǰ��k�����б����õ�λ�õĶ����Ʊ�ʾ 1�������� 0������� ��λ��
l:������ϵ��´�������ĸ��Խ����ڵ�ǰ��k�б����õ�λ�õĶ����Ʊ�ʾ
r:������ϵ��´������ҵ����Խ����ڵ�ǰ��k�б����õ�λ�õĶ����Ʊ�ʾ
k:����׼���ڵ�k�з��ûʺ�
*/
void dfs(int k,int c,int l,int r){
	int sta,t;
	if(k == n+1){
		cnt++;
        return;
	}
    sta = c | l | r;//sta�����ۺ� ���к������Խ��ߺ�ĵ�k�б����õ�λ�� �����Ʊ�ʾ
    for(int i=0;i<n;i++){
        t = 1<<i;//�����(i+1)�е�λ��Ϊ1 ��Ϊ��1����1<<0
        if(~sta&t){//sta��λȡ��1�ʹ�����õ�λ�� ��t ��λ�� ���Ϊ1����һ�п���,Ϊ0������һ�б�����
            //a[k] = i;
            //���ڵ�k+1�е� ���е�״̬ ��Ҫ��һ������c|t,���Խ�����ΪҪ��������,ռλ��������1λ,����l|t��Ҫ������1λ,������ͬ��Ҫ��������Ҫ���ƶ�һλ
            dfs(k+1,c|t,(l|t)<<1,(r|t)>>1);
        }
    }
}

int main(){
	dfs(1,0,0,0);
	printf("%d\n",cnt);
	return 0;
}

/*
��һ������ ������λ����Ч����һ����
https://www.cnblogs.com/lukelmouse/p/10579916.html
#include <bits/stdc++.h>
using namespace std;
int n,tot,goal = (1<<8) - 1;
void dfs(int lvis,int rvis,int row){
    int safe,next;
    if(row != goal){
        safe = goal & (~ (row|lvis|rvis));//�õ����н�
        while(safe){//
            next = safe & (~safe + 1);// �õ� ���ұߵ�һ��λ��,safe & (-safe)
            safe ^= next;// ɾ�����ұߵ�һ����
            bfs((lvis|next)<<1,(rvis|next)>>1,row|next);
        }
    }
    else
        tot++;
}
int main(){
    //cin>>n;
    n = 8;
    dfs(0,0,0);
    cout<<tot<<endl;
    return 0;
}
*/
