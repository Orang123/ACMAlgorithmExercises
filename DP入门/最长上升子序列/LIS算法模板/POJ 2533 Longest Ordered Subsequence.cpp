/*
LIS(Longest Increasing Subsequence)�����������,����½�������.
����:N��������һ���ϸ񵥵����������е���󳤶�
����:http://poj.org/problem?id=2533
˼·:�ɲ���O(N^2)��dp������O(NlogN)�Ķ��ֵ�������(LIS)��������,
����LIS�޷���¼������·����
�����Ż��ɲο�����:https://www.cnblogs.com/itlqs/p/5743114.html
�������dp����.
*/
//ac 15ms
//dp[i]��ʾ�Ե�i������β�ĵ������������е���󳤶�,�����ǳ���Ϊi����ЩԪ������������������е���󳤶�
//�ϸ�������ⵥ�����������������������,״̬��ת������֮ǰ�ĵ�������������ת�Ƶ������ĵ���������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[1100],dp[1100];

int main(){
    int n,ans=1;//����һ��Ҫ���ó�1,���򵱳���Ϊ1ʱ,�������Ϊ���µ�ans�ĳ�ʼֵ,������Ϊ1
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dp[1]=1;//��ʼֵ����Ԫ�ع���һ����������
    for(int i=2;i<=n;i++){
        /*
        ���Ԫ���п�������С��,���䱾��Ҳ�ǳ���Ϊ1������������,���ﲻ�ܼ̳�dp[i-1]��ֵ,
        ��Ϊ��a[i]��������С��,���̳���dp[i-1],�¸�Ԫ��a[i+1],���ڵ�ǰ��a[i]ʱ,dp[i+1]=dp[i]+1,
        �п���a[i+1]ֻ����a[i],����a[i]ǰ���Ԫ�ض�С����,ʵ��a[i+1]ֻ����a[i],a[i+1]=2�Ŷ�.
        */
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);//ans��¼�����������������е���󳤶�,dp[i+1]��һ������dp[i]
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 16ms O(n^2) ����
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100];

int main(){
    int n,ans=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 16ms �ݹ���仯����д��O(N^2)
//�ص���������,���ڲ�ͬ��a[i]��a[j](j<i)�Ƚ�ʱ,dp[j]���ظ�������,�����Ҫ�������������ظ�����.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100],ans=1;

int dfs(int i){
    if(dp[i])
		return dp[i];
	dp[i]=1;
    for(int j=1;j<i;j++){
        //����һ��Ҫ��dfs(j),��Ϊa[i]������ǰi��������С��,
        //д��dp[i]=max(dp[i],dfs(j)+1),���ܾͽ��벻�����if����,����wa
    	dfs(j);
        if(a[i]>a[j])
            dp[i]=max(dp[i],dp[j]+1);
    }
    ans=max(ans,dp[i]);
    return dp[i];
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
		dp[i]=0;
	}
    dfs(n);
    printf("%d",ans);
    return 0;
}
*/

