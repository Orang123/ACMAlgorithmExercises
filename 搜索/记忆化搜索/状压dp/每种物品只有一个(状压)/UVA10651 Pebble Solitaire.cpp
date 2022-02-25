/*
����:ժ������
Pebble Solitaire��һ����Ȥ����Ϸ�����õ�һ��������һ��С���İ壬
��Щ�����ֻ��һ��û�б�����ʯռ�ݡ� ��Ϸ��Ŀ���Ǵ��������Ƴ�����
�ܶ�Ķ���ʯ���������������������Ϳ��Խ����ƶ�����������������ڵġ�
������һ��ֱ�ߵĶ�������������ΪA��B��C�����м�ΪB������A�ǿյģ�
��B��C�Ͼ���һ��ʯ�ӡ���ô����԰�C�ϵ�ʯ���Ƶ�A�ϣ�������B�е�ʯ�ӡ�
����Լ����ƶ�ʯ�ӣ�ֱ���޷����ƶ�Ϊֹ������������У���������һ����
����Ϸ���壬��һ������һ���߷���ʮ����С���İ塣 ÿ����Ϸ��ʼʱ����һ
Щ���ϱ�����ʯ�ӡ����������ʹ�������ٵĶ���ʯ���������ϡ�
�� a) �������ֿ��ܵ��ƶ����ֱ���8->6��7->9��
b) Ϊ a) ѡ��ڶ����ƶ���ʽ�Ľ������ʱ���������ƶ���ʽ���ֱ���5->7����6->4��
c) ��Ϊ b) ������һ��ѡ��Ľ������ʱ��û���������ƶ���ʽ�ˡ�

�����֮���Ǹ���12��������'o','-'���,ת������'oo-' -> '--o','-oo'->'o--',���������ʣ�¼���'o'��
����:https://www.luogu.com.cn/problem/UVA10651
˼·:����Ҫö����������λ,���Ƿ�����i,i+1Ϊ'o',i+2Ϊ'-',��i,i+1תΪ'-',i+2תΪ'o'.
����i,i-1Ϊ'o',i-2Ϊ'-',��i,i-1תΪ'-',i-2תΪ'o'.������ת���Ĺ�����,12��С����'o'��
'-'�������Ҫ�ö�����λ����ʾ״̬��Ψһ��,�����ٲ���ת�������л�����ص�������,��Ҫ��¼
��Щ�ص�������Ĵ�.
���仯����,dp[cur]��ʾ��cur״̬(����cur)���ܱ仯ת�Ƶ�����״̬��'o'���ٵĸ���.
*/
//ac 0ms ���仯���� �ж��ַ���str���㵱ǰ״̬
//dp[cur]=1/0 ����ǰ�����϶���ʯ�Ķ�����λ��״̬֮ǰ�Ƿ�õ���,1�����Ѿ����ֹ�,0����δ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[1<<12],ans;
char str[N];

//���㵱ǰ״̬ 'o'��ʾ�Ķ�����λ1
int calState(){
    int sta=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            sta|=1<<i-1;
    }
    return sta;
}

//���㵱ǰ״̬str��,'o'�ĸ���
int calNum(){
    int cnt=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            cnt++;
    }
    return cnt;
}

