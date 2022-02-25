#include<bits/stdc++.h>
#define N 100100
#define M 1000
typedef long long ll;
using namespace std;
/*
�ع�Ī��ʱ�临�Ӷ�n*����n
L[i]��R[i] ���Ϊi�Ķ�Ӧ��������˵㡢�Ҷ˵� cnt1Ϊ����ͳ�ƴ��������Ҫ�� cnt2Ϊ���Ҷ˵��ƶ���չͳ�ƴ��������Ҫ��
*/
int a[N],val[N],tmp[N],pos[N],cnt1[N],cnt2[N],L[M],R[M];
ll max0,tmp0,ans[N];
struct Node{
    int l,r,id;
    bool operator < (const Node &x)const{
        //����˵����ڵĿ�����Ϊ��һ�ؼ���,���Ҷ˵�����Ϊ�ڶ��ؼ���.
        if(pos[l]^pos[x.l]) return pos[l]<pos[x.l];//����ʵ�ʰ��� ��˵�return l<x.lҲû�д�.
        else return r<x.r;
    }
}Q[N];

//a[i]<=10^9 ��ɢ�� ����val[i]
void discret(int n){
    int len;
    sort(tmp+1,tmp+1+n);
    len=unique(tmp+1,tmp+1+n)-tmp-1;
    for(int i=1;i<=n;i++)
        val[i]=lower_bound(tmp+1,tmp+1+len,val[i])-tmp;
}
//�ֿ�
void setBlock(int n){
    int siz,num;
    siz=sqrt(n);//n��һ���� ��ȫƽ��,siz*siz����<n
    num=n/siz;//��Ĵ�СΪsiz,��ĸ���Ϊnum.
    for(int i=1;i<=num;i++){
        L[i]=(i-1)*siz+1;
        R[i]=i*siz;
        for(int j=L[i];j<=R[i];j++) pos[j]=i;//��¼����С�����ڵĿ�,�����±�L[i]~R[i]�����Ŀ�ı��Ϊi

    }
    if(R[num]<n){//siz*siz<nʱ,ʣ�µ����ĸ���С��һ��siz��
        num++;//��������һ���¿�
        L[num]=R[num-1]+1;//�¿����˵�Ϊ��һ�����Ҷ˵�+1
        R[num]=n;//�¿���Ҷ˵�Ϊ������ĩβ�±�n
        for(int j=L[num];j<=R[num];j++)
            pos[j]=num;
    }
    /*for(int i=1;i<=num;i++)
        for(int j=L[i];j<=R[i];j++)
            pos[j]=i;*/
}
//ÿ����һ���� �͸�����������Ҫ��(���ִ���*a[i])����ֵ
void add(int k,ll &max1){
    cnt1[val[k]]++;
    max1=max(1ll*cnt1[val[k]]*a[k],max1);
}
//�����ǻع� ����֮ǰ���ӵĴ���,���������ֵ���м���.
void rollback(int k){
    cnt1[val[k]]--;
}

