/*
����:���ر���ģ����.n<=1000,v<=20000
���õ��������Ż���TLE
����:https://www.acwing.com/problem/content/description/6/
˼·:���������Ż�dp.
�ο����:https://www.acwing.com/problem/content/solution/6/1/
�ο�����:https://blog.csdn.net/weixin_46503238/article/details/115132242
��ʱ��δ��ⵥ�������Ż�.���Ӷ�O(NV)
���ر������������Ż� ��¥��ǳ�"�����˰��⡷"-�����˰��⡷
*/

/*
һ�� n ����Ʒ�������������� m
ÿ����Ʒ�����Ϊv, ��ֵΪw������Ϊs
���������ع�һ�´�ͳ��dp����
dp[i][j] ��ʾ��ǰ i ����Ʒ��������Ϊ j �ı��������õ�������ֵ
dp[i][j] = max(��������Ʒ i������1����Ʒ i������2����Ʒ i, ... , ����k����Ʒ i)
���� k Ҫ���㣺k <= s, j - k*v >= 0
������Ʒ  i = dp[i-1][j]
��k����Ʒ i = dp[i-1][j - k*v] + k*w
dp[i][j] = max(dp[i-1][j], dp[i-1][j-v] + w, dp[i-1][j-2*v] + 2*w,..., dp[i-1][j-k*v] + k*w)
ʵ�������ǲ�����Ҫ��ά��dp���飬�ʵ��ĵ���ѭ�����������ǿ����ظ�����dp������������һ�ֵ���Ϣ
������ dp[j] ��ʾ����Ϊj������£���õ�����ֵ
��ô�����ÿһ����Ʒ i �����Ƕ�����һ�� dp[m] --> dp[0] ��ֵ����� dp[m] ����һ��ȫ������ֵ
dp[m] = max(dp[m], dp[m-v] + w, dp[m-2*v] + 2*w, dp[m-3*v] + 3*w, ...)
�����������ǰ� dp[0] --> dp[m] д������������ʽ
dp[0], dp[v],   dp[2*v],   dp[3*v],   ... , dp[k*v]
dp[1], dp[v+1], dp[2*v+1], dp[3*v+1], ... , dp[k*v+1]
dp[2], dp[v+2], dp[2*v+2], dp[3*v+2], ... , dp[k*v+2]
...
dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j]
�Զ��׼���m һ������ k*v + j������  0 <= j < v
���ԣ����ǿ��԰� dp ����ֳ� j ���࣬ÿһ���е�ֵ��������ͬ��֮��ת���õ���
Ҳ����˵��dp[k*v+j] ֻ������ { dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] }
��Ϊ������Ҫ����{ dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] } �е����ֵ��
����ͨ��ά��һ�������������õ�����������Ļ�������ͱ���� j ���������е�����
���ԣ����ǿ��Եõ�
dp[j]    =     dp[j]
dp[j+v]  = max(dp[j] +  w,  dp[j+v])
dp[j+2v] = max(dp[j] + 2w,  dp[j+v] +  w, dp[j+2v])
dp[j+3v] = max(dp[j] + 3w,  dp[j+v] + 2w, dp[j+2v] + w, dp[j+3v])
...
���ǣ����������ǰ�������ÿ�ζ�������һ�� w ������������Ҫ��һЩת��
dp[j]    =     dp[j]
dp[j+v]  = max(dp[j], dp[j+v] - w) + w
dp[j+2v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w) + 2w
dp[j+3v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w, dp[j+3v] - 3w) + 3w
...
������ÿ����ӵ�ֵ�� dp[j+k*v] - k*w
�����������⣬����Ҫ������
1��ά������Ԫ�صĸ�����������ܼ�����ӣ�������ͷԪ��
2��ά�����еĵ����ԣ�����βֵ >= dp[j + k*v] - k*w
�����У�������Ԫ�صĸ���Ӧ��Ϊ s+1 ������ 0 -- s ����Ʒ i

���ߣ�lys
���ӣ�https://www.acwing.com/solution/content/6500/
��Դ��AcWing
*/

/*
���ߣ�o_O
���ӣ�https://www.acwing.com/solution/content/1537/
��Դ��AcWing
�������:
*/
//ac 2259ms
//���Ӷ�O(NV) 1000*20000=2*10^7
#include <bits/stdc++.h>
using namespace std;

