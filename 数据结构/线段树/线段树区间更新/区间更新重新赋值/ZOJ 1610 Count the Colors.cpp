/*
����:ժ������
��n�β�����ÿ�ζ��Ƕ�һ�����е�һ���������Ⱦɫ����ɫ������ͬ����
��ʱ��������ɫ�п��ܸ���ǰ�����ɫ�������Ϳ��ɫ���ܿ�������ɫ�м��֣�
ÿ����ɫ�ܱ��ֳɲ������Ķ���.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365109
˼·:�߶����������,ÿ�θ���ֱ�����¸�ֵ.ͳ����ɫ��ͬ��ɫʱ����
�������ȱ������������������߶���,�����õ������иպþ���ԭʼ����������,
����sum[rt]!=-1 ��ʾ�Ѿ�Ⱦɫ,�ȽϺ�֮ǰ��˵���ɫ�Ƿ���ͬ,����ͬ��ͳ��
��ɫ����+1.
*/
//ac 22ms
//�����ĵ�һ������������,������յ���Ⱦɫ,���ֻ��2����ɫ,ֻ�а��߶�Ⱦɫ����3����ɫ
//�����߶�Ⱦɫ,�����ǶԵ�Ⱦɫ,�ϸ����� �߶�������������� ���������߶�Ⱦɫ����� �޷����߶����ϱ�ʾ
#include<cstdio>
#include<cstring>
#define N 8100
#define maxn 8000

int n,sum[N<<2],tp,cnt[N];

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])//������ɫ��ͬʱ,���ڵ��������Ϊ��������ɫ
        sum[rt]=sum[rt<<1];
    else//���򸸽ڵ��������Ϊ-1
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        sum[rt]=-1;
    }
}

void update(int l,int r,int c,int rt,int curl,int curr){
    if(l<=curl && curr<=r){
        sum[rt]=c;
        return;
    }
    pushdown(rt);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,c,rt<<1,curl,mid);
    if(r>mid)
        update(l,r,c,rt<<1|1,mid+1,curr);
    pushup(rt);
}

//��ѯʱ��������������
void query(int rt,int l,int r){
    //���������ǵ�ǰ�����Ѿ�Ⱦɫ �� ����Ҷ�ӽڵ�
    if(sum[rt]!=-1 || l == r){
        if(sum[rt]!=tp && sum[rt]!=-1)//��֮ǰ��ɫ��ͬ,���ҵ�ǰ������Ⱦɫ(sum[rt]!=-1)
            cnt[sum[rt]]++;
        tp=sum[rt];//��¼��һ����ɫΪ��ǰ������ɫ,����Ϊ-1 ûȾɫ.
        return;
    }
    int mid=(l+r)/2;
    query(rt<<1,l,mid);
    query(rt<<1|1,mid+1,r);
}

int main(){
    int x1,x2,c,siz;
    while(scanf("%d",&n)!=EOF){
        memset(sum,-1,sizeof(sum));
        memset(cnt,0,sizeof(cnt));
        tp=-1;
        siz=0;
        while(n--){
            scanf("%d%d%d",&x1,&x2,&c);
            if(siz<c)
                siz=c;
            //x1+1  ��������ʹ�õ�һ������ͳ�Ƶ�[2,3]������������֮��ļ����ɫ
            //����߶����������Ⱦɫ������,�������ȱ��,ĳЩ������ܸպ���������֮�䳤��Ϊ1[mid,mid+1]�ᱻ��©
            update(x1+1,x2,c,1,1,maxn);
        }
        query(1,1,maxn);
        for(int i=0;i<=siz;i++){
            if(cnt[i])
                printf("%d %d\n",i,cnt[i]);
        }
        printf("\n");
    }
    return 0;
}
