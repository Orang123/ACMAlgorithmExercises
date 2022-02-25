/*
����:��һ��n*m������,��k����ɫ,ÿ����ɫ��ciƿ,
��Ҫ�����ڵ�����Ϳ�ɲ�ͬ��ɫ,������Ҫ��������������.
���Ƿ����.���Ⱦɫ����.
0<n,m<=5.0<k<=n*m.
c[1]+c[2]+..c[k]==n*m,������ɫ�ĸ���ǡ�õ��ڸ�����Ŀ.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5113
˼·:dfsö��ÿ�����ӿ���Ϳ����ɫ,һ����֦:��ʣ��δȾɫ
�ĸ�����Ŀ+1��һ��С��ĳ����ɫʣ�����ʱ,������ɫҪ��
ȫ��Ϳ��ȥ,��Ȼ�����������ɫͬɫ,����.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,k,cas,mp[5][5],c[30];
int dfs(int num){
    if(num == n*m) return 1;
    /*
    ��֦,��ʣ��δȾɫ�ĸ�����Ŀ+1��һ��С��ĳ����ɫʣ�����ʱ,
    ������ɫҪ��ȫ��Ϳ��ȥ,��Ȼ�����������ɫͬɫ,����.
    eg:3x3������ֻȾһ��ɫʱ������ʱ,���ֻ��Ⱦ5������,4*4������һ����ɫ���Ϳ8������,
    Ҳ����ֻ��һ����ɫ,���������ʣ��δȾɫ��һ��+1��λ�ÿ���Ϳ��֤����λ�ò�ͬɫ.
    */
    for(int i=1;i<=k;i++)
        if((n*m-num+1)/2<c[i]) return 0;
    int x=num/m,y=num%m;
    for(int i=1;i<=k;i++){
        if(!c[i]) continue;
        if(x>0 && i==mp[x-1][y]) continue;//�ж�����
        if(y>0 && i==mp[x][y-1]) continue;//�ж�����
        c[i]--;
        mp[x][y]=i;
        if(dfs(num+1)) return 1;
        c[i]++;
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&c[i]);
        printf("Case #%d:\n",cas);
        if(dfs(0)){
            printf("YES\n");
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(j) printf(" ");
                    printf("%d",mp[i][j]);
                }
                printf("\n");
            }
        }
        else
            printf("NO\n");
    }
    return 0;
}