int n, m;
int f[20002], q[20002], g[20002];
int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        int v, w, s;
        cin >> v >> w >> s;
        memcpy(g, f, sizeof(f));
        for (int j = 0; j < v; ++j) {
            /*
            hhΪ����λ��
            ttΪ��βλ��
            ��ֵԽ�󣬱�ʾλ��Խ����
            �����ڶ�β�������Ϊ�գ���hh>ttʱ����Ϊ��
            */
            int hh = 0, tt = -1;
            /*
            q[]Ϊ��������
            �洢ǰ��s(��Ʒ����)�е����ֵ
            �����ͷ(hh)��β(tt)�����ݼ�
            */
            for (int k = j; k <= m; k += v) {

                // f[k] = g[k]; //��һ����û�����ʲô�ã�ȥ����Ҳ��ac������Ϊǰ��ʹ�ù���memcpy,����Ӧ��һ������ȵ�

                //k������赱ǰ��������Ϊk
                //q[hh]Ϊ����Ԫ�أ����ֵ���±꣩
                //g[]Ϊdp[i-1][]
                //f[]Ϊdp[i][]

                /*
                ά��һ����СΪk������
                ʹ���ֵΪǰk��Ԫ�������
                (k - q[hh]) / v ��ʾ��ȡ��Ʒ���������൱����ԭʼ�Ķ��ر���dp��k��
                */
                if (hh <= tt && (k - q[hh]) / v > s) {
                    hh++;
                }

                /*
                ��������ֵ����ֵ����ǰk��Ԫ�ص����ֵ
                (k - q[hh]) / v ��ʾ��ȡ��Ʒ���������൱����ԭʼ�Ķ��ر���dp��k��
                q[hh]Ϊ����Ԫ�أ�g[]��ǰk���������ֵ���±꣩��g[]Ϊdp[i-1][]
                ���� g[q[hh]]Ϊֻ����ǰi-1����Ʒʱ����ǰq[hh]����Ʒ������ֵ
                */
                if (hh <= tt) {
                    f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w);
                }

                /*
                ����βԪ��С�ڵ�ǰԪ�أ����βԪ�س��ӣ�
                ������һ��Ԫ�رȵ�ǰԪ��С�����Ԫ��һ�����ᱻ�õ�����������˼�룩
                g[q[tt]] + (k - q[tt]) / v * w
                ��
                g[k] - (k - j) / v * w
                �ֱ��ʾ��βԪ�ص�ֵ�͵�ǰԪ�ص�ֵ
                */
                while (hh <= tt && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) {
                    tt--;
                }

                //ȥ���˱ȵ�ǰС��Ԫ�أ���֤�������Ԫ�ض��ȵ�ǰԪ�ش����
                q[++tt] = k;
            }
        }
    }
    cout << f[m] << endl;
}

/*
//yxc���д��� ��ע��
//ac 992ms ���������Ż� ���Ű汾
//���Ӷ�O(NV) 1000*20000=2*10^7
#include <iostream>
#include <cstring>

using namespace std;

const int N = 20010;

int dp[N], pre[N], q[N];
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        memcpy(pre, dp, sizeof(dp));
        int v, w, s;
        cin >> v >> w >> s;
        for (int j = 0; j < v; ++j) {
            int head = 0, tail = -1;
            for (int k = j; k <= m; k += v) {

                if (head <= tail && k - s*v > q[head])
                    ++head;

                while (head <= tail && pre[q[tail]] - (q[tail] - j)/v * w <= pre[k] - (k - j)/v * w)
                    --tail;

                if (head <= tail)
                    dp[k] = max(dp[k], pre[q[head]] + (k - q[head])/v * w);

                q[++tail] = k;
            }
        }
    }
    cout << dp[m] << endl;
    return 0;
}
*/

/*
//TLE �������Ż� ���Ӷ�O(��log(num[i])*v) 1000*log(20000)*20000=14000*20000=2.8*10^8
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 20010
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        m=num[i];
        for(int k=1;m>0;k<<=1){//ö�ٵ�i����Ʒ���ܵĶ��������
            m-=k;
            if(m<0) k+=m;
            tw=w[i]*k;
            tv=val[i]*k;
            for(int j=v;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/
