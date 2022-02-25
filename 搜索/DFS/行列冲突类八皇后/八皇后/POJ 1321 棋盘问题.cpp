/*
����:��һ������n*n��״�����̣���״�����ǲ�����ģ�����ڷ�k�����ӣ�����û������
Ҫ��ڷ�ʱ������������Ӳ��ܷ��������е�ͬһ�л���ͬһ�У����������ڸ�
����״�ʹ�С�����̣��ڷ�k�����ӵ����п��еİڷŷ���C��
k<=n;
����:http://poj.org/problem?id=1321
˼·:��Ϊ���ӵ������������������еĸ���,��ô�ʹ��ڷŲ��������,
�ھ���İ˻ʺ������� ��ö��ÿ���Ƿ��������.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,cnt,col[10];
char map0[10][10];

void dfs(int row,int num){
    if(num == k){
        cnt++;
        return;
    }
    if(row == n+1) return;
    for(int i=1;i<=n;i++){
        if(map0[row][i]=='#' && !col[i]){
            col[i]=1;
            dfs(row+1,num+1);
            col[i]=0;
        }
    }
    /*
    ��Ϊ�п���k<n&k<'#'���̵�λ�ø���,�����п������Ӷ��ڷ�����,
    ���Ǻ�����л���ʣ�������λ��,���Լٶ��Ȳ���ǰ�����,�Ȱں������,
    ��������ö�ٳ����п��ܵİڷ�.
    */
    dfs(row+1,num);
}

int main(){
    while(scanf("%d%d",&n,&k) && n!=-1&&k!=-1){
        cnt=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&map0[i][j]);
        }
        dfs(1,0);
        printf("%d\n",cnt);
    }
	return 0;
}
/*
//λ����汾
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,cnt,col[10];
char map0[10][10];

void dfs(int row,int num,int c){
    if(num == k){
        cnt++;
        return;
    }
    if(row == n+1) return;
    for(int i=0;i<n;i++){
        int j=1<<i;
        if(~c&j && map0[row][i+1]=='#')
            dfs(row+1,num+1,c|j);
    }
    dfs(row+1,num,c);
}

int main(){
    while(scanf("%d%d",&n,&k) && n!=-1&&k!=-1){
        cnt=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&map0[i][j]);
        }
        dfs(1,0,0);
        printf("%d\n",cnt);
    }
	return 0;
}

*/
