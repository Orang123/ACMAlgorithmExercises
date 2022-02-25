/*
����:�������죬�ϱ������ɻ𳵣��˸տ�ʼ������ߣ�
ÿһ�غ��˿���������һ��Ȼ��ѡ�����ơ����ƻ򲻶���
Ȼ�����л𳵻�����ƽ��2�������Ƿ���ܰ�ȫ�������ұ�
����:https://codeforces.ml/contest/586/problem/D
˼·:��������1λ,��������2λ,��������˶�,��ôʵ���൱���������ƶ���3λ,
ֻ����������ʱ����Ҫ����ԭ��λ�õ��ұ�1λ�Ƿ����ƶ�,��Ϊ���������ƶ�֮ǰ��Ҫ����һλ,
�������жϵ�ʱ���ǰ�����������������ĺ���λ�жϵ�,��������֮ǰ���Ƿ��������ƶ�����һλ,
���ԭ�ȶ��޷�����һλ,��Ҳ�޷������ƶ�2λ,��Ȼ��û������˶�3��֮˵.
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n,k,vis[4][110],flag;
char mp[4][110];

int dfs(int x,int y){
    if(y>n) return 1;
    if(mp[x][y+1]!='.') return 0;//�������Ƿ��������ƶ����ҵ���һ��,�������.
    vis[x][y]=1;
    for(int i=-1;i<=1;i++){
        if(x+i<1 || x+i>3) continue;
        int flag=0;
        for(int j=1;j<=3;j++){//����������ƶ����ܺͻ���ײ
            if(mp[x+i][y+j] != '.'){
                flag=1;
                break;
            }
        }
        if(vis[x+i][y+3]) continue;//�߹���״̬�����ظ���
        if(!flag){
            if(dfs(x+i,y+3)) return 1;
        }
    }
    return 0;
}

int main(){
    int x,y,T;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=3;i++){
            for(int j=1;j<=n;j++){
                cin >> mp[i][j];
                if(mp[i][j] == 's') x=i,y=j;
            }
            for(int h=1;h<=3;h++)//�п����ƶ��ᳬ��ԭ��������еķ�Χ
                mp[i][n+h]='.';
        }
        if(dfs(x,y))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
