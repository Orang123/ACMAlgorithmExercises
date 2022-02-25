/*
����:��һ������n,��Χ��1~2^63-1����1~n֮�京��49�������ж��ٸ���
ע��:"49"�������������Ӵ�.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3555
˼·:ֱ�ӱ����ж�ÿһλ����,n���10^18,1s�϶���TLE.
������λdp.
������2�����ͽ��ıȽ���ϸ.
https://blog.csdn.net/qq_34374664/article/details/52917231
https://www.cnblogs.com/liuxueyang/archive/2013/04/14/3020032.html
*/
//ac 15ms ���仯����
//dp[k][pre]��ʾn����λ��k��ĩβ(�������������λ�±�)�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ��������"49"�����ִ��ĸ���
//pre == 0��ʾ��һλ����4
//pre == 1��ʾ��һλ��4
//pre == 2��ʾ��ͷ���±�Ϊk�Ĵ��г��ֹ�������"49"�Ӵ�
//�ռ临�Ӷ�O(20*3)=60
//ʱ�临�Ӷ�O(10*20*3)=600
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20//2^63-1 ��Ӧ10^18 �����19λ�� long long ��ʾ
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][3];

ll dfs(int k,int pre,int limit){
    if(!k)//������λ������ȷ��,pre == 2��˵�������� "49"��,����1 ��ʾһ���Ϸ������ִ�
        return pre == 2;
    /*
    ���ڵ�limit=0�����,��λ����ֵ��ȡ������9ȥ�ۼӵ�,������limit==1��ʱ��,
    ���λ�Ѿ�ȡ�ö���������,�����λ�Ͳ���ȡ��n����λ���������,�����ͳ���n��,
    �����仯dp[k][pre]�������limit=0��ʱ��,���Ǻ����λ�������п��ܳ���n,
    ��λֻ��ȡ�����λ����ֵ,ֱ�Ӽ��仯����֮ǰlimit=0����� ��ʹ���ƫ��
    ����Ҫ�жϣ���Ȼ�ʹ��ˡ�
    */
    //����ļ��仯ֻ��limit == 0���������λ�������¼,��Ϊ���������λ���ǰ����ȡ9�����,������dfsҲ��������֮ǰ��¼��dpֵ
    if(!limit && dp[k][pre]!=-1)//�豣֤limit=0 ��ǰ���λ����ȡ�ò�������� �������Ϊ���ܰ���ȡ�����ֵ9����
        return dp[k][pre];
    //limit == 1 ��ǰλ��ֻ��ȡ��a[k](ԭʼn��ǰλ����ֵ),����ᳬ��n,
    //limit == 0 ǰ��λû�а����ȡ,�ǵ�ǰλ�Ϳ���ȡ�����λ9,����Ҳ���ᳬ��n
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){//��С��0��ʼȡ,����ǰ��0
        //��һλ����4 �� ��һλ��4 ��ǰλ��ȡ9,������������ǲ���"49"��������,
        //��������pre��ȡֵ �����ǰλ i == 4,��ôȡ1,����ȡ0,
        //limit��ֵ ֻ�е�����Ϊ1,�ҵ�ǰλȡ���ֵlast limit����1,���඼��0(��:ǰ��λ��û��ȡ�����)
        if(pre == 0 || (pre ==1 && i != 9))
            ans+=dfs(k-1,i == 4,limit && i == last);//�Ӹ�λ���λ����,�������ܱ�֤��������λ������n
        //������2�����,��ʾ��λ���Ѿ�����"49",����pre ҪΪ2
        //1.pre == 1 && i ==9 ��:��һ�γ���"49"��
        //2.pre == 2,ǰ����λ�Ѿ����ֹ�"49"��
        else
            ans+=dfs(k-1,2,limit && i == last);
    }
    //����ʵ�ʶ���limit ==1�����,��Զ��ֻ���������һ��,ʵ�ʲ�������ж�Ҳ�ǲ���Ӱ������.
    //����ж��dfs,��dp����ֻ��ʼ��һ��,�����dfs���õ�ǰ���dp��ֵ,�����һ��Ҫ����!limit��Ȼ������
    //��Ϊ���λ�����last��ֵȡ���ڵ�ǰa[k],��ÿ�ε�a[k]�����ǲ�ͬ��
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));//dp�����������ֻ�ó�ʼ��һ��,�����dfs��ǰ���dpֵͬ���ظ�ʹ��
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        while(n){
            a[++len]=n%10;
            n/=10;
        }
        //�Ӹ�λ���λ����,�������ܱ�֤��������λ������n
        printf("%lld\n",dfs(len,0,1));
    }
    return 0;
}

