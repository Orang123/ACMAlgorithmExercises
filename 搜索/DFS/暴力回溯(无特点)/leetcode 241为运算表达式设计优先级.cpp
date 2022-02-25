/*
题意:给定一个含有数字和运算符的字符串，为表达式添加括号，改变其运算优先级以求出不同的结果。
你需要给出所有可能的组合的结果。有效的运算符号包含 +, - 以及 * 。
输入: "2*3-4*5"
输出: [-34, -14, -10, -10, 10]
解释:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
链接:https://leetcode-cn.com/problems/different-ways-to-add-parentheses
*/
class Solution {
public:
    vector<int> diffWaysToCompute(string s) {
        vector<int> res;
        for(int i=0;i<s.size();i++){
            if(!isdigit(s[i])){//枚举分隔开的运算符,先计算运算符左右两侧的结果,最后再让res1和res2结合
                auto res1=diffWaysToCompute(s.substr(0,i));//先计算左侧下标[0,i-1]的子串
                auto res2=diffWaysToCompute(s.substr(i+1));//先计算右侧下标[i+1,s.size()-1]的子串
                for(auto &val1 : res1){
                    for(auto &val2 : res2){
                        if(s[i] == '+')
                            res.push_back(val1+val2);
                        else if(s[i] == '-')
                            res.push_back(val1-val2);
                        else if(s[i] == '*')
                            res.push_back(val1*val2);
                    }
                }
            }
        }
        if(res.empty())//在不断分割的过程中,中会使得 s只包含数字,结束状态就是数字本身
            res.push_back(stoi(s));
        return res;
    }
};