void dfs(int cur){
    if(dp[cur])
        return;
    dp[cur]=1;
    ans=min(ans,calNum());
    for(int i=1;i<=12;i++){
        if(str[i] == 'o'){
            //�ж�i,i+1����'o' i+2����'-'
            if(i<=10 && str[i+1] == 'o' && str[i+2] == '-'){
                str[i]=str[i+1]='-';//i��i+1��Ϊ'-',i+2��Ϊ'o'
                str[i+2]='o';
                dfs(calState());
                str[i]=str[i+1]='o';
                str[i+2]='-';
            }
            //�ж�i,i-1����'o' i-2����'-'
            if(i>=3 && str[i-1] == 'o' && str[i-2] == '-'){
                str[i]=str[i-1]='-';//i��i-1��Ϊ'-',i-2��Ϊ'o'
                str[i-2]='o';
                dfs(calState());
                str[i]=str[i-1]='o';
                str[i-2]='-';
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    while(n--){
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        ans=strlen(str+1);
        dfs(calState());
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms ���仯����
//dp[cur]��ʾ��cur״̬(����cur)���ܱ仯ת�Ƶ�����״̬��'o'���ٵĸ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
using namespace std;

int n,dp[1<<12];
char str[N];

int calInitState(){
    int sta=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            sta|=1<<i-1;
    }
    return sta;
}

int calNum(int sta){
    int cnt=0;
    while(sta){
        if(sta & 1)
            cnt++;
        sta>>=1;
    }
    return cnt;
}

int dfs(int cur){
    if(dp[cur]!=-1)
        return dp[cur];
    dp[cur]=calNum(cur);
    int sta;
    for(int i=1;i<=12;i++){
        //�ж�i,i+1����'o' i+2����'-'
        if(i<=10 && (cur & 1<<i-1) && (cur & 1<<i) && !(cur & 1<<i+1)){
        	int sta=cur;
            sta^=1<<i-1;//i��i+1��Ϊ'-',i+2��Ϊ'o'
            sta^=1<<i;
            sta|=1<<i+1;
            dp[cur]=min(dp[cur],dfs(sta));
        }
        //�ж�i,i-1����'o' i-2����'-'
        if(i>=3 && (cur & 1<<i-1) && (cur & 1<<i-2) && !(cur & 1<<i-3)){
        	int sta=cur;
            sta^=1<<i-1;//i��i-1��Ϊ'-',i-2��Ϊ'o'
            sta^=1<<i-2;
            sta|=1<<i-3;
            dp[cur]=min(dp[cur],dfs(sta));//���ݺ�ԭ
        }
    }
    return dp[cur];
}

int main(){
    scanf("%d",&n);
    while(n--){
    	memset(dp,-1,sizeof(dp));
        scanf("%s",str+1);
        printf("%d\n",dfs(calInitState()));
    }
    return 0;
}
*/

/*
//ac 0ms ���仯���� λ�������״̬����
//dp[cur]=1/0 ����ǰ�����϶���ʯ�Ķ�����λ��״̬֮ǰ�Ƿ�õ���,1�����Ѿ����ֹ�,0����δ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 13
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[1<<12],ans;
char str[N];

int calInitState(){
    int sta=0;
    for(int i=1;i<=12;i++){
        if(str[i] == 'o')
            sta|=1<<i-1;
    }
    return sta;
}

int calNum(int sta){
    int cnt=0;
    while(sta){
        if(sta & 1)
            cnt++;
        sta>>=1;
    }
    return cnt;
}

void dfs(int cur){
    if(dp[cur])
        return;
    dp[cur]=1;
    ans=min(ans,calNum(cur));
    for(int i=1;i<=12;i++){
        //�ж�i,i+1����'o' i+2����'-'
        if(i<=10 && (cur & 1<<i-1) && (cur & 1<<i) && !(cur & 1<<i+1)){
            cur^=1<<i-1;//i��i+1��Ϊ'-',i+2��Ϊ'o'
            cur^=1<<i;
            cur|=1<<i+1;
            dfs(cur);
            cur|=1<<i-1;//���ݺ�ԭ
            cur|=1<<i;
            cur^=1<<i+1;
        }
        //�ж�i,i-1����'o' i-2����'-'
        if(i>=3 && (cur & 1<<i-1) && (cur & 1<<i-2) && !(cur & 1<<i-3)){
            cur^=1<<i-1;//i��i-1��Ϊ'-',i-2��Ϊ'o'
            cur^=1<<i-2;
            cur|=1<<i-3;
            dfs(cur);//���ݺ�ԭ
            cur|=1<<i-1;
            cur|=1<<i-2;
            cur^=1<<i-3;
        }
    }
}

int main(){
    scanf("%d",&n);
    while(n--){
        memset(dp,0,sizeof(dp));
        scanf("%s",str+1);
        ans=strlen(str+1);
        dfs(calInitState());
        printf("%d\n",ans);
    }
    return 0;
}
*/
