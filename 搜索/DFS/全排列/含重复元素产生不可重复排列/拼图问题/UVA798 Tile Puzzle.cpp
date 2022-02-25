/*
����:ժ������
����w*h�ľ��κ�n��ƴͼ(����)��������n��ƴͼ�ĸ���num[i]����w[i]����h[i]��
��˵����Щƴͼ�����ö����ֲ�ͬ�ķ���ƴ�ճ�w*h�ľ��Ρ�ÿ�����ο��Ժ�Ż�����.
w,h<100.n<=10.
����Ӧ���ܱ�֤�������һ���Ž�.
����:https://www.luogu.com.cn/problem/UVA798
˼·:ö��ÿһ��λ��(x,y)�����ܷ��õĿ��������ƴͼ.
*/
//ac 700ms dfs����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 110
using namespace std;

int n,sumW,sumH,num[N],w[N],h[N],mp[M][M],ans;

//��(x,y)������һ����͸�Ϊ(th,tw)��ƴͼ,ע����Ϊ(x,y)�����ռ��һ����λ�Ŀ�͸� ����ö�ٵ������Ͻ��� th-1��tw-1
int check(int x,int y,int th,int tw){
    if(x+th-1>sumH || y+tw-1>sumW)//ע�����ֻ�ܼ�th-1,tw-1,��Ϊ(x,y)λ�ñ�����ռ��һ����λ�Ŀ�͸�
        return 0;
    for(int i=0;i<th;i++){
        for(int j=0;j<tw;j++){
            if(mp[x+i][y+j])//��ǰ
                return 0;
        }
    }
    return 1;
}

void update(int x,int y,int th,int tw,int val){
    for(int i=0;i<th;i++){
        for(int j=0;j<tw;j++){
            mp[x+i][y+j]=val;
        }
    }
}

void dfs(int x,int y){
    if(y == sumW+1){//��ǰ������,��ʼɨ����һ�е�һ��
        x++;
        y=1;
    }
    if(x == sumH+1){//w*h�ľ����Ѿ�����
        ans++;
        return;
    }
    if(!mp[x][y]){//(x,y)λ��δ��ռ��
        for(int i=1;i<=n;i++){
            if(num[i] && check(x,y,h[i],w[i])){//���
                num[i]--;
                update(x,y,h[i],w[i],1);
                dfs(x,y+1);//��һ��λ��֮���Դ�(x,y+1)��ʼ ����Ϊ�����ռ�ݵ�λ�ò�ȷ��,������©����λ��,����һ����Ԫһ����Ԫɨ���ж�
                update(x,y,h[i],w[i],0);
                num[i]++;
            }
            if(num[i] && w[i]!=h[i] && check(x,y,w[i],h[i])){//����ƴͼ ��߲�ͬʱ,����Ҳ������һ�ַ���.
                num[i]--;
                update(x,y,w[i],h[i],1);
                dfs(x,y+1);
                update(x,y,w[i],h[i],0);
                num[i]++;
            }
        }
    }
    else
        dfs(x,y+1);//(x,y)λ���Ѿ������ƴͼռ��,ɨ����һ��λ��(x,y+1)
}

int main(){
    while(scanf("%d%d%d",&sumW,&sumH,&n)!=EOF){//����Ŀ����ʵ�ߵ� Ҳ����Ӱ���
        ans=0;
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&num[i],&w[i],&h[i]);
        dfs(1,1);
        printf("%d\n",ans);
    }
    return 0;
}
