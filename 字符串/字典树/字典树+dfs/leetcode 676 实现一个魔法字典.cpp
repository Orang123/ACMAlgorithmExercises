/*
题意:设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 互不相同 。
如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，使得所
形成的新单词存在于你构建的字典中。
实现 MagicDictionary 类：
MagicDictionary() 初始化对象
void buildDict(String[] dictionary) 使用字符串数组 dictionary 设定该数据结构，
dictionary 中的字符串互不相同
bool search(String searchWord) 给定一个字符串 searchWord ，判定能否只将字符串中
一个 字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。
如果可以，返回 true ；否则，返回 false 。
链接:https://leetcode-cn.com/problems/implement-magic-dictionary/
*/
//前缀树的程序表示
class TrieNode {
public:
    bool isWord;//当前节点为结尾是否是字符串
    vector<TrieNode*> children;
    TrieNode() : isWord(false), children(26, nullptr) {}
    ~TrieNode() {
        for (TrieNode* child : children)
            if (child) delete child;
    }
};

class MagicDictionary {
private:
    TrieNode *trieRoot;//构建的单词后缀树
    //在树中插入一个单词的方法实现
    void addWord(string &word) {
        TrieNode *ptr = trieRoot;//扫描这棵树，将word插入
        //将word的字符逐个插入
        for (auto ch : word) {
            if (ptr->children[ch - 'a'] == NULL) {
                ptr->children[ch - 'a'] = new TrieNode();
            }
            ptr = ptr->children[ch - 'a'];
        }
        ptr->isWord = true;//标记为单词
    }
    //在nowTreePtr中搜索word[index]，isMod代表的是是否使用了替换一个字母的机会
    bool myFindWord(TrieNode *nowTreePtr, string &word, int index, bool isMod){
        if (nowTreePtr == NULL){
            return false;
        }
        if (word.size() == index){
            //此时搜索完毕，必须保证nowTreePtr也到达了一个单词的尾端，并且替换一个字母的机会也使用了
            return isMod && nowTreePtr->isWord;
        }
        else{
            //搜索nowTreePtr的26个节点
            for (int i = 0; i < 26; ++i){
                if (nowTreePtr->children[i] != NULL){
                    if ('a' + i == word[index]){
                        //成功匹配，继续搜索下一个字母
                        if (myFindWord(nowTreePtr->children[i], word, index + 1, isMod)){
                            return true;
                        }
                    }
                    else if (isMod == false && myFindWord(nowTreePtr->children[i], word, index + 1, true)){
                        //如果'a' + i ！= word[index]，则使用替换字母的机会（在此之前替换字母的机会是没有使用的，因为只能使用一次）
                        return true;
                    }
                }
            }
            return false;
        }
    }
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        trieRoot = new TrieNode();
    }

    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        //构建字典树
        for (auto &word : dict){
            addWord(word);
        }
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        return myFindWord(trieRoot, word, 0, false);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
