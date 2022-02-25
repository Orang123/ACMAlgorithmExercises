#include<cstdio>
#include<stack>
#include<algorithm>
#define N 52
using namespace std;
int n,cnt;
int de[N];
stack<int> s;
int map[N][N];

int convert1(char c){//��A~Z a~z ӳ���0~25 26~51
    if(c>='A' && c<='Z')
        return c-'A';
    else
        return c-'a'+26;
}

int convert2(int c){//��0~25 26~51ת����A~Z a~z ʮ����
    if(c>=0 && c<=25)
        return c+'A';
    else
        return c+'a'-26;
}

void dfs(int u){
    for(int i=0;i<N;i++){
        if(map[u][i]){
            map[u][i]=map[i][u]=0;
            dfs(i);
        }
    }
    s.push(u);
}

int main(){
    char a[2];
    int u,v;
    scanf("%d",&n);
    while(n--){
        scanf("%s",a);
        u=convert1(a[0]);
        v=convert1(a[1]);
        map[u][v]=map[v][u]=1;
        de[u]++;
        de[v]++;
    }
    int cnt=0,S1,S2;
    for(int i=51;i>=0;i--){
        if(de[i]&1){
            cnt++;
            S1=i;//��¼��С�����
        }
        else if(de[i])//��¼��С��ż��
            S2=i;
    }
    if(cnt>2){
        printf("No Solution");
        return 0;
    }
    else if(cnt==2)
        dfs(S1);
    else if(cnt==0)
        dfs(S2);
    int t;
    while(!s.empty()){
        t=s.top();
        s.pop();
        printf("%c",convert2(t));
    }
    return 0;
}
