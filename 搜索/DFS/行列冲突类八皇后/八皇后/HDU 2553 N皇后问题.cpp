/*
����:��N*N�ķ������̷�����N���ʺ�ʹ�����ǲ��໥����
��������2���ʺ�������ͬһ�ţ�ͬһ�У�Ҳ�������������̱߿��45�ǵ�б���ϡ�
��������ǣ����ڸ�����N������ж����ֺϷ��ķ��÷�����
����:https://acm.hdu.edu.cn/showproblem.php?pid=2553
˼·:λ����ʵ��8�ʺ�
*/
#include<cstdio>
int n,cnt,ans[11];
void dfs(int k,int c,int l,int r){
	int sta,t;
	if(k == n+1){
		cnt++;
        return;
	}
    sta = c | l | r;
    for(int i=0;i<n;i++){
        t = 1<<i;
        if(~sta&t)
            dfs(k+1,c|t,(l|t)<<1,(r|t)>>1);
    }
}

int main(){
    for(int i=1;i<=10;i++){
        cnt=0;
        n=i;
        dfs(1,0,0,0);
        ans[i]=cnt;
    }
    while(scanf("%d",&n)&&n)
        printf("%d\n",ans[n]);
	return 0;
}