int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        tmp[i]=val[i]=a[i];
    }
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].id=i;
    }
    discret(n);
    setBlock(n);
    sort(Q+1,Q+1+q);
    //lastblock �����ж���ε�ѯ�ʺ���һ��ѯ�ʵ���˵��Ƿ���ͬһ��,����ͬһ�鷽�����β����һ��ѯ�ʵ�rָ����չ����������Ҫ��
    int l=1,r=0,_l,lastblock=0;
    for(int i=1;i<=q;i++){
        /*
        ����ѯ�����Ҷ˵���ͬһ���е�ѯ��,�����ۼ�Q{i].l��Q[i].r���ֵĴ��� �ټ�¼�����Ҫ��,֮���ٻ�ԭ���ִ���
        ֮����Ҫ������������,����Ϊ����ѯ���Ҷ˵㲢�����R[pos[Q[i].l]]��ʼ������չ,���Ծ͵�������cnt2�����¼������
        ���Ҷ˵�ֱ��������ƶ���չ��cnt1���ֿ�.
        */
        if(pos[Q[i].l] == pos[Q[i].r]){
            tmp0=0;
            for(int j=Q[i].l;j<=Q[i].r;j++) cnt2[val[j]]++;//�����õ���cnt2,�����Ҷ˵��ƶ��õ���cnt1
            for(int j=Q[i].l;j<=Q[i].r;j++)
                tmp0=max(1ll*cnt2[val[j]]*a[j],tmp0);
            ans[Q[i].id]=tmp0;
            for(int j=Q[i].l;j<=Q[i].r;j++) cnt2[val[j]]--;
            continue;
        }
        //����µ�ѯ����˵��֮ǰ��˵����ڿ鲻��ͬһ�� ������ѯ�����Ҷ˵�Ҳ����ͬһ��
        if(lastblock ^ pos[Q[i].l]){
            //��ʼ�� ���Ҷ˵� �Ҷ˵�ΪR[pos[Q[i].l]],��˵�ΪR[pos[Q[i].l]]+1
            /*
            �п�����һ��r�Ҷ˵㱾��ͱȽ�С,��:r<R[pos[Q[i].l]],�����������while(l<R[pos[Q[i].l]]+1) rollback(r--);
            �Ὣ�ϴ�ѯ�ʵ�l~r��һ�λ�ԭ,���ұ���ʹ��r~R[pos[Q[i].l]]-1��һ�ζ�������˴���,��һ�ζ�����ٵĴ����ȵ��˺���
            while(r<Q[i].r) add(++r,max0);��õ���ԭ,����ͬʱ�Դ���ѯ��R[pos[Q[i].l]]~Q[i].r�����������ۼӴ��������������Ҫ��.
            ����һ��ѯ�ʵ��Ҷ˵�ϴ�:r>R[pos[Q[i].l]]����Ҫ��r�˵���г�ʼ��ΪR[pos[Q[i].l]].��һ��ѯ�ʵ���˵�l��ͬ
            */
            while(r>R[pos[Q[i].l]]) rollback(r--);
            while(l<R[pos[Q[i].l]]+1) rollback(l++);
            //max0�����Ҫ��Ҫ����Ϊ0,��Ϊ�Ǵ��µĿ鿪ʼ������,ͬʱ��һ��Ÿ���Ϊ��ǰ��pos[Q[i].l]
            max0=0,lastblock=pos[Q[i].l];
        }
        /*
        �����ѯ����˵����������һ����˵���������ͬʱ,����sort����ԭ��,����ѯ�ʵ��Ҷ˵�һ�����ڵ�����һ��ѯ���Ҷ˵�,
        ������ָ����ƶ�����β����һ�ε�λ�ü������ұ���չ�ƶ����Ӵ������������Ҫ��.���Ǳ���ѯ�ʵ���˵�����һ��ѯ�ʵ���˵��С��ϵ�ǲ�ȷ����,
        ����˵��������п��ܴ�,Ҳ�п���С,���ⲻӰ����˵�������չ ���Ӵ���,��Ϊÿ�ζ��Ǵ����ѯ����˵����ڿ���ұ߽翪ʼ��չ��,
        ��Ϊ������˵�һ��������˵����ڿ��ұ߽������.
        */
        //�ƶ��Ҷ˵� ���м������������Ҫ��  �������ʵ�ʾ��Ƕ�����˵���ͬһ���ڵ���Ī�ӵ�����ת��,������˵����ڿ����Ī��,��ͬ�� �������
        while(r<Q[i].r) add(++r,max0);
        //�����¼��˵�ĳ�ʼֵ,��_l�����ƶ��ۼ�,֮�󷽱㻹ԭcnt����
        _l=l;
        tmp0=max0;//ͬʱ������˵����Ҫ�ȼ��� ��һ����ʱֵ,��Ϊ�����˵㻹Ҫ��ԭ,��Ҫ����Ȼֻ�ܼ����Ҷ˵��ƶ����ӵ�,����������һ��ѯ�� ��˵���ܼ�����չ
        //�ƶ���˵�,���Է��� ���Ҷ˵㶼����������,�������Ӵ���.
        while(_l>Q[i].l) add(--_l,tmp0);
        ans[Q[i].id]=tmp0;//��¼��ǰѯ�����������Ҫ��
        while(_l<l) rollback(_l++);//��ԭ��˵��ƶ����Ӵ��� ��ԭ�ȵ�R[pos[Q[i].l]]+1
    }
    for(int i=1;i<=q;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
