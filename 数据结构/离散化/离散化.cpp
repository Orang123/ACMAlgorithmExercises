��ɢ������
��һ��������ɢ���������в�ѯ�ǱȽϳ��õ�Ӧ�ó�����
// a[i] Ϊ��ʼ����,�±귶ΧΪ [1, n]
// len Ϊ��ɢ�����������Ч����
std::sort(a + 1, a + 1 + n);

len = std::unique(a + 1, a + n + 1) - a - 1;
// ��ɢ�����������ͬʱ�����ɢ�����ʲ�ͬ���ĸ�����

�����������ɢ��֮�����ʹ�� std::lower_bound ����������ɢ��֮������������±�ţ���
std::lower_bound(a + 1, a + len + 1, x) - a;  // ��ѯ x ��ɢ�����Ӧ�ı��
ͬ���أ�����Ҳ���Զ� vector ������ɢ����
// std::vector<int> a, b; // b �� a ��һ������
std::sort(a.begin(), a.end());
a.erase(std::unique(a.begin(), a.end()), a.end());
for (int i = 0; i < n; ++i)
  b[i] = std::lower_bound(a.begin(), a.end(), b[i]) - a.begin();


/*
//ժ�Բ���:https://blog.csdn.net/QiHang_QiHang/article/details/80739063
typedef long long ll;
const int N = 1e5+10;

int main()
{
    int a[N],sub[N];
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++) {
        scanf("%d",&sub[i]);
        a[i] = sub[i];
    }
    sort(sub, sub + n);
    int size = unique(sub, sub + n) - sub;

    printf("size  %d\n",size);
    for(int i = 0; i < n; i++)
        a[i] = lower_bound(sub, sub + size, a[i]) - sub;
    for(int i =0 ;i < n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
*/

/*
//ժ�Բ���:https://blog.csdn.net/tb_youth/article/details/104334081
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int a[8] = {1,5,3,2,3,2,7,90};
    sort(a,a+8);
    vector<int>vec(a,a+8);

    cout<<"ʹ��uniqueǰ:"<<endl;
    for(int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;

    //ʹ��uniqueǰ��Ҫ��֤����������ģ�
    //unique���ص��ǲ��ظ��������ĵ�ַ����������ʽ����
    //uniqueֻ�ǽ��ظ���Ԫ�ص�λ���ú���������ͬ��Ԫ��������
    int cnt = unique(vec.begin(),vec.end())-vec.begin();

    cout<<"Ŀ�����г��ȣ�"<<cnt<<endl;
    cout<<"ʹ��unique��:"<<endl;
    for(int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
    cout<<"ʹ��erase��:"<<endl;
    vec.erase(vec.begin()+cnt,vec.end());
    for(int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
    return 0;
}

*/
