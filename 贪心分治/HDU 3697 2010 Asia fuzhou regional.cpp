#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
̰��+����
����:��n�ſγ�(n<=300),ÿ�ſγ��и�ѡ�ε�ʱ���s,e,ֻ����s֮����e֮ǰѡ����ſγ̡�
ÿλͬѧ����ѡ������һ����ʼʱ�䣬Ȼ��ÿ5������һ��ѡ�λ��ᣬ��ÿλͬѧ������ѡ�����ſΡ�
��Ϊѡ����ĳ��ʱ����,ֻ�ܰ���ʱ������5min��ѡ ����ֻ��ѡһ��,���Բ���������ѡ�ĸ���ѡ�ĸ�������ŵ�˼ά,
�����ų���������.
*/
int n,vis[310];
struct Course{
    int st,ed;
    bool operator <(const Course &x)const{
        if(ed!=x.ed) return ed<x.ed;//������ʱ���Ƿ��������
        else return st<x.st;
    }
}cors[310];

int main(){
    while(scanf("%d",&n) && n){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&cors[i].st,&cors[i].ed);
        sort(cors+1,cors+1+n);
        int cnt,ans=-1;
        for(int i=0;i<5;i++){//iȡֵ0~4 ��ʵ��5��ȡֵ���� 0~1��1~2��2~3��3~4��4~5 ��Ϊʱ������5Ϊ��λǰ��������5�����俪ʼ����ʱ����ǵ�Ч��,��Ϊ��֪����һ��
            cnt=0;
            memset(vis,0,sizeof(vis));
            for(int k=i;k<cors[n].ed;k+=5){
                for(int j=1;j<=n;j++){
                    if(!vis[j] && k>=cors[j].st && k<cors[j].ed){//k>=cors[j].st����k��cors[j].st��cors[j].st+1֮��
                        vis[j]=1;
                        cnt++;
                        break;//һ��ʱ���ֻ��ѡ��һ�ſγ� ʱ��k+=5 �ٴ��ж��Ƿ��пγ��������
                    }
                }
            }
            ans=max(ans,cnt);
        }
        printf("%d\n",ans);
    }
    return 0;
}
