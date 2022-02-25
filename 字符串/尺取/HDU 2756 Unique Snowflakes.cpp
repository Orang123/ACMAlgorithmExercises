/*
����:ժ������
�������ɸ�����������Ĳ�ͬ���ݵĳ��� ��
����:http://acm.hdu.edu.cn/showproblem.php?pid=2756
˼·:��ȡ.��ָ���ƶ������ǵ���ǰ[l,r-1]�Ӵ��в�����a[r]������,
��a[r]�Ѿ�������[l,r-1]��ʱֹͣ,��¼��ǰ�Ӵ��ĳ���,֮����ָ��
ɾ������߳��ֵ�,ֱ��ɾ����ǰa[r]��Ԫ�غ�,��ָ������¿�ʼ����
�����µ�a[r]Ԫ��,���ж���Ĳ�ͬ���ݵ��Ӵ�����.
*/
//ac 592ms
//�������� if(!s.count(a[r])) break;
#include<cstdio>
#include<cstring>
#include<set>
#define N 1000010
using namespace std;

int n,a[N],ans;
set<int> s;

int main(){
    int T,l,r;
    while(scanf("%d",&T)!=EOF){
        while(T--){
            s.clear();
            scanf("%d",&n);
            for(int i=1;i<=n;i++)
                scanf("%d",&a[i]);
            ans=l=r=1;
            while(1){
                while(r<=n && !s.count(a[r]))
                    s.insert(a[r++]);
                if(!s.count(a[r]))
                    break;
                //ʵ�ʵ�r����ʱ,l���� ����ֻ��Խ��ԽС,l����������Ϊ��ɾ���Ӵ������е�a[r],������ָ������
                ans=max(ans,r-l);
                s.erase(a[l++]);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}

/*
//ac 577ms
//�������� �����ѭ��r<=n
#include<cstdio>
#include<cstring>
#include<set>
#define N 1000010
using namespace std;

int n,a[N],ans;
set<int> s;

int main(){
    int T,l,r;
    while(scanf("%d",&T)!=EOF){
        while(T--){
            s.clear();
            scanf("%d",&n);
            for(int i=1;i<=n;i++)
                scanf("%d",&a[i]);
            ans=l=r=1;
            while(r<=n){
                while(r<=n && !s.count(a[r]))
                    s.insert(a[r++]);
                ans=max(ans,r-l);
                s.erase(a[l++]);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
*/
