#ifndef SOLUTION_H
#define SOLUTION_H

// #include <algorithm>
#include <execution>
#include <cassert> // Required for assert()
#include <map>
#include <numeric>
#include <random>
#include <ranges>
#include <string>
#include <set>
#include <unordered_set>
#include <vector>

#include "node.h"
#include "vkstd.h"


// using namespace std;
using std::cout;
using std::endl;
using std::string;


class Solution
{
private:
    vector<int> m_ivec1;    // vector integer

    // string f_stringify(Node<int>*) const;
    // Node* vecToNode

    static void prn( const std::string &res, const std::string &shouldBe, const std::string &note );
    /* deprecated
     * use temp library vkstd::toString instead

    static string vecToString(const vector<int>& vec);

    static string vecToString(const vector<std::string>& vec);

    static string vecToString(vector<char>& vec);
*/
    string mlc_151(string s);  //reverseWords

    Node<int>* mlc_82(Node<int>*);

    Node<int>* elc_83(Node<int>*);

    // Reorder List
    void mlc_143(Node<int>*);

    // ListNode* deleteMiddle(ListNode* );
    Node<int>* mlc_2095(Node<int>* );
    
//    bool search(vector<int>& nums, int target);
    bool lc_81(vector<int>& nums, int target) const;

    // vector<int> findClosestElements(vector<int>& arr, int k, int x)
    vector<int> lc_658(vector<int>& arr, int k, int x, int mode=0) const;

    // int longestArithSeqLength(vector<int>& nums)
    int lc_1027(vector<int>& nums, int mode=0) const;

    // int findNthDigit(int n)
    int lc_400(int n, int mode=0) const;

    // int numFriendRequests(vector<int>& ages)
    int lc_825(vector<int>& ages, int mode=0) const;

    // int numMatchingSubseq(string s, vector<string>& words)
    int lc_792(string s, vector<string>& words, int mode=0) const;

    // int lengthOfLIS(vector<int>& nums)
    int lc_300(vector<int>& nums, int mode=0) const;

    // int minSubArrayLen(int target, vector<int>& nums)
    int lc_209(int target, vector<int>& nums, int mode=0) const;

    // long long sumDigitDifferences(vector<int>& nums)
    long long lc_3153(vector<int>& nums, int mode=0) const;

    // int totalHammingDistance(vector<int>& nums)
    int lc_477(vector<int>& nums, int mode=0) const;

    // int integerReplacement(int n)
    int lc_397(int n, int mode=0) const;

    // int maxProduct(vector<string>& words)
    int lc_318(vector<string>& words, int mode=0) const;

    // int kConcatenationMaxSum(vector<int>& arr, int k)
    int lc_1191(vector<int>& arr, int k, int mode=0) const;

    // int countTexts(string pressedKeys)
    int lc_2266(string pressedKeys, int mode=0) const;

    // int numDecodings(string s)
    int lc_91(string s, int mode=0) const;

    // int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    int lc_127(string beginWord, string endWord, vector<string>& wordList, int mode=0) const;

    // int minMutation(string startGene, string endGene, vector<string>& bank)
    int lc_433(string startGene, string endGene, vector<string>& bank, int mode=0) const;

    // int findTheLongestSubstring(string s)
    int lc_1371(string s, int) const;

    // string countOfAtoms(string formula)
    string lc_726(string formula, int mode=0) const;

    // string decodeString(string s)
    string lc_394(string s, int mode=0) const;

    // long long largestPerimeter(vector<int>& nums);
    long long lc_2971(vector<int>& nums, int mode=0);

    // int triangleNumber(vector<int>& nums)
    int lc_611(vector<int>& nums, int mode);

    // TODO
    // int minOperations(int k)
    int lc_3091(int k, int mode);

    // int maxDistance(vector<int>& nums1, vector<int>& nums2)
    int lc_1855(vector<int>& nums1, vector<int>& nums2, int mode = 0);

    // int evalRPN(vector<string>& tokens)
    int lc_150(vector<string>& tokens, int mode = 0);

    // int calculate(string s);
    int lc_224(string s);

    // int calculate(string s);
    int lc_227(string s);


public:
    Solution();

    // s-show size
    static std::string stringify(vector<int>& vec, bool s=true);

    // int nextGreaterElement(int n)
    const int lc_556(int n, int mode = 0);

    // void nextPermutation(vector<int>& nums)
    const void lc_31(vector<int>& nums);

    void test();

    void lc_81_test() const;
    void lc_1027_test() const;
    void lc_658_test() const;
    void lc_400_test() const;
    void lc_825_test() const;
    void lc_792_test() const;
    void lc_300_test() const;
    void lc_209_test() const;
    void lc_3153_test() const;
    void lc_477_test() const;
    void lc_397_test() const;
    void lc_318_test() const;
    void lc_1191_test() const;
    void lc_2266_test() const;
    void lc_91_test() const;
    void lc_127_test() const;
    void lc_433_test() const;
    void lc_1371_test() const;
    void lc_726_test() const;
    void lc_394_test() const;
    void lc_2971_test();
    void lc_611_test();
    void lc_3091_test();
    void lc_150_test();

    void lc_224_test();

    void lc_227_test();

    void lc_1855_test();

    void mlc_2095_test();

    void mlc_143_test();

    void mlc_151_test();

    void mlc_82_test();

    void elc_83_test();
};

#endif // SOLUTION_H