/*
//TLE ����dfs,����¼�ص�������.
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100],ans=1;

int dfs(int i){
	int res=1;
    for(int j=1;j<i;j++){
    	dfs(j);
        if(a[i]>a[j])
            res=max(res,dfs(j)+1);
    }
    ans=max(ans,res);
    return res;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
		dp[i]=0;
	}
    dfs(n);
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 0ms �������ж����Ż�
//��ϸ񵥵�������������
//ά��һ�������Ķ���(LIS)
//�µ�Ԫ�أ�������ڶ�βԪ�أ��������β
//������ֲ��ұ��������СԪ�أ��滻��
//�����г��ȼ�ΪLIS�Ľ�
//�������ժ�Բ���:https://www.cnblogs.com/frankchenfu/p/7107019.html
//����ÿ����һ����ջ��Ԫ�ش�������ͷŽ�ջ�������ջ��Ԫ��С�ľͶ��ֲ���ǰ�ߵ�Ԫ�أ�
//�ҵ�һ������Ӧ�ñ�������Ԫ�ء���������ȥ����ǰ�ߵ�Ԫ�ء����Ԫ�ؿ��ܲ������Ž��һ���֣�
//����������ʹ�ú��滹δ����ġ��Ƚ�С�������п��ܽ���������С�ͨ�׵���˵����Ϊ�ż���
//������Ҫ���ڵ�ǰ���е����һ�������ܼӽ�ȥ�����������̫���ˣ��Ҿ͹ԹԴ���ĩβ�����
//ǰ����һ�������Ҵ�Ҳ�����ұ���ã���Ȼ���������Ҳ������������ֻ��ѡ��һ������ֻ��
//�����滻���ˡ���Ȼ������ʱ��ͷ���Ĳ�һ������ʣ����Ƕ��ں��滹�кܶ���˵����Ž�����
//����£��Ҹ����Ǵ����˸�����ᣬʹ��������е����һ�����п��ܱ�С���ø�����˽�����
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

//b����Ϊ������������
int a[1100],b[1100];

void erfen(int l,int r,int val){
    int mid;
    while(l<r){
        mid=(l+r)/2;
        if(val>b[mid]) l=mid+1;//���������val>=b[mid] 1 2 3 2 3 2 �������ݻ����4,ʵ�ʽ��Ӧ��3
        else r=mid;
    }
    b[l]=val;
}

int main(){
    int n,k=2;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    b[1]=a[1];//��һ��Ԫ��Ҫ�ȷŽ�ȥ
    for(int i=2;i<=n;i++){//���Ӷ� O(NlogN) �ӵڶ���Ԫ�ؿ�ʼ�������
        //��a[i]�ȵ��������������ĩ���ֵ����ʱ ���
        if(a[i]>b[k-1]) b[k++]=a[i];//����½�������������a[i]>=b[k-1]
        //��a[i]���ֵʱ,���ֲ��Ҷ����е�һ������a[i]����,��a[i]�滻��,����������Ӱ������������е�kֵ��С
        //��:һ��ʼ����2��Ԫ�� 1 4 i=3ʱa[3]=2,��ʱ����������л���2,���罫2�����ĩ,
        //1 4 2 i=4ʱ,a[4]=5ʱ,{1 4 5}{1 2 5}2���������������г��ȶ���3,
        //����һ��ʼa[3]С��4ʱ,ֱ�ӽ�4��ֵ�滻Ϊa[2]���յĶ���Ϊ1 2 5,
        //����Ϊ3,����˵����������ǡ����ʹ�ö��еĳ��Ⱦ�������������еĳ���.
        //https://www.cnblogs.com/itlqs/p/5743114.html �ο�����
        //׼ȷ��˵�������ǽ���˭���档�����滻��˭����Ϊ������ǰ���˭���涼��û������ģ�
        //�ٽ�Ҳ���������len���������滻�����ˡ���ô�滻��˭�أ������滻���Ǹ���ñ����滻���Ǹ���
        //Ҳ������d�����е�һ���������ġ���һ����ζ��ǰ��Ķ�С�ڵ������������һ������������b[j]��
        //˵��b[1..j-1]��С�ڵ���������ô����ȫ���Խ���b[j-1]Ȼ������һ������Ϊj�Ĳ��½������У�
        //������������бȵ�ǰ��d[j]��������и���Ǳ������Ϊ�������d[j]С����
        //�Ծ��滻���������ˣ�Ҳ����b[j]=a[i]����ʵ���λ��Ҳ����Ψһ�ܹ��滻��λ��
        //��ǰ������˲�����b[k]��Сֵ�Ķ��壬�����滻�˲������������У�.
        else
            erfen(1,k-1,a[i]);
    }
    printf("%d",k-1);
    return 0;
}
*/

/*
//ac 0ms �������� ʹ��lower_bound stl��������
//��ϸ񵥵�������������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],b[1100];

int main(){
    int n,k=2,pos;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    b[1]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]>b[k-1]) b[k++]=a[i];//����½�������������a[i]>=b[k-1]
        else{
        //lower_bound()���ֺ����ķ���ֵΪһ��ָ�򵥵�����[first, last) �е�һ����С��(���ڵ���)val��Ԫ�صĵ�ַ ��Ӧ�ϸ����������� �ϸ����
        //upper_bound()���ֺ������ص��ǵ��������е�һ������val��Ԫ�صĵ�ַ ��Ӧ���½�������,���Դ��ڵ���,���ϸ��
            pos=lower_bound(b+1,b+k,a[i])-b;//�ڶ���������b+1+k-1=b+k
            b[pos]=a[i];
        }
    }
    printf("%d",k-1);
    return 0;
}
*/

/*
//ac 16ms �������� ʹ��lower_bound stl��������
//lower_bound b�����±��0��ʼ,Ϊ�˷���ͳ��ĩβ�Ϸ�λ��b�����ʼ��ΪINF
//��ϸ񵥵�������������
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxn=1005;
const int INF=0x3f3f3f3f;
int n,res,x,dp[maxn];
int main(){
    while(~scanf("%d",&n)){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;++i){
            scanf("%d",&x);
            *lower_bound(dp,dp+n,x)=x;//������С����
        }
        printf("%d\n",lower_bound(dp,dp+n,INF)-dp);
    }
    return 0;
}
*/