/*
//ac 15ms ���仯���� dp��ά����,����limit
//dp[k][pre][limit]��ʾn����λ��k��ĩβ(�������������λ�±�)�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ��Ҹ�λ״̬Ϊlimitʱ�������"49"�����ִ��ĸ���
//limit == 0 ��ʾ��λ���������,����λ���������ȡ��9
//limit == 1 ��ʾ��λ�����,��ǰλ���ֻ��ȡa[k].
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20//2^63-1 ��Ӧ10^18 �����19λ�� long long ��ʾ
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][3][2];

ll dfs(int k,int pre,int limit){
    if(!k)
        return pre == 2;
    if(!limit && dp[k][pre][limit]!=-1)//���������仯ֻ��limit ==0�ж�,���򲻼�limit ÿ�ζ�Ҫ��ʼ��dpֵ
        return dp[k][pre][limit];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
        if(pre == 0 || (pre ==1 && i != 9))
            ans+=dfs(k-1,i == 4,limit && i == last);
        else
            ans+=dfs(k-1,2,limit && i == last);
    }
    dp[k][pre][limit]=ans;
    return ans;
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        while(n){
            a[++len]=n%10;
            n/=10;
        }
        //�Ӹ�λ���λ����,�������ܱ�֤��������λ������n
        printf("%lld\n",dfs(len,0,1));
    }
    return 0;
}
*/

/*
//ac 15ms ���仯����
//dp[k][pre]��ʾn����λ��k��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ����㲻����"49"�����ִ��ĸ���
//pre == 0��ʾ��һλ����4
//pre == 1��ʾ��һλ��4
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][2];

ll dfs(int k,int pre,int limit){
    if(!k)//������λ��ȡֵ����,����һ������"49"����,����1
        return 1;
    if(!limit && dp[k][pre]!=-1)
        return dp[k][pre];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
    	if(pre == 1 && i == 9)//��һλ��4,��ǰλ��9 ��������
    		continue;
    	ans+=dfs(k-1,i == 4,limit && i == last);
    }
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int main(){
    int T;
    ll tp;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        tp=n;
        while(tp){
            a[++len]=tp%10;
            tp/=10;
        }
        //��Ϊdfs��������lenλȫ0�����,�����ֵΪ0,��ʵ��Ҫͳ�Ƶ���ֵ��1~n֮��,���Զ����һ��"0",Ҫ�ټ���1
        printf("%lld\n",n-dfs(len,0,1)+1);
    }
    return 0;
}
*/

/*
//ac 15ms ���仯���� ten�������dfs
//ten[i]��ʾ10^i
//dp[k][pre]��ʾn����λ��k��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn�����ִ��������"49"�����ִ��ĸ���
//pre == 0��ʾ��һλ����4
//pre == 1��ʾ��һλ��4
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][2],ten[N];

ll dfs(int k,int pre,int limit){
    if(!k)//����λȡ��,Ҳû�г���"49"�Ĵ����,����0
        return 0;
    if(!limit && dp[k][pre]!=-1)
        return dp[k][pre];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
    	if(pre == 1 && i == 9)
    		//�Ѿ�����49
			//1.limit == 1 ֮ǰ��λ��ȡ�������λ,�����λ���ܳ���n�����ԭʼ��λ,
			//����������ִ��ĸ�������n���±�k-1~1λ��ʾ������,��ten[k-1]ȡģ�ɵõ�
			//���ǲ�������k-1~iλȫ��ȡ0�����,����Ҫ�ټ�1.
			//2.limit == 0 ֮ǰ��λ����Ͳ������,��k-1~1λ����󶼿���ȡ9,�Ǿ�������λ����9+ ����λ����0,����Ϊten[k-1] 10^(k-1)
    		ans+=limit?n%ten[k-1]+1:ten[k-1];
    	else
    		ans+=dfs(k-1,i == 4,limit && i == last);
    }
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int main(){
    int T;
    ll tp;
    ten[0]=1;
    for(int i=1;i<=18;i++)
    	ten[i]=ten[i-1]*10;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        tp=n;
        while(tp){
            a[++len]=tp%10;
            tp/=10;
        }
        printf("%lld\n",dfs(len,0,1));
    }
    return 0;
}
*/

