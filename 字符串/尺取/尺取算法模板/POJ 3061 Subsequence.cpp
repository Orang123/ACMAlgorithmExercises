/*
����:
������һ����N�������� (10<N<100000)��ɵ����У�
ÿ����С�ڻ����10000��������һ��������S(S< 100000000)��
��дһ�������������������Ԫ��֮�ʹ��ڻ����S�������е���С���ȡ�
����:http://poj.org/problem?id=3061
˼·:��ȡ.���Ӷ�O(n).ֱ�ӱ���ö��ÿ����㿪ʼ����ʱ�临�Ӷ�O(n^2).
*/
//ac 79ms
//r��ʾ�ұ߼����˼�����,l��ʾ������߼�ȥ�˼�����
#include<cstdio>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,s,a[N],sum,ans;

int main(){
    int T,l,r;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sum=l=r=0;
        ans=INF;
        while(1){
            //ÿ������r������,����sum<s������ſ�ʼ�ۼ��ұߵ�
            while(r<n && sum<s)//O(n)
                sum+=a[++r];
            if(sum<s)
                break;
            //r��ʾ�����ֶε��ұ߽� l+1�������Ӷε���߽� �ֶ�Ԫ�ظ���r-(l+1)+1=r-l
            //���ʵ�ʳ��Ⱦ�Ϊr-l
            ans=min(ans,r-l);
            //l�����ܳ���r,������
            sum-=a[++l];//ÿ�μ�ȥһ��l,sum�����Ȼ>=s,������ȥa[++l]. ʱ�临�Ӷ���������n�� �Ǹ�����
        }
        if(ans!=INF)
            printf("%d\n",ans);
        else//ans == INF ˵�����е���֮�Ͷ���sС,��˳���Ϊ0,û�������������Ӵ�(����������)
            printf("0\n");
    }
    return 0;
}

/*
//ac 79ms
//�±��0��ʼ ��++
//����ָ���һ��ѭ��
//l,r����ָ�����ʾ�±�
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,len,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=0,r=0,num=INF,len=0;
        while(r<n){
            while(r<n&&sum<s){
                sum+=a[r++];
            }
            while(sum>=s){
                sum-=a[l++];
            }
            //��Ϊr,l��������1,����ֱ�ӵ�����,ʵ�ʳ��Ⱦ�Ϊr-l+1(+1����Ϊ�±�֮���ʵ�ʳ�����1)
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 79ms ˫ָ��,if(sum<s) break;������ѭ��
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,len,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=0,r=0,num=INF,len=0;
        while(1){
            while(r<n&&sum<s)
                sum+=a[r++];
            if(sum<s)
            	break;
            while(sum>=s)
                sum-=a[l++];
            //��Ϊr,l��������1,����ֱ�ӵ�����,ʵ�ʳ��Ⱦ�Ϊr-l+1(+1����Ϊ�±�֮���ʵ�ʳ�����1)
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 79ms
//�±��0��ʼ ��++
//����ָ���һ��ѭ��
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,len,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=0;i<n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=-1,r=-1,num=INF,len=0;
        while(r<n-1){
            while(r<n-1&&sum<s){
                sum+=a[++r];
            }
            while(sum>=s){
                sum-=a[++l];
            }
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 79ms
//�±��1��ʼ ��++
//����ָ���һ��ѭ��
#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int a[100001];
int main(){
    int k,n,s,sum,l,r,num,total;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&n,&s);
        total=0;
        for(int i=1;i<=n;i++){
            scanf("%d",a+i);
            total+=a[i];
        }
        if(total<s){
            printf("0\n");
            continue;
        }
        sum=0,l=0,r=0,num=INF;
        while(r<n){
            while(r<n&&sum<s)
                sum+=a[++r];
            while(sum>=s)
                sum-=a[++l];
            //l�Ǽ�ȥ���±�Ϊl������ sum<s��,��ôʵ����ߵ��±����l,��˳���r-l+1
            num=min(num,r-l+1);
        }
        printf("%d\n",num);
    }
    return 0;
}
*/

/*
//ac 860ms
//ժ�Բ���:https://tigerisland.blog.csdn.net/article/details/73699161
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000;
int prefixsum[N+1];

int main()
{
    int t, n, s, val, ans;

    cin >> t;
    while(t--) {
        cin >> n >> s;

        // �������ݣ�����ǰ׺��
        prefixsum[0] = 0;
        for(int i=1; i<=n; i++) {
            cin >> val;

            prefixsum[i] = prefixsum[i - 1] + val;
        }

        if(prefixsum[n] < s)
            ans = 0;
        else {
            ans = n;
            for(int i=0; prefixsum[i] + s < prefixsum[n]; i++) {
                int pos = lower_bound(prefixsum + i, prefixsum + n, prefixsum[i] + s) - prefixsum;
                ans = min(ans, pos - i);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
*/
