/*
����:����һ��ֻ��СдӢ���ַ�a,b,c...y,z��ɵ��ַ���S,��S������Ĵ��ĳ���.
���ľ�������������һ�����ַ���,��aba, abba��.
�ַ�������<=110000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3068
˼·:manacher�㷨ģ����.�������ַ���hash���.
�ַ���hash����������Ӵ����ⲩ��:
https://blog.csdn.net/qq_43716912/article/details/98470518?spm=1001.2014.3001.5506
https://blog.csdn.net/Onebelieve_lxl/article/details/104040799?spm=1001.2014.3001.5506
*/
//ac 1528ms �ַ���hash+����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define p 233 //1000007Ҳ��
#define N 110100
using namespace std;
typedef unsigned long long ull;
ull h1[N],h2[N],powr[N];
char s[N];
int main(){
    int len;
    powr[0]=1;
    int k=N/2;
    for(int i=1;i<k;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1)!=EOF){
        len=strlen(s+1);
        h1[0]=0;
        for(int i=1;i<=len;i++)
            h1[i]=h1[i-1]*p+(s[i]-'a'+1);
        h2[len+1]=0;
        for(int i=len;i>=1;i--)
            h2[i]=h2[i+1]*p+(s[i]-'a'+1);
        int l,r,mid,ans=-1;
	/*
	���ֵ�������ʽ��
	1����Χ��Сʱ��r = mid��l = mid + 1��ȡ�м�ֵʱ��mid = (l + r) >> 1.
	2����Χ��Сʱ��l = mid��r = mid - 1��ȡ�м�ֵʱ��mid = (l + r + 1) >> 1;
	*/
        for(int i=1;i<=len;i++){
            l=0,r=min(i-1,len-i);//rΪ���Ļ��İ뾶 ����r=i-1 ����i��Գ����ĵ�����Ĵ�
            while(l<r){//ֻ�����ұ߽粻���ٶ���Ϊֹ ��Ϊ���Ļ��İ뾶
                //�Ի��İ뾶���ж��� �����һ�λ��İ뾶����ֱ�Ӱ���ǰ��Ƚϴ�Ļ��İ뾶ȥ����,
                //��Ϊ��������ȡ�����Ļ��İ뾶����û����ô��,�ᵼ��h����Խ���쳣
                mid=(l+r+1)>>1;
                //s[i-mid~i-1]�Ƿ��s[i+1~i+mid]��� ���ɻ��Ĵ�
                //����ǰ�뾶���ɵ��Ӵ��ǻ��Ĵ� �����������Ĵ��뾶 l=mid,�����´ε�mid�͸�����
                if(h1[i-1]-h1[i-mid-1]*powr[mid] == h2[i+1]-h2[i+mid+1]*powr[mid]) l=mid;
                else r=mid-1;//����ǰ�뾶���ɵ��Ӵ����ǻ��Ĵ� ����Ҫ��С���Ĵ��뾶 r=mid-1 �����´�mid�ͱ�С��
            }
            ans=max(ans,l*2+1);//���ĳ���Ϊ���İ뾶*2+�Գ�����(1)
            l=0,r=min(i,len-i);//����r=i ��ż���Ĵ�
            while(l<r){
                mid=(l+r+1)>>1;//l+r+1 +1��Ϊ�˱���mid=0 ab�����ͻ�hashֵ��Ϊ0�������
                //s[i-mid+1~i]�Ƿ��s[i+1~i+mid-1]���
                if(h1[i]-h1[i-mid]*powr[mid] == h2[i+1]-h2[i+mid+1]*powr[mid]) l=mid;
                else r=mid-1;
            }
            ans=max(ans,l*2);
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//405ms �ַ���hash ����Ĵ������������ӻ��İ뾶 �Ƕ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define p 233 //1000007Ҳ��
#define N 110100
using namespace std;
typedef unsigned long long ull;

ull h1[2*N],h2[2*N],powr[N];
char s[N],str[2*N];
int main(){
    int len;
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1)!=EOF){
        len=strlen(s+1);
        int j=0;
        for(int i=1;i<=len;i++){//ͨ��Ԥ����������#���� ż���Ķ�����Ϊ����� ͳһһ������
            str[++j]='#';
            str[++j]=s[i];
        }
        str[++j]='#';
        h1[0]=0;
        for(int i=1;i<=j;i++)
            h1[i]=h1[i-1]*p+(str[i]-'a'+1);
        h2[j+1]=0;
        for(int i=j;i>=1;i--)//����������Գ��Ӵ���hashֵ
            h2[i]=h2[i+1]*p+(str[i]-'a'+1);
        int l=0;
        for(int i=1;i<=j;i++){//ö�ٻ��ĶԳ����ĵ�
            if(i-l<1 || i+l>j) break;//���ĳ�����ĵ� ���Ե�ǰ����İ뾶Խ��,����ĵ�ֻ������Գ�,���İ뾶�㲻��������,������
            if(h1[i-1]-h1[i-l-1]*powr[l] != h2[i+1]-h2[i+l+1]*powr[l]) continue;//�Ƚ��ԶԳ����ĵ����Ӵ�hashֵ�Ƿ����
            while(str[i-l-1] == str[i+l+1] && i-l-1>=1 && i+l+1<=j) l++;//��ԭ�������İ뾶���ɵĻ��Ĵ����˵���Ⱦ��������ӻ��İ뾶
            //while(h1[i-1]-h1[i-l-1]*powr[l] == h2[i+1]-h2[i+l+1]*powr[l] && i-l>=1 && i+l<=j) l++; ����ÿ�ζ�����hashֵ�Ƚ����� ����һ�� 452ms
        }
        printf("%d\n",l);//��Ϊstr�����#Ԥ����֮��Ļ��İ뾶����������Ĵ��ĳ���
    }
    return 0;
}
*/

/*
manacher�㷨 ����O(n)ʱ�����������Ӵ� ��manacherר����
*/
