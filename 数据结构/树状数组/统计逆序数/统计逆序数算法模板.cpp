/*
input
5
2 3 1 5 4

output
3

input
7
1 4 2 3 6 5 7

output
3
*/
//��������������Ҫÿ�������Կ���ǰ�����б���С����,ʱ�临�Ӷ�ΪO(n^2)
//ac ��״���� reflect[i]��ɢ�� ʱ�临�Ӷ�O(nlog(n))
//������״����˳��a�����1��n
#include<cstdio>
#include<algorithm>
#define N 10000
using namespace std;

//reflect[i]=val ��ʾԭ��a����iλ�õ���ֵΪval,����val����ɢ������ֵ��Χ��1~n֮��
int n,c[N],reflect[N],ans;
struct Ele{
    int val,pos;
    bool operator <(const Ele &x)const{
        return val<x.val;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x){
    while(x<=n){
        c[x]+=1;//��Ϊ�Ǽ���,�������Ƚڵ��ۼӵ���ֵ����1
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    //a[0].val=-1//���ԭʼֵ����0,a[0].val����Ϊ-1������ɢ������
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].val);
        a[i].pos=i;//��¼��ǰval��ԭ�����е�λ��
    }
    sort(a+1,a+1+n);//C++ stl�е�sort�����ȶ�����,�����ɢ��������ͬ����ֵ �Ծ�Ҫ�������ȵ�
    for(int i=1;i<=n;i++){
        //������ɢ��Ҫ�� ��ȵ�ֵ ��ɢ���ֵҲ���,���������,
        //ԭ����������ǰ����ȵ�ֵ,�������ں���,��ɢ���ֵ�ʹ�,
        //������״�������ʱ,��ɢ����ڵ�ֵ,��������ֵ����� ������������Ͳ���������ͻ����
        if(a[i].val == a[i-1].val)
            reflect[a[i].pos]=reflect[a[i-1].pos];
        else
            reflect[a[i].pos]=i;
    }
    for(int i=1;i<=n;i++){//O(nlog(n))
        update(reflect[i]);//����iλ���ϵ���ֵreflect[i] ������״������
        //getsum(reflect[i])�����iλ��֮ǰ�м�����С�ڵ��ڵ�iλ���ϵ���ֵ,���ｫiλ�ñ������ֵҲ���˽�ȥ
        ans+=i-getsum(reflect[i]);//ͳ�Ƶ�iλ��֮ǰ�м��������ڵ�iλ���ϵ���ֵ,����ǵ�i����������������
    }
    printf("%d",ans);
    return 0;
}

/*
//ac ��״���� reflect[i]��ɢ�� ʱ�临�Ӷ�O(nlog(n))
//������״����˳��a�����n��1
#include<cstdio>
#include<algorithm>
#define N 10000
using namespace std;

//reflect[i]=val ��ʾԭ��a����iλ�õ���ֵΪval,����val����ɢ������ֵ��Χ��1~n֮��
int n,c[N],reflect[N],ans;
struct Ele{
    int val,pos;
    bool operator <(const Ele &x)const{
        return val<x.val;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x){
    while(x<=n){
        c[x]+=1;//��Ϊ�Ǽ���,�������Ƚڵ��ۼӵ���ֵ����1
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].val);
        a[i].pos=i;//��¼��ǰval��ԭ�����е�λ��
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        //��ɢ��,��ԭ�ȵ���ֵ��С��ϵ����,������1~n֮�����ֵ
        //��ԭ������posλ�õ��� val����Ϊ��λ��rnk i
        if(a[i].val == a[i-1].val)//��ɢ����ȵ�ֵһ��Ҫ��֤��ɢ��ֵ���,��Ϊ������c[x]��ʾ����С�ڵ���,��nĩβ��ʼ��ӵ�
        	reflect[a[i].pos]=reflect[a[i-1].pos];
        else
        	reflect[a[i].pos]=i;
	}
    for(int i=n;i>=1;i--){//O(nlog(n))
        //��Ϊ�ǰ��Ӻ���ǰ��˳��ͳ�Ƶ�,��Ҫͳ��i+1~n��λ�����м�������reflect[i]С,��˲�ѯʱҪ��1 ��Ϊ���ϸ�С��,���ڵĲ����������
        ans+=getsum(reflect[i]-1);
        //���·���getsumǰ�󶼿���
        update(reflect[i]);//����iλ���ϵ���ֵreflect[i] ������״������
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//�鲢������������� O(nlog(n))
//��Ϊ��ԭ�������Ϊ�˺ܶ��Ӷ�,����Щ�Ӷ��໥֮�䲻���ص�,
//ÿ���ж���������ж�a[low..mid]�Ƿ��a[mid+1..high]��,��������������,
//�����ģ�����,�ٴ��ж�����ԻὫa[low..high]��Ϊ��ߵ��ֶκ��ұߵ��Ӷ�a[high..],�����Ͳ����ظ�����������.
//�����������˹鲢��������ֶβ����ص�������,�������O(nlog(n))ʱ�䲻�ظ�����������
#include<cstdio>
#define N 10000

int n,a[N],tp[N],ans;

void mergeArr(int low,int mid,int high){
    int i=low,j=mid+1,k=low;
    while(i<=mid && j<=high){
        if(a[i]<=a[j])//������<=,��Ϊֻ���ϸ���ڲŹ��������
            tp[k++]=a[i++];
        else{
            tp[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid)
        tp[k++]=a[i++];
    while(j<=high)
        tp[k++]=a[j++];
    for(int i=low;i<=high;i++)
        a[i]=tp[i];
}

//o(nlog(n))
void mergeSort(int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        mergeSort(low,mid);
        mergeSort(mid+1,high);
        mergeArr(low,mid,high);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    mergeSort(1,n);
    printf("%d",ans);
    return 0;
}
*/
