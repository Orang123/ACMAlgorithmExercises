/*
����:
��......���ο���Harry������һ��С�鷳,��Ϊ��������Hermione
�����ܹ���ס���е����������Ľ�һ�������ɴ��ʲô��,����
�������˱��������һ��ͳһ����:�����������a��ͷb��β��һ��
����,��ô�������þ�ǡ����ʹA������B����.Harry�Ѿ���������
���������ﶼ�г���һ����,���������æ����һ�����Ƿ��������
ʦ����ҵ,��һ��B(ball)���һ��M(Mouse),��֪��,������Լ���
����ɵĻ�,����ֻ����Hermione���,���ұ�����һ��Ѻú�ѧϰ�ĵ���.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1181
˼·:dfsö�ٺ�֮ǰβ��ĸƴ�ӵĵ���,һ����֦�� ������β��ͬ�ĵ��ʿ���ȥ��.
*/
//ac 15ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100
#define INF 0x3f3f3f3f
using namespace std;

int len[N],vis[N],cnt;
char str[N][N];

int dfs(char x){
    if(x == 'm')
        return 1;
    for(int i=0;i<cnt;i++){
        if(!vis[i] && str[i][0] == x){
            vis[i]=1;
            if(dfs(str[i][len[i]-1]))
                return 1;
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    while(scanf("%s",str[cnt])!=EOF){
        len[cnt]=strlen(str[cnt]);
        if(str[cnt][0] != str[cnt][len[cnt]-1])
            cnt++;
        while(scanf("%s",str[cnt]) && str[cnt][0] !='0'){
            len[cnt]=strlen(str[cnt]);
            if(str[cnt][0] != str[cnt][len[cnt]-1])
                cnt++;
        }
        int flag=0;
        for(int i=0;i<cnt;i++){
            if(str[i][0] == 'b'){
                vis[i]=1;
                if(dfs(str[i][len[i]-1])){
                    printf("Yes.\n");
                    flag=1;
                    break;
                }
                vis[i]=0;
            }
        }
        if(!flag)
            printf("No.\n");
        cnt=0;
        memset(vis,0,sizeof(vis));
    }
    return 0;
}