/*
//ac 15ms �������
#include<cstdio>
#include<algorithm>
#define N 20
using namespace std;
typedef long long ll;

int a[N];
ll n,dp[N][3],ans;

int main(){
    int T;
    scanf("%d",&T);
    //����dpʱ��iλ�Ǵ��������1��ʼ�����
    //dp[i][0]������Ϊ i ���Ҳ�����49�����ֵĸ�����
����//dp[i][1]������Ϊ i ���Ҳ�����49���������λ��9�����ֵĸ�����
����//dp[i][2]������Ϊ i ���Һ���49�����ֵĸ�����
	//ע��dp[i][0]�ǰ���dp[i][1]��,dp[i][0]Ҳ���� ����49���������λ��9�����ִ�
    dp[0][0]=1,dp[0][1]=dp[0][2]=0;//��ʼ״̬
    for(int i=1;i<21;i++){
    	//���ݳ˷�ԭ��,����49 dp[i][0]����һλdp[i-1][0]������ ��iλ����ȡ0~9,��ʮλ����,���ڷ�ǰ��0�� ʵ�ʱ�ʾ�ľ���dp[i-1][0]����Ϊi-1���ⲿ��ֱ�Ӽ̳�
		//���Ƕ��ڵ�i-1λΪ9Ҳ����dp[i-1][1],��iλȡ4ʱ,������49xxxx,Ҫ��ȥ��һ�����
        dp[i][0]=10*dp[i-1][0]-dp[i-1][1];
        //dp[i][1]������ǰi-1λ����49�����,���ڵ�iλ����9
        dp[i][1]=dp[i-1][0];
        //��49�ľ�����ǰi-1λ��49�Ļ�����,��iλ���Է�0~9 ��10λ����, ��������ǰi-1λ����49�����λΪ9,�ڵ�iλ����4,Ҳ���Թ����µĺ�49��
        dp[i][2]=10*dp[i-1][2]+dp[i-1][1];//dp[1][2]����dp[0][2] dp[0][1]���Ϊ0
    }
    while(T--){
       scanf("%lld",&n);
       int len=0;
       //����ΪʲôҪ������ n ��Ҫ�� n ��1������һ����������������49������������������ڵ�3����������ѷ������������ּ��ϣ�
	   //��Ϊ4�����ϸ����4������ִ�н������0�������������1֮��n�ͱ����50��������3��ǡ�ÿ���ִ�У����������ȷ���ˡ�
	   //���Ƕ���һ�����������ǲ�֪��ΪʲôҪ��n��1
       n++;
       while(n){
        	a[++len]=n%10;
            n/=10;
       }
       a[len+1]=0;//����Ӱ�� i == lenʱ,a[i+1] == 4 a[i] == 9���ж�
       int flag=0;
       ans=0;
       for(int i=len;i>=1;i--){
       		//����a[i]��ʾ��ʵ����0��1��2..a[i]-1����λ,
			//����ȡ0ʱ,ʵ�ʾ��Ǵ��������������Ϊi-1�ĺ�49�����ִ�
			//����ȡ1��2��..��a[i]-1ʱ,���ǳ˷�ԭ���dp[i-1][2]ƴ�ճ�����Ϊi�ĺ�49�����ִ�
			//֮���Բ�ȡa[i]����Ϊ�޷���֤,dp[i-][2]�е����ִ��Ậ�д���ԭ��n�����ִ�,��ʵ����һλi+1��a[i+1]�͸պú͵�iλ�� 1��2��..a[i]-1ƴ�ճ�����Ϊi+1�ĺ�49�����ִ�
			//�����ǱȽ���ѧ��,���ϼ���û�н��������
            ans+=a[i]*dp[i-1][2];
            //flag == 1��ʾǰ���Ѿ����ֹ�49��,ֱ�Ӻ�dp[i-1][0]����49��ƴ�� �����µĺ�49�����ִ� ͬ��a[i]ʵ�ʱ�ʾ����0��1��2..a[i]-1,Ϊ�˱������ִ����ܱ�n��
            if(flag) ans+=a[i]*dp[i-1][0];//����ǰ������cnt�� �������㲢�����ظ�����  ǰ������ֻ��0-a[i]-1 ������㶼�ٶ�����ǰ��ȡ��a[i]
            else{//flag == 0,ǰ��û����49
            	if(a[i]>4)//a[i]>4 ���������ʵ�ʿ���ȡ��4,�Ϳ��Ժ�dp[i-1][1]���λ��9ƴ�ճ�49
            		ans+=dp[i-1][1];
			}
            if(a[i+1]==4 && a[i] == 9) flag=1;//i+1λ��iλ������49
       }
       printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms ������� ֻ�迪dp[N][[2] Eric�μ��ϵ�
#include<cstdio>
#define N 20
typedef long long LL;
LL dp[N][2];

//״̬��ʾ
//dp[i][0]��ʾiλ��������49����������Ŀ
//dp[i][1]��ʾiλ����������49����������Ŀ
//״̬ת��
//dp[i][0] = dp[i-1][0]*10 + dp[i-2][1]
//dp[i][1] = dp[i-1][1]*10 �C dp[i-2][1]
//�߽�����
//dp[0][1] = 1,dp[1][1] = 10
void init(){
    int i;
    dp[0][1] = 1;
    dp[1][1] = 10;

    for(i=2;i<N;i++){
        dp[i][0] = dp[i-1][0]*10 + dp[i-2][1];
        dp[i][1] = dp[i-1][1]*10 - dp[i-2][1];
    }
}

int main(){
    int i,len,tag,digit[N],cas;
    LL ans,n;

    init();
    scanf("%d",&cas);
    while(cas--){
        scanf("%I64d",&n);
        for(len=0;n;n/=10) digit[len++] = n%10;
        digit[len] = 0;
        ans = 0;
        tag = 0;
        //ͳ��
        //n = 0ak-1��a0
		//��iλ����ȡ1��ai������
		//ans += ai * dp[i][0]
		//���ǰ���Ѿ����ڡ�49������ôi���Ĳ���49��Ҳ��Ҫ����,����iλ����ȡ1��ai������
		//ans += ai *dp[i][1]
		//���ǰ��û�д���49�����룬��ai > 4,����dp[i-1][1]
		//ans += dp[i-1][1]
		//�ж�a[i+1,i]==49,���ó��ֱ�־��������һ������
		//����Ѿ�����49����ô490��0Ҳ�ǽ⣬ans++
        for(i=len-1;i>=0;i--){
            ans += dp[i][0]*digit[i];
            if(tag) ans += dp[i][1]*digit[i];
            else if(digit[i]>4 && i) ans += dp[i-1][1];
            if(digit[i+1]==4 && digit[i]==9) tag = 1;
        }
        //ͳ�ƾ���
        //49
		//4*dp[1][0]+9*dp[0][0]+1 = 1
		//548
		//5*dp[2][0]+dp[1][1]+4*dp[1][0]+8*dp[0][0] = 5*1+10 = 15
		//4910
		//4*dp[3][0]+9*dp[2][0]+dp[1][1]+1*dp[1][0]+dp[1][1]+0*dp[0][0]+1= 4*20+9*1+10+1*0+10+0*0+1 = 110
        printf("%I64d\n",ans+tag);
    }

    return 0;
}
*/
