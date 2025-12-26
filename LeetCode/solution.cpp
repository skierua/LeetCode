#include "solution.h"

Solution::Solution() {}

void Solution::test(){
    vector<int> v{2,3,4,1,2,3};
    testNode_data(v);
    Node<int> *n = makeNode<int>(v);
    // auto p = make_unique<Node<int>*>( makeNode<int>(v));
    auto p = make_unique<Node<int>*>(n);
    cout << "list=" << n->stringify();
    // std::unique_ptr<Node<int>> *n = makeNode<int>(v);
    // auto tmp = make_unique<Node<int>>
    // delete n;

}

void Solution::prn( const std::string &res, const std::string &shouldBe, const std::string &note = "" ) {

    std::cout << ((res.compare(shouldBe)==0 ) ? "+++" : "\033[31m---")     // \033[32m green
              << " res= " << res
              << " sB=" << shouldBe
              << " orig= " << note
              << "\033[0m" << std::endl;
}

/* deprecated
 * use temp library vkstd::toString instead
string Solution::vecToString(const vector<int>& vec) {

    string rslt = "";
    auto count{0};
    for( const auto &v : vec){
        ++count;
        rslt += (rslt.empty() ? "" : ", ") + std::to_string(v);
        if (count > 10) {
            rslt += ", ...";
            break;
        }
    }
    return "["+rslt+"](" + to_string(std::size(vec))+")";

}

string Solution::vecToString(const vector<std::string>& vec) {

    string rslt = "";
    auto count = 0;
    for(const auto &v : vec){
        ++count;
        rslt += (rslt.empty() ? "" : ", ")
                + (v.empty() ? "[E]"
                             : (v.size() < 11 ? v
                                              : (v.substr(0,10) + ".../" + to_string(v.size()))));
        if (count > 10) {
            rslt += ", ...";
            break;
        }
    }
    return "["+rslt+"](" + to_string(std::size(vec))+")";

}

string Solution::vecToString(vector<char>& vec) {
    string rslt = "";
    auto count = 0;
    for( const auto &v : vec){
        ++count;
        rslt += (rslt.empty() ? "" : ",") + std::string(1,v);
    }
    return "["+rslt+"](" + to_string(count)+")";

}
*/

bool Solution::lc_81(vector<int>& nums, int target) const{
    auto len = nums.size();
    bool res{false};
    if (len == 0) return res;
    if (len == 1) {
        if (nums[0] == target) return true;
        else return res;
    }

    size_t lf{0}, md{0}, rt{len-1};

    while (lf < rt){
        md = lf + (rt - lf)/2; //break;
        // cout << " md="<< md << " lf=" << lf  << " rt=" << rt
        //      << " val=" << nums[md]
        // << endl;
        if (nums[md] == target
            || nums[lf] == target
            || nums[rt] == target){
            res = true;
            break;
        }
        if (nums[md] == nums[lf] && nums[md] == nums[rt]) {
            ++lf;
            --rt;
            // cout << "EQUAL md="<< md << " lf=" << lf  << " rt=" << rt
            // << endl;
            continue;
        }
        if (nums[lf] <= nums[md]) {
            if (target < nums[md] && target >= nums[lf]) {
                rt = md;
                // break;
            } else  lf = ++md;
        } else {
            if (target > nums[md] && target <= nums[rt]) {
                lf = ++md;
                // break;
            } else  rt = md;
        }
    }
    // if ( !res && lf < len )  res = (nums[lf] == target);
    // cout << " md="<< md << " lf=" << lf  << " rt=" << rt
    // << endl;

    return res;
}

void Solution::lc_81_test() const{
    vector< pair<pair<vector<int>,int>, bool> >
        data = {
            {{{2,5,6,0,0,1,1,1,1,1,1,1,2}, 0}, true },
            // ,{{{2,5,6,0,0,1,2},3}, false }
            // ,{{{2},2}, true }
            // ,{{{2},3}, false }
            // ,{{{2,2},2}, true }
            // ,{{{2,2},3}, false }
            // ,{{{2,5,6,0,0,1,1,1,1,1,1,1,2}, 6}, true }
            // ,{{{2,5,6,0,0,1,1,1,1,1,1,1,2}, 7}, false }
            {{{1,0,1,1,1},0}, true },
            {{{1,1,1,0,1},0}, true },
            {{{1,3,1,1,1},3}, true },
            {{{1,1,1,3,1},3}, true },
            {{{2,1,1,2,2,2,2},1}, true },
                };
    // string res{""};
    auto comp{false} ;
    for (auto& v: data) {
        comp = lc_81(v.first.first, v.first.second );
        cout << ((comp ? 1 : 0) == (v.second ? 1 : 0) ? "+ " : "- ")
             << "data= " << stringify(v.first.first)
             << " t= " << v.first.second
             << " res=" << (comp ? "TRUE " : "FALSE ")
             << endl;
    }
}

// int nextGreaterElement(int n)
const int Solution::lc_556(int n, int mode) {

    if (n < 10) return -1;

    auto v_str = [&n](){
        std::string nums = std::to_string(n);
        auto itpivot{std::next(nums.rbegin())};
        for ( ; itpivot != nums.rend(); ++itpivot) {
            if ( *itpivot < *std::next(itpivot,-1) ) {
                break;
            }
        }
        if (itpivot == nums.rend()) {
            nums = "-1";
        } else {
            for (auto it{std::rbegin(nums)}; it < itpivot; ++it ){
                if (*it > *itpivot) {
                    std::iter_swap(itpivot, it);
                    break;
                }
            }
            std::reverse(std::rbegin(nums),itpivot);
        }
        long long lres  = std::stoll(nums);
        if (lres > INT_MAX) return -1;

        return static_cast<int>(lres);
    };

    auto v_int = [&n](){
        long long left{n}, right{0};
        auto pivot{0}, rmin{0}, lpov{1}, rpov{1};
        auto tmp = left % 10;
        left /= 10;
        while (left > 0) {
            // std::cout << "BEF left=" << std::to_string(left) << " tmp=" << std::to_string(tmp) << std::endl;
            pivot = left % 10;
            lpov *= 10;
            left /= 10;
            if (pivot < tmp) break;
            tmp = pivot;
            // std::cout << "AFT left=" << std::to_string(left) << " tmp=" << std::to_string(tmp) << std::endl;
        }
        if (left == 0 && !(pivot < tmp)) return -1;
        left *= 10;
        right = n % lpov;

        while (!(rmin > pivot)){
            rmin = right % 10;
            rpov *= 10;
            right /=10;
        }
        left = (left + rmin) * lpov;
        right = right * rpov + pivot * (rpov/10) + n % (rpov/10);


        // reverse right
        tmp = 0;
        while(right > 0){
            tmp *=10;
            tmp += (right % 10);
            right /= 10;
            rpov /=10;
        }
        left += tmp;
        // cout << "n=" << std::to_string(n)<< " left=" << std::to_string(left)
        //      << " lpov=" << std::to_string(lpov)
        //      << " pivot=" << std::to_string(pivot)
        //      << " rmin=" << std::to_string(rmin)
        //      << " right=" << std::to_string(right)
        //      << " tmp=" << std::to_string(tmp)
        //      << " rpov=" << std::to_string(rpov)
        //      // << " p1=" << std::to_string(p1) << " p2=" << std::to_string(p2)
        //      << std::endl;
        if (left > INT_MAX) left = -1;

        return static_cast<int>(left);
    };

    if (mode == 1) return v_int();
    else return v_str();

    // return v_int();
    // return v_str();
}

// void nextPermutation(vector<int>& nums)
const void Solution::lc_31(vector<int>& nums) {
    auto len = nums.size();
    if (len < 2) return;
    auto itpivot{std::next(nums.rbegin())};
    // advance(itpivot, 1);
    for ( ; itpivot != nums.rend(); ++itpivot) {
        if ( *itpivot < *std::next(itpivot,-1) ) {
            break;
        }
    }
    if (itpivot == nums.rend()) {
        std::reverse(std::begin(nums),std::end(nums));
    } else {
        for (auto it{std::rbegin(nums)}; it < itpivot; ++it ){
            if (*it > *itpivot) {
                std::iter_swap(itpivot, it);
                break;
            }
        }
        std::reverse(std::rbegin(nums),itpivot);
    }

}

std::string Solution::mlc_151(std::string s){

    // consume double extra space 10-20μs
    auto reverse1 = [&s] () {
        std::string res{""};
        u_long wstart{0};
        auto word_trg{false};
        for (auto i{s.size()}; i > 0; --i) {
            if (s[i-1] == ' '){
                // cout << "1111 i=" << i << " wst=" << wstart << " trg=" << word_trg << " w=" << s.substr(i, wstart-i) << endl;
                if (word_trg){
                    // res += "-" + s.substr(i, wstart-i);
                    res += (res.empty() ? "" : " " ) + s.substr(i, wstart-i);
                }
                word_trg = false;;
            } else {
                // cout << "1111" << endl;
                if (!word_trg) wstart = i;
                word_trg = true;
                // res += *it;
            }
        }
        // cout << "4444"\
        //      << " wst=" << wstart << " trg=" << word_trg
        //      << " w=" << s.substr(0, wstart)
        //      << endl;
        if (word_trg) res += (res.empty() ? "" : " " ) + s.substr(0, wstart);

        return res;
    };

    // the same string + doble extra space 12-20μs
    auto reverse2 = [&s] () {
        auto len{s.size()};
        u_long wstart{0};
        auto word_trg{false};
        for (auto i{len}; i > 0; --i) {
            if (s[i-1] == ' '){
                if (word_trg){
                    s += (s.size() == len ? "" : " " ) + s.substr(i, wstart-i);
                }
                word_trg = false;;
            } else {
                if (!word_trg) wstart = i;
                word_trg = true;
            }
        }
        if (word_trg) s += (s.size() == len ? "" : " " ) + s.substr(0, wstart);

        return s.erase(0,len);
    };

    // the same string + NO extra space 15-39μs
    auto reverse3 = [&s] () {
        auto len{s.size()};
        u_long wstart{0};
        auto word_trg{false};
        for (auto i{len}; i > 0; --i) {
            if (s[i-1] == ' '){
                if (word_trg){
                    s += (" ") + s.substr(i, wstart-i);
                    s.erase(i,wstart-i);
                }
                word_trg = false;;
            } else {
                if (!word_trg) wstart = i;
                word_trg = true;
            }
        }
        if (word_trg) {
            s += (" ") + s.substr(0, wstart);
            s.erase(0,wstart);
        }
        s.erase(s.begin(),
                std::find_if(s.begin(),
                            s.end(),
                            [](unsigned char ch) { return !std::isspace(ch); }
                            )
        );
        return s;
    };


    return reverse1();

    // return reverse2();

    // return reverse3();
}

void Solution::mlc_151_test(){
    vector< pair<std::string,std::string> >
        data ={
            {"the sky is blue", "blue is sky the"},
            {"  hello world  ", "world hello"},
            {"a good   example", "example good a"},
            {"a   ", "a"},
            {"   w", "w"},
            {"f", "f"},
            {"", ""},
            };
    string sres, starg;
    const auto t1 = std::chrono::steady_clock::now();
    for (const auto &v: data) {
        sres = mlc_151(v.first);
        starg = v.second;
        cout << (sres.compare(starg)==0 ? "+ " : "- ")
             << "data= " << v.first
             << " res=" << sres
             << " target=" << starg << endl;
    }
    const auto t2 = std::chrono::steady_clock::now();
    cout << " time=" << to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) << " μs" << endl;
}

Node<int>* Solution::mlc_82(Node<int>* head){
    if (head == nullptr || head->next == nullptr)
        return head;

    auto prn = [&head] (){
        auto *p{head};
        while (p) cout << p->val << ",", p = p->next;
        cout << endl;
        return;
    };

    Node<int> *pprev{nullptr}, *pcur{head}, *pnext{head->next}, *tmp(nullptr);
    while (pnext != nullptr) {
        if (pcur->val == pnext->val) {
            while (pnext != nullptr && pnext->val == pcur->val) {
                // delete pnext;
                // cout
                //     << "remove " << pnext->val << ","
                //     << " pnext->next=" << (pnext->next==nullptr ? "NULL" : to_string(pnext->next->val))
                //     << endl;
                tmp = pnext;
                pnext = pnext->next;
                pcur->next = pnext;
                delete tmp;
            }
            // cout << endl;
            if (head == pcur) {
                head = pnext;
            }
            // delete pcur;
            // prn();
            if (pprev != nullptr) {
                pprev->next = pnext;
            }
            tmp = pcur;
            pcur = pnext;
            delete tmp;
            if (pnext != nullptr) pnext = pnext->next;
            // cout
            //      << "head=" << (head==nullptr ? "NULL" : to_string(head->val))
            //      << " prev=" << (pprev==nullptr ? "NULL" : to_string(pprev->val))
            // << " pcur=" << (pcur==nullptr ? "NULL" : to_string(pcur->val))
            // << " pnext=" << (pnext==nullptr ? "NULL" : to_string(pnext->val)) << endl;
        } else {
            pprev = pcur;
            pcur = pnext;
            pnext = pnext->next;
            // prn();
                // cout << "2prev=" << (pprev==nullptr ? "NULL" : to_string(pprev->val))
                // << " pcur=" << (pcur==nullptr ? "NULL" : to_string(pcur->val))
                // << " pnext=" << (pnext==nullptr ? "NULL" : to_string(pnext->val)) << endl;
        }

    }

    return head;

}

void Solution::mlc_82_test(){

    vector< pair<vector<int>,vector<int>> >
        data ={
            {{1,2,3,3,4,4,5}, {1,2,5}},
            {{1,1,1,2,3},{2,3}},
            {{1,1,1,3,3},{}},
            {{1,3,3},{1}},
            {{3,3},{}},
            };
    // string res{""};
    string sres, starg;
    Node<int> *n;

    for (auto v: data) {
        n = makeNode<int>(v.first);
        auto p = make_unique<Node<int>*>(n);
        Node<int>* nn = mlc_82(n);
        sres = (nn != nullptr ? nn->stringify() : "[](0)");
        starg = stringify(v.second);
        cout << (sres.compare(starg)==0 ? "+ " : "- ")
            << "data= " << stringify(v.first)
             << " res=" << sres
             << " target= " << starg << endl;
        // res = res
        //       + "data= " + stringify(v.first)
        //         + " res=" + nn->stringify()
        // //         + " target= " + stringify(v.second)
        //     ;
        delete nn;
    }
}

Node<int>* Solution::elc_83(Node<int>* head){
    if (head == nullptr || head->next == nullptr)
        return head;

    Node<int>  *pcur{head}, *pnext{head->next}, *tmp(nullptr);
    while (pnext != nullptr) {
        if (pcur->val == pnext->val) {
            while (pnext != nullptr && pnext->val == pcur->val) {
                tmp = pnext;
                pnext = pnext->next;
                pcur->next = pnext;
                delete tmp;
            }
        } else {
            pcur = pnext;
            pnext = pnext->next;
        }

    }

    return head;

}

void Solution::elc_83_test(){

    vector< pair<vector<int>,vector<int>> >
        data ={
                {{1,2,3,3,4,4,5}, {1,2,3,4,5}},
                {{1,1,1,2,3},{1,2,3}},
                {{1,1,2},{1,2}},
                {{1,3,3},{1,3}},
                {{3,3},{3}},
                {{1},{1}},
                };
    // string res{""};
    string sres, starg;
    Node<int> *n;

    for (auto v: data) {
        n = makeNode<int>(v.first);
        auto p = make_unique<Node<int>*>(n);
        Node<int>* nn = elc_83(n);
        sres = (nn != nullptr ? nn->stringify() : "[](0)");
        starg = stringify(v.second);
        cout << (sres.compare(starg)==0 ? "+ " : "- ")
             << "data= " << stringify(v.first)
             << " res=" << sres
             << " target= " << starg << endl;
       delete nn;
    }
}

void Solution::mlc_143(Node<int>* head){

    Node<int>  *pmid{head}, *crnt{head};
    if (crnt == nullptr || crnt->next == nullptr) return;

    // find list middle
    while (crnt->next != nullptr && crnt->next->next != nullptr) {
        crnt = crnt->next->next;
        pmid = pmid->next;
    }
    // std::cout << "AF" << " pmid=" << pmid->val << " crnt=" << crnt->val << std::endl;

    // reverse second half
    Node<int>  *prev{nullptr},  *next{nullptr};
    crnt = pmid->next;
    pmid->next = nullptr;
    while (crnt != nullptr){
        next = crnt->next;
        crnt->next = prev;
        prev = crnt;
        crnt = next;
    }

    // reorder list
    crnt = head;
    while(prev != nullptr){
        next = prev;
        prev = prev->next;
        // std::cout << "555" << " pmid=" << pmid->val
        //           << " crnt=" << crnt->val
        //           << " next=" << next->val
        //           << std::endl;

        next->next = crnt->next;
        crnt->next = next;
        crnt = next->next;
    }
}


void Solution::mlc_143_test(){

    vector< pair<vector<int>,vector<int>> >
        data ={
                {{1,2,3,4,5}, {1,5,2,4,3}},
                {{1,2,3,4},{1,4,2,3}},
            {{1,2,3,4,5,6,7,8}, {1,8,2,7,3,6,4,5}},
            {{1,2,3,4,5,6,7,8,9}, {1,9,2,8,3,7,4,6,5}},
                {{3,4},{3,4}},
                {{1},{1}},
                };
    // string res{""};
    string sres, starg;
    Node<int> *n;

    for (auto v: data) {
        n = makeNode<int>(v.first);
        // auto p = make_unique<Node<int>*>(n);
        mlc_143(n);
        sres = (n != nullptr ? n->stringify() : "[](0)");
        starg = stringify(v.second);
        cout << (sres.compare(starg)==0 ? "+++ " : "--- ")
             << "data= " << stringify(v.first)
             << " res=" << sres
             << " target= " << starg << endl;
        delete n;
    }
}

Node<int>* Solution::mlc_2095(Node<int>* head) {

    if (head == nullptr) return head;
    if (head->next == nullptr) {
        // delete head;
        head = nullptr;
        // std::cout << "000" << " head=" << head->val << std::endl;
        return nullptr;
    }

    Node<int>  *mid{head},*prev{head}, *crnt{head};
    // find list middle
    crnt = crnt->next->next;
    mid = mid->next;
    // std::cout << "111" << " prev=" << prev->val << " mid=" << mid->val << " crnt=" << crnt->val << std::endl;
    while (crnt != nullptr && crnt->next != nullptr) {
        crnt = crnt->next;
        if (crnt != nullptr) crnt = crnt->next;
        mid = mid->next;
        prev = prev->next;
    }
    prev->next = mid->next;
    delete mid;

    return head;
}

void Solution::Solution::mlc_2095_test(){

    vector< pair<vector<int>,vector<int>> >
        data ={
                {{1,3,4,7,1,2,6}, {1,3,4,1,2,6}},
                {{1,2,3,4},{1,2,4}},
                {{2,1},{2}},
                {{1},{}},
                };
    // string res{""};
    string sres, starg;
    Node<int> *n;

    for (auto v: data) {
        n = makeNode<int>(v.first);
        // auto p = make_unique<Node<int>*>(n);
        auto nres = mlc_2095(n);
        sres = (nres != nullptr ? nres->stringify() : "[](0)");
        starg = stringify(v.second);
        cout << (sres.compare(starg)==0 ? "+++ " : "--- ")
             << "data= " << stringify(v.first)
             << " res=" << sres
             << " target= " << starg << endl;
        delete n;
    }
}

int Solution::lc_1027(vector<int>& nums, int mode) const{

    auto l0 = [&nums](){    // from https://algo.monster/liteproblems/1027
        u_long n = nums.size();

        // dp[i][diff] represents the length of arithmetic sequence ending at index i
        // with difference 'diff' (offset by 500 to handle negative differences)
        // Since difference range is [-500, 500], we use index [0, 1000] after offset
        int dp[n][1001];
        memset(dp, 0, sizeof(dp));

        int maxLength = 0;

        // Iterate through each element as the ending point of arithmetic sequence
        for (int i = 1; i < n; ++i) {
            // Check all previous elements as potential previous element in sequence
            for (int prev = 0; prev < i; ++prev) {
                // Calculate the difference and offset by 500 to handle negative values
                // This maps difference range [-500, 500] to array index [0, 1000]
                int diff = nums[i] - nums[prev] + 500;

                // Extend the arithmetic sequence ending at prev with same difference
                // or start a new sequence of length 2 (implied by +1 in return statement)
                dp[i][diff] = max(dp[i][diff], dp[prev][diff] + 1);

                // Update the maximum length found so far
                maxLength = max(maxLength, dp[i][diff]);
            }
        }
        // for(auto m{0}; m < n; ++m) {
        //     cout << m << "/" << nums[m] << ": ";
        //     for(auto i{0}; i < 1001; ++i)
        //         if (dp[m][i] != 0)
        //             cout << i << "/" << dp[m][i] << ",";
        //     cout << endl;
        // }

        // Add 1 because dp stores the count of transitions, not elements
        // A sequence with 0 transitions has 1 element, 1 transition has 2 elements, etc.
        return maxLength + 1;
    };

    // !!! WRONG !!!
    auto l2 = [&nums](){
        auto res{0};
        auto len{nums.size()};
        std::vector<std::map<int,int>> qty(len, std::map<int,int>());
        std::set<int> flt;
        auto diff{0};
        for (auto i{0}; i < len-1; ++i){
            flt.clear();
            for (auto k{i+1}; k < len; ++k){
                if (flt.count(nums[k])){
                }
                diff = nums[i]-nums[k];
                if (qty[i].count(diff) != 0){
                    if (qty[k].count(diff) == 0) qty[k][diff] = qty[i][diff]+1;
                    else qty[k][diff] = std::max(qty[i][diff], qty[k][diff]+1);
                } else {
                    if (qty[k].count(diff) == 0) qty[k][diff] = 1;
                }
                if (res < qty[k][diff]) res = qty[k][diff];
            }
        }
        ++res;

        return res;
    };

    auto l1 = [&nums](){
        auto res{0};
        auto len{nums.size()};
        std::vector<std::unordered_map<int,int>> qty(len, std::unordered_map<int,int>());
        auto diff{0};

        for (auto i{1}; i < len; ++i){
            for (auto k{0}; k < i; ++k){
                diff = nums[i]-nums[k] +500;
                qty[i][diff] = std::max(qty[i][diff], qty[k][diff]+1);
                if (res < qty[i][diff]) res = qty[i][diff];
            }
        }
        ++res;

        return res;
    };

    auto l3 = [&nums](){
        auto res{0};
        auto len{nums.size()};
        std::vector<std::array<int,1001>> qty(len, std::array<int,1001>());
        auto diff{0};

        for (auto i{1}; i < len; ++i){
            for (auto k{0}; k < i; ++k){
                diff = nums[i]-nums[k] +500;
                qty[i][diff] = std::max(qty[i][diff], qty[k][diff]+1);
                if (res < qty[i][diff]) res = qty[i][diff];
            }
        }
        // for(auto m{0}; m < len; ++m) {
        //     cout << m << "/" << nums[m] << ": ";
        //     for(auto i{0}; i < qty[m].size(); ++i)
        //         if (qty[m][i] != 0)
        //             cout << i << "/" << qty[m][i] << ",";
        //     cout << endl;
        // }

        ++res;
        // cout << "res=" << res << endl;

        return res;
    };

    if (mode == 1) return l1();         // time=55186 μs
    else if (mode == 2) return l2();    // time=53108 μs    // !!! WRONG !!!
    else if (mode == 3) return l3();    // time=2424 μs
    return l0();                        // time=2172 μs
}

void Solution::lc_1027_test() const {
    vector< pair<vector<int>, int> >
        data ={
            {{3,6,9,12}, 4},
            {{9,4,7,2,10}, 3},
            {{20,1,15,3,10,5,8}, 4},
            {{1, 1, 1, 1, 1}, 5},
            {{0,8,45,88,48,68,28,55,17,24}, 2},
            {{44,46,22,68,45,66,43,9,37,30,50,67,32,47,44,11,15,4,11,6,20,64,54,54,61,63,23,43,3,12,51,61,16,57,14,12,55,17,18,25,19,28,45,56,29,39,52,8,1,21,17,21,23,70,51,61,21,52,25,28}, 6},
            {{214,450,10,56,35,16,45,347,375,208,398,46,284,489,415,380,409,106,30,66,39,411,410,201,105,345,136,76,327,451,71,328,496,248,425,97,76,193,391,429,191,36,407,172,90,163,309,37,403,156,257,77,338,457,445,357,142,493,500,165,440,154,88,193,359,296,70,97,364,84,395,240,2,74,219,277,447,149,3,297,40,196,96,161,147,106,27,429,348,436,42,494,371,331,104,10,283,415,444,126,476,392,25,437,167,148,251,275,94,52,325,459,353,247,266,129,479,363,493,375,110,420,430,97,84,31,118,150,164,188,456,117,158,144,482,150,179,6,164,73,438,295,123,2,402,111,182,161,350,260,486,18,285,485,281,131,486,121,116,253,323,423,47,328,139,169,32,148,256,397,267,484,312,50,123,250,416,390,445,87,281,174,93,15,293,471,103,280,42,147,111,194,188,338,396,340,500,92,240,480,153,162,206,277,208,401,414,60,257,167,419,175,175,100,314,449,469,246,412,424,52,303,83,9,30,4,245,106,91,354,90,347,460,208,217,197,480,412,288,222,182,443,19,454,91,74,136,309,236,412,8,64,422,87,54,330,276,256,12,180,340,144,487,302,418,130,50,446,487,169,204,403,229,63,399,430,272,473,370,456,415,384,418,149,22,15,364,173,213,84,185,236,11,353,433,345,25,413,200,107,369,193,68,300,199,450,490,230,141,112,154,43,490,206,11,55,204,318,373,180,253,357,486,441,180,441,459,47,387,213,120,462,301,21,139,306,497,264,342,446,311,305,448,21,279,471,496,419,462,358,216,490,237,312,159,90,34,36,352,119,372,290,42,114,162,3,369,122,127,236,464,10,204,225,219,221,443,101,15,263,313,498,164,451,387,217,364,316,371,263,380,96,30,65,417,290,451,207,351,317,457,366,350,2,414,375,177,447,409,272,252,486,156,87,200,116,201,498,342,98,67,279,466,271,75,161,492,237,481,356,403,64,473,362,56,466,175,99,197,308,327,413,343,474,446,76,375,68,479,490,167,339,249,419,424,355,101,371,84,86,270,335,244,293,75,121,118,89,171,197,221,15,234,402,239,225,475,426,337,92,432,253,210,163,251,219,440,492,280,317,336,148,302,276,353,446,448,83,444,304,244,169,45,65,202,62,318,457,431,161,471,54,288,150,280,159,376,169,115,458,371,458,446,146,232,153,487}, 8},
            {{12,28,13,6,34,36,53,24,29,2,23,0,22,25,53,34,23,50,35,43,53,11,48,56,44,53,31,6,31,57,46,6,17,42,48,28,5,24,0,14,43,12,21,6,30,37,16,56,19,45,51,10,22,38,39,23,8,29,60,18}, 4},
            {{83,20,17,43,52,78,68,45}, 2},
            // {{}, },
                };

    for (auto m: {0,1,2, 3}){
    // for (auto m: {0,3}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_1027(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString(std::move(inp),20);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}

vector<int> Solution::lc_658(vector<int>& arr, int k, int x, int mode) const{
    vector<int> res;
    auto len{arr.size()};

    if (len <= k) return arr;
    if (x > arr[len-1]) res.insert(res.end(), std::next(arr.end(), 0 - k), arr.end());
    else if (x < arr[0]) res.insert(res.end(), arr.begin(), std::next(arr.begin(), k));
    else {
        auto i = std::min_element( arr.cbegin(), arr.cend(),
                                  [x](const auto a, const auto b){ return std::abs(a - x) < std::abs(b - x);} );
        auto lf{i}, tlf{i}, rt{std::next(i,1)};
        while (std::distance(lf,rt) < k){
            tlf = (lf != arr.begin()) ? std::next(lf,-1) : lf;
            if (rt != arr.end()
                && std::abs(*rt - x) < std::abs(*tlf - x)) {
                std::advance(rt, 1);
            } else if (lf == arr.begin()) std::advance(rt, 1); else lf = tlf;
        }
        res.insert(res.end(), lf, rt);
    }
    return res;
}


void Solution::lc_658_test() const{
    vector< tuple<vector<int>, int, int, vector<int> > > data =
        {
         { {1,2,3,4,5}, 4, 3, {1,2,3,4}},
        { {1,1,2,3,4,5}, 4, -1, {1,1,2,3}},
        { {1,2,3,4,5}, 3, 7, {3,4,5}},
        { {1,2,3,4,5}, 3, -7, {1,2,3}},
        { {1,2,3,4,5}, 6, 1, {1,2,3,4,5}},
        { {1,2,3,4,5,6,7,8,9}, 3, 3, {2,3,4}},
        { {1,10}, 1, 5, {1}},
        { {1,1,1,10,10,10}, 1, 9, {10}},
        { {1,1,1,10,10,10}, 2, 9, {10,10}},
        { {1,1,1,10,10,10}, 1, 1, {1}},
        { {0,0,1,2,3,3,4,7,7,8}, 3, 5, {3,3,4}},
        { {0,1,1,1,2,3,6,7,8,9}, 9, 4, {0, 1, 1, 1, 2, 3, 6, 7, 8}},
         };
    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            auto inp = get<0>(v);
            auto k = get<1>(v);
            auto x = get<2>(v);
            auto res = vkstd::toString(lc_658(inp, k, x, m));
            auto shouldBe = vkstd::toString(std::move(get<3>(v)));
            auto note = vkstd::toString(std::move(get<0>(v))) + ", k=" + std::to_string(k) + ", x=" + std::to_string(x);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


/*
    i=1 a=9 b=1 s=10 p=10 a*b=9 max=2147483638
    i=2 a=90 b=2 s=190 p=100 a*b=180 max=2147483467
    i=3 a=900 b=3 s=2890 p=1000 a*b=2700 max=2147480947
    i=4 a=9000 b=4 s=38890 p=10000 a*b=36000 max=2147447647
    i=5 a=90000 b=5 s=488890 p=100000 a*b=450000 max=2147033647
    i=6 a=900000 b=6 s=5888890 p=1000000 a*b=5400000 max=2142083647
    i=7 a=9000000 b=7 s=68888890 p=10000000 a*b=63000000 max=2084483647
    i=8 a=90000000 b=8 s=788888890 p=100000000 a*b=720000000 max=1427483647
    i=9 a=900000000 b=9 s=298954298 p=1000000000 a*b=-489934592 max=-1657549057
    i=10 a=410065408 b=10 s=104641082 p=1410065408 a*b=-194313216 max=-1953170433
    i=11 a=-194313216 b=11 s=-2032804294 p=1215752192 a*b=-2137445376 max=-10038273
*/
int Solution::lc_400(int n, int mode) const{
    if (n > std::numeric_limits<int>::max()) return 0;
    auto lranges = [](){
        auto b{1}, i{1}, p{10};
        long long a{9}, s{10*b};
        while (true && s < std::numeric_limits<int>::max()){
            long long l = a * b;
            cout << "i="<< i << " a=" << a << " b="
            << b << " s=" << s  << " p=" << p
            << " a*b=" << l << " max=" << INT_MAX - a*b << endl;
            if (l > INT_MAX) break;
            a *= 10; p *=10;
            ++b; ++i;
            s += a * b;
        }
        return;
    };
    auto lalien = [n]() mutable {
        // k represents the number of digits in current range (1-digit, 2-digit, 3-digit numbers, etc.)
        int digitsPerNumber = 1;

        // cnt represents the count of numbers in current range
        // 1-digit: 9 numbers (1-9)
        // 2-digit: 90 numbers (10-99)
        // 3-digit: 900 numbers (100-999)
        int countInRange = 9;

        // Find which range the nth digit belongs to
        // Use 1ll to prevent integer overflow during multiplication
        while (1ll * digitsPerNumber * countInRange < n) {
            // Subtract the total digits in current range from n
            n -= digitsPerNumber * countInRange;

            // Move to next range (e.g., from 1-digit to 2-digit numbers)
            ++digitsPerNumber;
            countInRange *= 10;
        }

        // Calculate the actual number that contains the nth digit
        // pow(10, k-1) gives the starting number of current range
        // (n-1)/k gives how many numbers to skip from the start
        int targetNumber = pow(10, digitsPerNumber - 1) + (n - 1) / digitsPerNumber;

        // Calculate which digit position within the target number
        // (n-1) % k gives the 0-indexed position
        int digitIndex = (n - 1) % digitsPerNumber;

        // Convert number to string and extract the digit at the calculated position
        return to_string(targetNumber)[digitIndex] - '0';
    };

    auto l1 = [n]() mutable {
        auto lres{n};
        // auto k{n};
        if (n < 10) {
            return lres;
        } else if (n < 190) {
            n -= 10;
            auto num = 10 + n/2;
            // cout << " k=" << k << " num=" << num << endl;
            lres = std::stoi(std::to_string(num).substr(n%2,1));
        } else if (n < 2890){
            n -= 190;
            auto num = 1e2 + n/3;
            // cout << " k=" << k << " num=" << num << endl;
            lres = std::to_string(num)[n%3] - '0';
        } else if (n < 38890){
            n -= 2890;
            auto num = 1e3 + n/4;
            lres = std::to_string(num)[n%4] - '0';
        } else if (n < 488890){
            n -= 38890;
            auto num = 1e4 + n/5;
            lres = std::to_string(num)[n%5] - '0';
        } else if (n < 5888890){
            n -= 488890;
            auto num = 1e5 + n/6;
            lres = std::to_string(num)[n%6] - '0';
        } else if (n < 68888890){
            n -= 5888890;
            auto num = 1e6 + n/7;
            lres = std::to_string(num)[n%7] - '0';
        } else if (n < 788888890){
            n -= 68888890;
            auto num = 1e7 + n/8;
            lres = std::to_string(num)[n%8] - '0';
        } else if (n < 2e31 - 1){
            n -= 788888890;
            auto num = 1e8 + n/9;
            lres = std::to_string(num)[n%9] - '0';
        } else lres = 0;

        return lres;
    };

    // lranges();
    if (mode == 1) return l1();
    return lalien();
}

void Solution::lc_400_test() const {
    vector< pair<int, int> >
        data ={
                {3, 3},
                // {11, 0},
            // {120, 6}, {121, 5}, {122, 6}, {123, 6},
            // {190, 1}, {191, 0}, {192, 0}, {1120, 4}, {1121, 1}, {1122, 0}, {1123, 4},
            // {2120, 4}, {2121, 3}, {2122, 7}, {2123, 4}, {2889, 9},
            // {2890, 1}, {2891, 0}, {2892, 0}, {4120, 0}, {4121, 7}, {4122, 1}, {4123, 3},
            {788888890, 1}, {999999999, 9}, {1234567890, 8}, {1765432123, 8}, {2123456789, 4}, {888888888, 0}, {2e31-1, 2},
            // {, },
                };
    // vector<int> tmp(5000, 1);
    // std::uniform_int_distribution<int> ud(1, 120);
    // std::minstd_rand rnd{std::random_device{}()};
    // for (auto k{0}; k < tmp.size(); ++k) tmp[k] = ud(rnd);
    // data.push_back(std::make_pair(std::move(tmp), 0)) ;

    // vector<int> tmp2(5000);
    // std::iota(std::begin(tmp2), std::end(tmp2), 1000);
    // data.push_back(std::make_pair(std::move(tmp2), 0)) ;

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_400(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = std::to_string(inp);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_825(vector<int>& ages, int mode) const{
    auto v2 = ages;

    auto lalien = [&ages](){
        const int MAX_AGE = 121;
        vector<int> ageCount(MAX_AGE);

        // Count the frequency of each age
        for (int age : ages) {
            ++ageCount[age];
        }

        int totalRequests = 0;

        // Check all possible age pairs
        for (int ageX = 1; ageX < MAX_AGE; ++ageX) {
            for (int ageY = 1; ageY < MAX_AGE; ++ageY) {
                // Check if person X (with ageX) can send friend request to person Y (with ageY)
                // Person X will NOT send a friend request to person Y if any of the following is true:
                // 1. ageY <= 0.5 * ageX + 7
                // 2. ageY > ageX
                // 3. ageY > 100 && ageX < 100

                bool condition1 = ageY <= 0.5 * ageX + 7;
                bool condition2 = ageY > ageX;
                bool condition3 = ageY > 100 && ageX < 100;

                // If none of the conditions are true, X can send request to Y
                if (!condition1 && !condition2 && !condition3) {
                    // Calculate the number of friend requests
                    // Each person with ageX can send requests to all people with ageY
                    if (ageX == ageY) {
                        // If ages are the same, each person can send to others but not themselves
                        // So we subtract 1 from the count for self-request
                        totalRequests += ageCount[ageX] * (ageCount[ageY] - 1);
                    } else {
                        // Different ages: all people with ageX can send to all people with ageY
                        totalRequests += ageCount[ageX] * ageCount[ageY];
                    }
                }
            }
        }

        return totalRequests;
    };

    auto l2 = [&v2](){
        auto lres{0};
        std::sort(v2.begin(), v2.end());
        auto k{0};
        for (auto i{0}; i < v2.size(); ++i){
            k = i;
            for(; k < v2.size() && v2[k] == v2[i]; ++k){}
            if (k < v2.size()) ++k;
            for (; k > 0; --k){
                if (k-1 == i) continue;
                if (
                    v2[k-1] <= ((v2[i] >>1)+7)
                    // ages[k] <= dict[i]
                    || v2[k-1] > v2[i]
                    || (v2[k-1] > 100 && v2[i] < 100)
                    ) continue;
                ++lres;
            }
        }

        return lres;
    };

    auto l1 = [&ages](){
        auto lres{0};
        // vector<int> dict(ages.size(),0);
        // for (auto i{0}; i < ages.size(); ++i)
        //     dict[i] = (ages[i] >>1)+7;
        for (auto i{0}; i < ages.size(); ++i){
            for (auto k{0}; k < ages.size(); ++k){
                if (k == i) continue;
                // cout << " i=" << i << " k=" << k << " ai=" << ages[i]  << " ak=" << ages[k] << " di=" << dict[i] << endl;
                if (
                    ages[k] <= ((ages[i] >>1)+7)
                    // ages[k] <= dict[i]
                    || ages[k] > ages[i]
                    || (ages[k] > 100 && ages[i] < 100)
                    ) continue;
                ++lres;
            }
        }

        // cout << "dict ";
        // for (const auto& v: dict) cout << v << " ";
        // cout << endl;
        return lres;
    };

    auto l3 = [&ages](){
        auto lres{0};
        std::map<int, int> dict;
        for (const auto& v: ages) ++dict[v];
        for (const auto& x: dict){
            if (!(((x.first >>1)+7) < x.first)) continue;
            auto left = dict.lower_bound((x.first >>1)+8);
            // if (left == dict.end()) left = dict.begin();
            auto right = dict.lower_bound(x.first);
            if (right != dict.end()) std::advance(right,1);
            for (auto y = left;  y != right; std::advance(y,1)){
            // for (const auto& y: dict){
                if (!(
                    // || y->first <= ((x.first >>1)+7)
                    // || y->first > x.first
                    // ||
                  (y->first > 100 && x.first < 100)
                        )) lres += x.second * (y->second - (x.first == y->first ? 1 : 0));
            }
        }
        // cout << " d.size=" << dict.size() << endl;
        return lres;
    };

    if (mode == 1) return l1();
    else if (mode == 2) return l2();
    else if (mode == 3) return l3();
    return lalien();

}

void Solution::lc_825_test() const {
    vector< pair<vector<int>, int> >
        data ={
            {{16,16}, 2},
            {{16,17,18}, 2},
            {{20,30,100,110,120}, 3},
            {{73,106,39,6,26,15,30,100,71,35,46,112,6,60,110}, 29},
            {{54,23,102,90,40,74,112,74,76,21}, 22},
            {{10}, 0},
            // {{}, },
        };
    vector<int> tmp(5000, 1);
    std::uniform_int_distribution<int> ud(1, 120);
    std::minstd_rand rnd{std::random_device{}()};
    for (auto k{0}; k < tmp.size(); ++k) tmp[k] = ud(rnd);
    data.push_back(std::make_pair(std::move(tmp), 0)) ;

    // vector<int> tmp2(5000);
    // std::iota(std::begin(tmp2), std::end(tmp2), 1000);
    // data.push_back(std::make_pair(std::move(tmp2), 0)) ;

    for (auto m: {0,1,2,3}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_825(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString(std::move(v.first),20);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_792(string s, vector<string>& words, int mode) const{
    if (!(s.size())) return 0;
    auto res{0};
    std::unordered_map<char,vector<int> > dict;
    for ( auto i{0}; i < s.size(); ++i)  dict[s[i]].push_back(i);
    auto cnt{0};
    for (const auto& v: words){
        cnt = 0;
        // auto i{0};
        auto ok{true};
        for (auto i{0}; i < v.size(); ++i){
            auto f = dict.find(v[i]);
            if (f == dict.end()) {ok = false; break;}
            auto lb = std::lower_bound((f->second).begin(), (f->second).end(), cnt);
            // cout << "v=" << v << " cnt=" << cnt << " lb=" << *lb << endl;
            if (lb == (f->second).end()) {ok = false; break;}
            else cnt = *lb +1;
        }
        if (ok) ++res;
    }

    // cout << "dict ";
    // for (const auto& v: dict) cout << v.first << "/" << vkstd::toString(v.second) << " ";
    // cout << endl;

    return res;

}

void Solution::lc_792_test() const{
    vector< tuple<string, vector<string>, int > > data =
        {
            { "abcde", {"a","bb","acd","ace"}, 3},
            { "dsahjpjauf", {"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"}, 2},
            { "aaaaa", {"a", "aa", "aaa", "aaaa", "aaaaa", "b"}, 5},
            { "abcde", {"f", "g", "h", "i", "j"}, 0},
        { "abababab", {"ab", "ba", "aaa", "bbb", "abab", "baba"}, 6},
        { "x", {"x", "y", "z", "xx", "xy"}, 1},
        { "abcdefghij", {"abcdefghij", "abc", "ghij", "abcd", "mnop"}, 4},
        { "rwpddkvbnnuglnagtvamxkqtwhqgwbqgfbvgkwyuqkdwhzudsxvjubjgloeofnpjqlkdsqvruvabjrikfwronbrdyyjnakstqjac"
         , {"wpddkvbnn","lnagtva","kvbnnuglnagtvamxkqtwhqgwbqgfbvgkwyuqkdwhzudsxvju","rwpddkvbnnugln","gloeofnpjqlkdsqvruvabjrikfwronbrdyyj","vbgeinupkvgmgxeaaiuiyojmoqkahwvbpwugdainxciedbdkos","mspuhbykmmumtveoighlcgpcapzczomshiblnvhjzqjlfkpina","rgmliajkiknongrofpugfgajedxicdhxinzjakwnifvxwlokip","fhepktaipapyrbylskxddypwmuuxyoivcewzrdwwlrlhqwzikq","qatithxifaaiwyszlkgoljzkkweqkjjzvymedvclfxwcezqebx"}
         , 5},
        // { "", {}, 3},
         };
    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            auto inp = get<0>(v);
            auto vec = get<1>(v);
            auto res = std::to_string(lc_792(inp, vec, m));
            auto shouldBe = std::to_string(get<2>(v));
            auto note = inp + ":" + vkstd::toString(vec);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}

int Solution::lc_300(vector<int>& nums, int mode) const{

    auto l0 = [&nums](){
        size_t n = nums.size();

        // dp[i] represents the length of the longest increasing subsequence
        // ending at index i
        vector<int> dp(n, 1);

        // Iterate through each position as potential end of subsequence
        for (int i = 1; i < n; ++i) {
            // Check all previous elements that could form an increasing subsequence
            for (int j = 0; j < i; ++j) {
                // If current element is greater than previous element,
                // we can extend the subsequence ending at j
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    // dp[i] =  dp[j] + 1;
                }
            }
            // cout << vkstd::toString(dp) << endl;
        }

        // Return the maximum length among all possible ending positions
        return *max_element(dp.begin(), dp.end());
    };

    auto l1 = [&nums](){
        // auto res{0}, tres{0};
        size_t len = nums.size();
        vector<int> res(len,1);
        // nums.push_back(1e4 + 1);
        for (auto i{1}; i < len; ++i){
            for (auto k{0}; k < i; ++k){
                if (nums[k] < nums[i]) res[i] = max(res[i], res[k]+1);
            }
            // cout << " len=" << len << " " << vkstd::toString(res) << endl;
        }
        return *max_element(res.begin(), res.end());
    };

    auto l2 = [&nums](){
        auto res{0}, tres{0};
        auto len{nums.size()};
        nums.push_back(1e4 + 1);
        for (auto i{len}; i > 0; --i){
            if (nums[i-1] < nums[i]) {
                ++tres;
            } else {
                if (res < tres) res = tres;
                tres = 0;
            }
        }
        return res;
    };

    if (mode == 1) return l1();
    return l0();
}

void Solution::lc_300_test() const {
    vector< pair<vector<int>, int> >
        data ={
                {{10,9,2,5,3,7,101,18}, 4},
                {{0,1,0,3,2,3}, 4},
                {{7,7,7,7,7,7,7}, 1},
            {{2,5,3,7,101,18,1,2,3}, 4},
            // {{}, },
                };
    // vector<int> tmp;
    // std::uniform_int_distribution<int> ud(1000000, 9999999);
    // std::minstd_rand rnd{std::random_device{}()};
    // for (auto k{0}; k < 5000; ++k) tmp.emplace_back(ud(rnd));
    // data.push_back(std::make_pair(std::move(tmp), 0)) ;

    // vector<int> tmp2(5000);
    // std::iota(std::begin(tmp2), std::end(tmp2), 40000);
    // data.push_back(std::make_pair(std::move(tmp2), 43750000)) ;

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_300(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString(v.first);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}

int Solution::lc_209(int target, vector<int>& nums, int mode) const{
    vector<int> acum(nums.size()+1,0);
    std::partial_sum(nums.begin(), nums.end(), std::next(acum.begin(),1));


    // cout << "000 res=" << res << endl;

    auto l1 = [&acum](auto t){
        auto lres{acum.size()};
        for (auto i{acum.begin()}; i != acum.end(); std::advance(i,1)){
            auto lb = std::lower_bound(i, acum.end(), t + (*i));
            auto dist = ((lb == acum.end()) ? acum.size() : std::distance(i,lb));
            // cout << "t=" << target + acum[i]
            //      << " d=" << dist
            //      << " lb=" << *lb << endl;
            if (dist < lres) lres = dist;
        }
        return lres < acum.size() ? lres : 0;
    };

    auto l2 = [&acum](auto t){
        auto lres{acum.size()};
        for (auto i{0}; i < acum.size(); ++i){
            auto lb = std::lower_bound(std::next(acum.begin(),i), acum.end(), t + acum[i]);
            auto dist = ((lb == acum.end()) ? acum.size() : std::distance(acum.begin(),lb) - i);
            // cout << "t=" << target + acum[i]
            //      << " d=" << dist
            //      << " lb=" << *lb << endl;
            if (dist < lres) lres = dist;
        }
        return lres < acum.size() ? lres : 0;
    };

    auto lfastest = [&nums] (auto t) {
        int left = 0;
        int right = 0;
        int sumo = 00;
        int ans = INT_MAX;
        while(right < nums.size()){
            sumo += nums[right];
            while(sumo >= t){
                ans = std::min(ans, right-left+1);
                sumo -= nums[left];
                left += 1;
            }
            right += 1;
        }
        return ans == INT_MAX ? 0 : ans;
    };
    // cout << "555 res=" << res << endl;

    // cout<< vkstd::toString(nums) << " " << vkstd::toString(acum)
    //      << endl;
    if (mode == 1) return static_cast<int>(l2(target));
    else if (mode == 2) return lfastest(target);
    return static_cast<int>(l1(target));
}

void Solution::lc_209_test() const{
    vector< tuple<vector<int>, int, int > > data =
        {
            { {2,3,1,2,4,3}, 7, 2},
            { {1,4,4}, 4, 1},
            { {1,1,1,1,1,1,1,1}, 11, 0},
        };
    for (auto m: {0,1,2}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            auto inp = get<0>(v);
            auto targ = get<1>(v);
            auto res = std::to_string(lc_209(targ, inp, m));
            auto shouldBe = std::to_string(get<2>(v));
            auto note = std::to_string(targ) + ":" + vkstd::toString(inp);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


long long Solution::lc_3153(vector<int>& nums, int mode) const{

    auto pattern = [&nums](){
        size_t arraySize = nums.size();
        // Calculate the number of digits in the first number
        int digitCount = floor(log10(nums[0])) + 1;

        // Array to count frequency of each digit (0-9) at current position
        int digitFrequency[10];
        long long totalDifferences = 0;

        // Process each digit position from right to left
        for (int position = 0; position < digitCount; ++position) {
            // Reset frequency array for current digit position
            memset(digitFrequency, 0, sizeof(digitFrequency));

            // Count frequency of each digit at current position
            for (int i = 0; i < arraySize; ++i) {
                int currentDigit = nums[i] % 10;  // Extract rightmost digit
                ++digitFrequency[currentDigit];
                nums[i] /= 10;  // Remove the processed digit
            }

            // Calculate contribution to total differences for this position
            // For each digit value, count pairs with different digits
            for(const auto v : digitFrequency) cout << " v=" << v;
            cout << endl;
            for (int digit = 0; digit < 10; ++digit) {
                // digitFrequency[digit] numbers have this digit
                // (arraySize - digitFrequency[digit]) numbers have different digits
                // Each pair contributes 1 to the difference count
                totalDifferences += 1LL * digitFrequency[digit] * (arraySize - digitFrequency[digit]);
            }
        }

        // Divide by 2 because each pair is counted twice
        // (once for each number in the pair)
        return totalDifferences / 2;
    };

    auto lmb = [&nums](){
        long long lres{0};
        auto len{nums.size()};
        if (!(len)) return lres;

        auto nlen{0};
        auto tmp{nums[0]};
        for (; tmp > 0; ++nlen, tmp /=10){}
        // int nlen = floor(log10(nums[0])) + 1;
        // cout << "nlen=" << nlen << " n=" << nums[0] << endl;
        vector<int> freq(10,0);
        for (auto i{0}; i < nlen; ++i){
            std::fill(freq.begin(), freq.end(),0);
            for (auto k{0}; k < len; ++k){
                // dig = nums[k] % 10;
                ++freq[nums[k] % 10];
                nums[k] /= 10;
            }
            // for(const auto v : freq) cout << " v=" << v;
            // cout << endl;
            for(const auto v : freq) lres += v * (len - v);
        }

        return lres / 2;
    };

    auto lmb2 = [&nums](){
        long long lres{0};
        auto len{nums.size()};
        if (!(len)) return lres;

        auto nlen{0};
        auto tmp{nums[0]};
        for (; tmp > 0; ++nlen, tmp /=10){}
        // int nlen = floor(log10(nums[0])) + 1;
        // cout << "nlen=" << nlen << " n=" << nums[0] << endl;
        vector<int> freq(10,0);
        for (auto i{0}; i < nlen; ++i){
            std::fill(freq.begin(), freq.end(),0);
            for (auto k{nums.begin()}; k != nums.end(); std::advance(k,1)){
                ++freq[*k % 10];
                *k /= 10;
            }
            // for(const auto v : freq) lres += v * (len - v);
            lres += std::reduce(freq.cbegin(), freq.cend(), 0, [len](auto res, auto v){return res + v * (len - v);});
            // lres += std::accumulate(freq.cbegin(), freq.cend(), 0, [len](auto res, auto v){return res + v * (len - v);});
        }

        return lres / 2;
    };

    if (mode == 1) return lmb();
    else if (mode == 2) return lmb2();
    return pattern();
}

void Solution::lc_3153_test() const {
    vector< pair<vector<int>, int> >
        data ={
                {{13,23,12}, 4},
                {{10,10,10,10}, 0},
                // {{}, },
                };
    vector<int> tmp;
    std::uniform_int_distribution<int> ud(1000000, 9999999);
    std::minstd_rand rnd{std::random_device{}()};
    for (auto k{0}; k < 5000; ++k) tmp.emplace_back(ud(rnd));
    data.push_back(std::make_pair(std::move(tmp), 0)) ;

    vector<int> tmp2(5000);
    std::iota(std::begin(tmp2), std::end(tmp2), 40000);
    data.push_back(std::make_pair(std::move(tmp2), 43750000)) ;

    for (auto m: {0,1,2}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_3153(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString(v.first);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_477(vector<int>& nums, int mode) const{

    // from https://algo.monster/liteproblems/477
    auto pattern = [&nums](){
        int totalDistance = 0;
        size_t arraySize = nums.size();

        // Iterate through each bit position (0 to 31 for 32-bit integers)
        for (int bitPosition = 0; bitPosition < 32; ++bitPosition) {
            int onesCount = 0;

            // Count how many numbers have a 1 at the current bit position
            for (int number : nums) {
                // Right shift by bitPosition and check if the least significant bit is 1
                onesCount += (number >> bitPosition) & 1;
            }

            // Calculate the number of 0s at this bit position
            int zerosCount = static_cast<int>(arraySize - onesCount);

            // For this bit position, the Hamming distance contribution is:
            // (number of 1s) * (number of 0s)
            // This represents all pairs where one has 1 and the other has 0
            totalDistance += onesCount * zerosCount;
        }

        return totalDistance;
    };

    auto lmb = [&nums](){
        auto lres{0};
        auto len{nums.size()};
        auto qty{0};
        for (auto bit{1}, i{0}; i < 32; ++i){
            qty = 0;
            for (const auto v: nums) {
                if ((v & bit) == bit) ++qty;
            }
            lres += qty * (len - qty);
            bit <<= 1;
        }
        return lres;
    };

    if (mode ==1) return lmb();
    return pattern();
}

void Solution::lc_477_test() const {
    vector< pair<vector<int>, int> >
        data ={
            {{4,14,2}, 6},
            {{4,14,4}, 4},
            // {{}, },
                };
    vector<int> tmp;
    std::uniform_int_distribution<int> ud(0, 1000000000);
    std::minstd_rand rnd{std::random_device{}()};
    for (auto k{0}; k < 5000; ++k) tmp.emplace_back(ud(rnd));
    data.push_back(std::make_pair(std::move(tmp), 0)) ;

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_477(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString(inp);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_397(int n, int mode) const{

    auto lmb = [](auto v){
        auto lres{0};
        auto tmp{1}, q{0};
        while (tmp < v){
            tmp <<=1;
            ++lres;
        }
        if (tmp > v){
            auto diff = tmp - v;
            tmp >>=1;
            if (diff > (v - tmp)) diff = v - tmp -1;
            lres += diff;
        }

        return lres;
    };

    auto lmb2 = [](auto v){
        auto lres{0};
        long vn{v};
        while (vn > 1){
            // cout << " n=" << v ;
            if (vn & 1) {
                if ( vn > 3 && ((vn & 3) == 3)) ++vn;
                else --vn;
                ++lres;
                // cout << " n=" << v ;
            }
            if (vn == 1) break;
            vn >>=1;
            ++lres;
        }
// cout << endl;
        return lres;
    };

    auto pattern = [](auto v){
        int steps = 0;
        long num = v;  // Use long to avoid overflow when incrementing INT_MAX

        while (num != 1) {
            // If num is even, divide by 2 (right shift by 1)
            // cout << " n=" << num;
            if ((num & 1) == 0) {
                num >>= 1;
            }
            // If num is odd
            else {
                // Special case: for 3, always decrement (3 -> 2 -> 1 is optimal)
                // For other numbers ending in binary '11', increment is better
                // This is because adding 1 to '...11' gives '...00', allowing more divisions
                if (num != 3 && (num & 3) == 3) {
                    ++num;
                }
                // For numbers ending in binary '01' or when num is 3, decrement
                else {
                    --num;
                }
            }
            ++steps;
        }
        // cout << endl;

        return steps;    };

    if (mode == 1) return lmb2(n);
    else if (mode == 2) return lmb(n);
    return pattern(n);
}


void Solution::lc_397_test() const {
    vector< pair<int, int> >
        data ={
            {8, 3},
            {7, 4},
            {4, 2},
            {1, 0},
            {10000, 16},
            {25, 6},
            {20, 5},
            {15, 5},
            {12, 4},
                {1234, 14},
                };

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_397(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = std::to_string(inp);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}

int Solution::lc_318(vector<string>& words, int mode) const{

    // std::sort(words.begin(), words.end());
    auto lmb = [&words](){
        size_t lres{0};
        const auto len{words.size()};
        auto k{0}, i{0};
        for (auto w1{0}; w1 < len; ++w1){
            for (auto w2{w1+1}; w2 < len; ++w2){
                i = 0;
                for ( ; i < words[w1].size(); ++i) {
                    k = 0;
                    for ( ; k < words[w2].size(); ++k) {
                        // cout << " w1=" << words[w1] << " l1=" << words[w1][i]
                        //      << " w2=" << words[w2] << " l2=" << words[w2][k]
                        //      << endl;
                        if (!(words[w1][i] ^ words[w2][k])) break;
                    }
                    // cout << " w2s=" << words[w2].size() << " k=" << k << endl;
                    if (k != words[w2].size()) break;
                }
                if (i == words[w1].size()){
                    if (lres < (words[w1].size() * words[w2].size())) lres = words[w1].size() * words[w2].size();
                }
            }
        }
        return lres;
    };

    auto lmb2 = [&words](){
        size_t lres{0};
        const auto len{words.size()};
        vector<int> mask(len, 0);
        std::transform(words.cbegin(), words.cend(), mask.begin(),
                       [](const auto w){
                           auto m{0};
                           for (auto i{0}; i < w.size(); ++i){
                               m |= (1 << (w[i] - 'a'));
                            }
                           return m;
        });
        for (auto w1{0}; w1 < len; ++w1){
            for (auto w2{w1+1}; w2 < len; ++w2){
                if (mask[w1] & mask[w2]) continue;
                if (lres < (words[w1].size() * words[w2].size())) lres = (words[w1].size() * words[w2].size());
            }
        }

        return lres;
    };

    if (mode == 1) return static_cast<int>(lmb());
    return static_cast<int>(lmb2());
}

void Solution::lc_318_test() const {
    vector< pair<vector<string>,int> >
        data ={
            {{"abcw","baz","foo","bar","xtfn","abcdef"}, 16},
            {{"a","ab","abc","d","cd","bcd","abcd"}, 4},
            {{"a","aa","aaa","aaaa"}, 0},
            {{"asdf", "zxc"}, 12},
            {{"as", "dqswer"}, 0},
//             {{
// "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh","yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz","nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn","pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm","vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd","kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg","eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii","rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr","uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu"
// }, 10000},
            // {{}, },
                };
    vector<string> tmp;
    string str{""};
    std::uniform_int_distribution<int> ud(97, 122);
    std::minstd_rand rnd{std::random_device{}()};
    for (auto k{0}; k < 500; ++k){
        str = "";
        for (auto i{0}; i < 500; ++i) {
            str += string(1, ud(rnd));
        }
        tmp.emplace_back(std::move(str));
    }
    // cout << "str="<< str << endl;
    data.push_back(std::make_pair(std::move(tmp), 0)) ;
    // std::transform(tmp.cbegin(), tmp.cend(), tmp.begin(),
    //                [](auto v){
    //                    std::uniform_int_distribution<int> ud(97, 122);
    //                    std::minstd_rand rnd{std::random_device{}()};
    //                    return ud(rnd);
    //                });

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_318(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString( inp );
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_1191(vector<int>& arr, int k, int mode) const{
    const int MOD{1000000000 + 7};
    // alien is from https://algo.monster/liteproblems/1191
    auto alien = [&arr, &MOD](auto k){
        long cumulativeSum = 0;
        long maxPrefixSum = 0;  // Maximum sum from start to any position
        long minPrefixSum = 0;  // Minimum sum from start to any position
        long maxSubarraySum = 0;  // Maximum subarray sum using Kadane's algorithm

        // Single pass through the array to calculate all necessary values
        for (int num : arr) {
            cumulativeSum += num;

            // Update maximum prefix sum (best sum starting from index 0)
            maxPrefixSum = max(maxPrefixSum, cumulativeSum);

            // Update minimum prefix sum (used to find maximum suffix)
            minPrefixSum = min(minPrefixSum, cumulativeSum);

            // Update maximum subarray sum (current sum minus minimum seen so far)
            maxSubarraySum = max(maxSubarraySum, cumulativeSum - minPrefixSum);
        }

        // Start with the maximum subarray sum from single array
        long result = maxSubarraySum;
        // const int MOD = 1e9 + 7;

        // If k = 1, we only have one array, return the maximum subarray sum
        if (k == 1) {
            return result % MOD;
        }

        // Calculate maximum suffix sum (from any position to end)
        long maxSuffixSum = cumulativeSum - minPrefixSum;

        // Consider joining suffix of first array with prefix of second array
        result = max(result, maxPrefixSum + maxSuffixSum);

        // If total array sum is positive, we can include middle arrays
        if (cumulativeSum > 0) {
            // Use prefix of first array + (k-2) complete middle arrays + suffix of last array
            // cout << "ALIEN " << " res="<<result << " maxPre="<<maxPrefixSum << " total=" << cumulativeSum << " suf=" << maxSuffixSum << endl;
            result = max(result, maxPrefixSum + (k - 2) * cumulativeSum + maxSuffixSum);
        }

        return result % MOD;

    };

    // fastest
    auto lfun = [&arr, &MOD](auto k){

        long lres{0}, total{0};
        long maxPre{0}, minPre{0};

        for (auto v : arr) {
            total += v;
            if (maxPre < total) maxPre = total;
            if (minPre > total) minPre = total;
            if (lres < total-minPre) lres = total-minPre;
        }
        // cout << "111 "
        //      << " total=" << total
        //      << " maxP=" << maxPre
        //      << " minP=" << minPre
        //      << " lres=" << lres
        //      << endl;
        if (k == 1) return lres % MOD;

        lres = max(lres, maxPre + total - minPre);
        if (total > 0) lres = max(lres, maxPre + total - minPre + (k-2) * total);
        return lres % MOD;
    };

    // double walking
    auto lkadane = [&arr, &MOD](auto k){
        auto len = arr.size();
        // auto lres{0};
        if (len == 0) return 0;
        long cur{arr[0]}, glo{arr[0]}, total{arr[0]};
        auto qty = (k > 1 ? 2 : 1);
        for(auto i=1; i < qty * len; ++i){
            total += arr[i % len];
            cur = (cur + arr[i % len] > arr[i % len] ? cur + arr[i % len] : arr[i % len]);
            if (glo < cur) glo = cur;
        }
        // cout << "BB tot"<< total << " glo=" << glo << endl;
        if ( qty == 2 ) total >>=1;
        // cout << "AA tot"<< total << endl;
        if ((k < 3) || (total <= 0)) return glo < 0 ? 0 : static_cast<int>(glo % MOD);

        return glo < 0 ? 0 : static_cast<int>((glo + (k-2) * total) % MOD);

    };

    if (mode == 1) return static_cast<int>(lfun(k));
    else if (mode == 2) return static_cast<int>(lkadane(k));
    return static_cast<int>(alien(k));
}

void Solution::lc_1191_test() const {
    vector< tuple<vector<int>, int, int > >
        data = {
            {{1,2}, 3, 9},
            {{1,-2,1}, 5, 2},
            {{-1,-2}, 7, 0},
            {{1,2,3,4,5,-20,4,3}, 3, 24},
            {{1,2,3,4,5,-20,4,3}, 1, 15},
                // {{}, 0, 0},
                };
    vector<int> tmp2(100000,10000);
    tuple<vector<int>, int, int > tt2{std::move(tmp2), 100000, 999300007};
    data.push_back(std::move(tt2)) ;
    vector<int> tmp(10000,0);
    std::transform(tmp.cbegin(), tmp.cend(), tmp.begin(),
                   [](auto v){
                       std::uniform_int_distribution<int> ud(0, 10000);
        std::minstd_rand rnd{std::random_device{}()};
                    return ud(rnd);
    });
    tuple<vector<int>, int, int > tt{std::move(tmp), 100000, 1};
    data.push_back(std::move(tt)) ;

    for (auto m: {0,1,2}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = get<0>(v);
            auto qty = get<1>(v);
            auto res = std::to_string(lc_1191(inp, qty, m));
            auto shouldBe = std::to_string(get<2>(v));
            auto note = vkstd::toString(inp) + "*" + std::to_string(qty);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

int Solution::lc_2266(string pressedKeys, int mode) const {

    if (pressedKeys.size() == 0) return 0; // don't follow the rules but anyway
    if (pressedKeys.size() == 1) return 1;
    auto len = pressedKeys.size();

    constexpr auto MOD{1000000007};     //{1e9+7};      //
    auto res{1};
    std::vector<int> ways(++len, 0);
    ways[0] = 1;

    for (int i = 1; i < len; ++i) {
        ways[i] = ways[i-1] % MOD;
        if (i > 1 && (pressedKeys[i-1] - '0') == (pressedKeys[i-2] - '0')){
            ways[i] = (ways[i] + ways[i-2]) % MOD;
            if (i > 2 && (pressedKeys[i-2] - '0') == (pressedKeys[i-3] - '0')){
                ways[i] = (ways[i] + ways[i-3]) % MOD;
                if (i > 3 && (pressedKeys[i-3] - '0') == (pressedKeys[i-4] - '0') && (pressedKeys[i-1] == '7' || pressedKeys[i-1] == '9')){
                    ways[i] = (ways[i] + ways[i-4]) % MOD;
                }
            }
        }
    }
    // for(const auto &v: ways) cout << v << " ";
    // cout << endl;

    return ways[len-1];
}

void Solution::lc_2266_test() const {
    vector< pair<string,int> >
        data ={
                {"22233", 8},
            {"2", 1},
            {"222", 4},
            {"23456789", 1},
            {"2222", 7},
            {"99999999", 108},
            {"777",4},
            {"7777",8},
            {"222222222222222222222222222222222222", 82876089},
            {"444479999555588866", 3136},
            // {"", 0},
                };

    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_2266(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = inp;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_91(string s, int mode) const{

    if (s.size() == 0) return 0; // don't follow the rules but anyway

    // slow / TLE
    auto ldfs = [&s](auto&& self, auto i, auto deep=0){
        cout << "l 000 "
             << " deep=" << std::to_string(deep)
             << " i=" << std::to_string(i)
             << endl;
        auto dd{deep};  // for testing
        ++deep;
        if (dd > 10) return 0;

        auto lres{0};
        if (i == s.size()) return 1;

        auto dig1 = s[i] - '0';
        auto dig2 = (i+1 < s.size() ? 10 * dig1 + (s[i+1] - '0') : 0);
        if (dig1 != 0) lres += self(self, i+1, deep);
        if ( dig2 > 9 && dig2 < 27) lres += self(self, i+2, deep);

        return lres;
    };

    // BAD / ERROR
    auto l2 = [&s](){

        auto lres{1};
        auto ok1{false}, ok2{false};
        auto ch1{0}, ch2{0};
        for (auto i{s.cbegin()} ; std::next(i,1) != s.cend(); std::advance(i,1) ){
            cout << "000 "
                 << " i=" << *i << endl;
            ch1 = *i - '0';
            if ((*std::next(i,1) - '0') == 0) {
                ch1 *= 10;
                if (!(ch1 > 9 && ch1 < 27)){
                    cout << "broken code" << endl;
                    lres = 0;
                    break;
                }
                continue;
            }
            ok1 = (ch1 !=0);
            if (!(ok1 || ok2)){     // broken code
                // cout << "broken code" << endl;
                lres = 0;
                break;
            }

            ch2 = 10 * ch1 + (*std::next(i,1) - '0');
            ok2 = (ch2 > -1 && ch2 < 27);
            cout << "l2 222 "
                 << " i=" << *i
                    << " ch1=" << std::to_string(ch1)
                 << " ch2=" << std::to_string(ch2)
                 << " lres=" << std::to_string(lres)
                 << endl;
            if (ok1 && ok2) ++lres;
        }
        return lres;
    };

    auto l3 = [&s](){
        auto len = s.size();
        ++len;

        std::vector<int> ways(len, 0);
        ways[0] = 1;

        auto dig1{0}, dig2{0};
        for (int i = 1; i < len; ++i) {
            dig1 = s[i - 1] - '0';
            if (dig1 != 0) {
                ways[i] = ways[i - 1];
            }

            if (i > 1) {
                dig2 = 10 * (s[i - 2] - '0') + dig1;
                if (dig2 > 9 && dig2 < 27) ways[i] += ways[i - 2];
            }
        }
        for(const auto &v: ways) cout << v << " ";
        cout << endl;

        return ways[len-1];
    };

    // from https://algo.monster/liteproblems/91
    auto l4 = [&s](){
        size_t n = s.size();

        // dp[i] represents the number of ways to decode s[0...i-1]
        // dp[0] represents empty string (base case)
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));

        // Empty string has one way to decode
        dp[0] = 1;

        // Iterate through each position in the string
        for (int i = 1; i <= n; ++i) {
            // Single digit decode: Check if current digit is valid (1-9)
            if (s[i - 1] != '0') {
                dp[i] = dp[i - 1];
            }

            // Two digit decode: Check if previous two digits form a valid number (10-26)
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))) {
                dp[i] += dp[i - 2];
            }
        }

        // Return the number of ways to decode the entire string
        return dp[n];
    };


    // return ldfs(ldfs,0,0);
    // return l2();
    return l3();
    // return l4();

#if 0
    // auto c1{true}, c2{true};
    // for ( auto k{s.cbegin()}; k != s.cend(); std::advance(k,1) ){
    //     c2 = ((*k - '0') == 0);
    //     if (c1 && c2){
    //         cout << "broken code" << endl;
    //         return 0;
    //     }
    //     c1 = ((*k - '0') > 2);
    // }

    auto res{1};
    auto ok1{false}, ok2{false};
    auto ch1{0}, ch2{0};
    for (auto i{s.cbegin()} ; std::next(i,1) != s.cend(); std::advance(i,1) ){
        // cout << "000 "
        //      << " i=" << *i << endl;
        ch1 = *i - '0';
        if ((*std::next(i,1) - '0') == 0) {
            ch1 *= 10;
            // cout << "222 "
            //      << " next i=" << *std::next(i,1)
            //         << " ch1=" << std::to_string(ch1)
            //      << " res=" << std::to_string(res)
            //      << endl;
            if (!(ch1 > 9 && ch1 < 27)){
                cout << "broken code" << endl;
                res = 0;
                break;
            }
            continue;
        }


        // ch1 = *i - '0';
        ok1 = (ch1 !=0);
        if (!(ok1 || ok2)){     // broken code
            // cout << "broken code" << endl;
            res = 0;
            break;
        }

        ch2 = 10 * ch1 + (*std::next(i,1) - '0');
        ok2 = (ch2 > -1 && ch2 < 27);
        if (ok1 && ok2) ++res;
        // cout << " ch1=" << std::to_string(ch1)
        //      << " ch2=" << std::to_string(ch2)
        //      << " res=" << std::to_string(res)
        //      << endl;
    }
    return res;
#endif
}


void Solution::lc_91_test() const {
    vector< pair<string,int> >
        data ={
        //     {"12", 2},
        // {"226", 3},
        // {"06", 0},
        //     {"00", 0},
        //     {"2101", 1},
        // {"123012", 0},
        //     {"22112", 8},
        //     {"1", 1},
        //     {"10", 1},
        //     {"20", 1},
        //     {"30", 0},
        //     {"1000", 0},
            // {"111111111111111111111111111111111111111111111", 1836311903},
            {"111111111111111", 987},
        };

    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_91(inp, m));
            auto shouldBe = std::to_string(v.second);
            auto note = inp;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}


int Solution::lc_127(string beginWord, string endWord, vector<string>& wordList, int mode) const{

    //
    auto lbfs = [ &wordList ](auto begG, auto endG){
        queue<pair<string, int>> bfsQ;
        bfsQ.push({begG, 1});

        unordered_set<string> vis;
        vis.insert(begG);
        // auto lres{1};

        // lambda for finding diff like binary search
        auto ldiff = [](auto &&self, string cur, string b){
            // cout << "ll00"<< " cur=" << cur
            //      << " b=" << b <<endl;
            auto len = cur.size();
            if (len == 1) return 1;

            auto lf = cur.substr(0,len/2);
            auto rt = cur.substr(len/2);
            auto blf = b.substr(0,len/2);
            auto brt = b.substr(len/2);

            auto lfdiff = ( lf == blf ? 0 : 1);
            auto rtdiff = ( rt == brt ? 0 : 1);

            if ((lfdiff + rtdiff) == 2) return 2;
            else if ((lfdiff + rtdiff) == 0) return 0;
            else if (lfdiff) return self(self, lf, blf);
            else if (rtdiff) return self(self, rt, brt);

            return 0;
        };

        while (!bfsQ.empty()) {
            auto [curG, lres] = bfsQ.front();
            bfsQ.pop();

            if (curG == endG) return lres;

            for (auto i{wordList.size()-1}; i < wordList.size(); --i){
                // cout << "555 "
                //      << " i=" << i << endl;
                if (ldiff(ldiff, curG, wordList[i]) == 1 ) {
                    // cout << "888 "
                    //      << " i=" << i
                    //      << " wordList[i]=" << wordList[i]
                    //      << " dist=" << lres << endl;

                    bfsQ.push({wordList[i], lres +1});
                    wordList.erase(wordList.begin() + i);
                }
            }

        }

        return 0;
    };

    auto l2bfs = [ &wordList ](auto begG, auto endG){
        queue<pair<string, int>> bfsQ;
        bfsQ.push({begG, 1});

        unordered_set<string> dict;
        for (const auto& v : wordList) dict.insert(v);

        // a bit optimization
        if (dict.find(endG) == dict.end()) return 0;

//        auto deep{0};   // for testing

        while (!bfsQ.empty()) {
            auto [cur, lres] = bfsQ.front();
            bfsQ.pop();
            // cout << "l2 000 cur=" << cur
            //         << " bfsQ=" << bfsQ.size()
            //      << " deep=" << deep                 << endl;

            if (cur == endG) return lres;

//            auto cc{0};
            for (auto i{cur.begin()}; i != cur.end(); std::advance(i,1)){
                // auto tmp = cur;
                auto c = *i;
                for ( auto l{'a'}; l <= 'z'; ++l){
                    if (l == c) continue;
                    *i = l;
                    auto f = dict.find(cur);
                    if ( f != dict.end()){
                        bfsQ.push({cur, lres +1});
                        dict.erase(f);
                        // cout << " cur=" << cur << endl;
                    }
                }
                *i = c;

                // tmp = cur;
            }
            // if (++deep > 50) break;
        }

        return 0;
    };

    if (mode == 1) return l2bfs(beginWord, endWord);
    return lbfs(beginWord, endWord);

}


void Solution::lc_127_test() const {
    vector< pair< tuple<string, string, vector<string> >,int> >
        data ={
            {{"hit", "cog", {"hot","dot","dog","lot","log","cog"}}, 5}, // "hit" -> "hot" -> "dot" -> "dog" -> cog"
            {{"hit", "cog", {"hot","dot","dog","lot","log"}}, 0},
            #if 0
            {{"catch", "choir",
              {"tours","awake","goats","crape","boron","payee","waken","cares","times","piled","maces","cuter","spied","spare","mouse","minty","theed","sprat","veins","brian",
               "crown","years","drone","froth","foggy","laura","sears","shunt","gaunt","hovel","staff","child","arson","haber","knows","rubes","czars","pawed","whine",
               "treed","bauer","jodie","timed","flits","robby","gooks","yawls","purse","veeps","tints","taped","raced","shaft","modes","dykes","slims","parts","emile",
               "frail","salem","jives","heave","bayer","leech","clipt","yanks","wilds","hikes","cilia","spiel","mulls","fetal","homed","drown","suite","defer","oaken",
               "flail","zippy","burke","slued","mowed","manes","verse","serra","bruno","spoke","mikes","hafts","breed","sully","croce","boers","chair","thong","pulse",
               "pasta","perot","fices","shies","nadir","every","diets","roads","cones","tuned","globs","graft","stall","royal","fixes","north","pikes","slack","vests",
               "quart","crawl","tangs","calks","mayor","filmy","barns","block","hoods","storm","cedes","emote","tacks","skirt","horsy","mawed","moray","wring","munch",
               "hewed","hooke","batch","drawl","berth","sport","welch","jeans","river","tabby","amens","stump","cause","maced","hiker","spays","dusty","trail","acorn",
               "zooms","puked","clown","sands","kelli","stein","rawer","water","dolts","momma","fluky","scots","pupil","halls","toady","pored","latch","shags","union",
               "tamps","stead","ryder","knoll","cacao","damns","charm","frank","draws","gowns","risen","saxes","lucks","avert","yolks","clime","wedge","ruses","famed",
               "sabik","gravy","anion","veils","pyres","raspy","lofts","tress","showy","percy","rices","taker","roger","yeats","baked","ayers","fazes","curly","shawn",
               "clare","paine","ranks","hocks","berta","plays","parks","tacos","onion","skeet","acton","lamer","teals","reset","steal","maven","sored","fecal","harsh",
               "totem","swoop","rough","jokes","mires","weird","quits","damps","touts","fling","sarah","peeps","waxen","traps","mange","swell","swoon","catch","mower",
               "bonny","finds","yards","pleas","filed","smelt","drams","vivid","smirk","whigs","loafs","opens","meter","hakes","berms","whack","donny","faint","peace",
               "libby","yates","purer","wants","brace","razed","emend","bards","karyn","japed","fated","missy","punks","humps","steak","depth","brunt","hauls","craws",
               "blast","broom","tones","ousts","wires","peeks","ruffs","crack","monte","worth","spans","tonic","runny","erick","singe","maine","casts","jello","realm",
               "haste","utter","bleat","kasey","palms","solos","hoagy","sweep","loner","naves","rhine","acmes","cadet","dices","saris","mauro","fifty","prows","karat",
               "dowel","frays","shorn","sails","ticks","train","stars","stork","halts","basal","glops","beset","rifer","layla","lathe","daffy","jinns","snide","groin",
               "kelly","zincs","fryer","quilt","drama","shook","swami","hulls","swazi","danes","axons","those","lorry","plath","prime","faces","crock","shake","borer",
               "droop","derek","shirk","styed","frown","jells","slows","lifts","jeers","helms","turds","dross","tired","rimes","beats","dingo","crews","bides","loins",
               "furry","shana","wises","logos","aural","light","pings","belch","campy","swish","sangs","nerds","boggy","skies","weals","snags","joyed","mamet","miser",
               "leaks","ramos","tract","rends","marks","taunt","sissy","lipid","beach","coves","fates","grate","gloss","heros","sniff","verve","tells","bulge","grids",
               "skein","clout","leaps","males","surfs","slips","grave","boats","tamed","muled","meier","lower","leafy","stool","reich","rider","iring","ginny","flaks",
               "chirp","tonga","chest","ollie","foxes","links","alton","darth","drier","sated","rails","gyros","green","jenna","cures","veals","sense","sworn","roses",
               "aides","loses","rival","david","worms","stand","track","dales","noyes","fraud","shock","sward","pluto","biked","roans","whiny","halve","bunts","spilt",
               "gamey","deeds","oozed","ruder","drano","sages","fewer","maize","aimed","bails","poole","hunts","shari","champ","shuns","jonah","faced","spook","harry",
               "lagos","peale","nacho","saint","power","chaff","shard","cocky","irate","tummy","withe","forks","bates","stuns","turfs","coped","coups","vince","helps",
               "facet","fezes","outer","cheek","tried","sumps","fakes","fonds","yearn","brays","flute","fetid","beyer","mamma","topic","bouts","trend","gorey","hills",
               "swaps","sexes","cindy","ruler","kited","gaits","shank","cloys","stuck","purus","musks","gouge","brake","biker","layer","lilly","bills","seven","flyer",
               "phase","wowed","beaus","cokes","chimp","spats","mooch","dried","hulks","shift","galen","wiped","clops","decal","nopes","huffs","lades","sunny","foyer",
               "gusty","wormy","chips","focus","pails","solid","ariel","gamed","diver","vying","sacks","spout","sides","agave","bandy","scant","coils","marci","marne",
               "swank","basil","shine","nines","clues","fuzes","jacks","robin","pyxes","later","silas","napes","homes","baled","dames","abuse","piker","coots","tiles",
               "bents","pearl","booty","hells","dusky","glare","scale","pales","leary","scull","bimbo","mossy","apron","manet","opted","kusch","shiny","argos","hoped",
               "towns","bilbo","slums","skull","shale","mandy","scows","speed","eager","lards","crows","merry","anted","faxed","leave","fargo","creek","comas","golda",
               "baize","easts","plied","rared","ashed","doted","bunin","bonds","yarns","latin","right","worst","sixes","gabby","begun","upend","giant","tykes","creak",
               "manor","bosom","riced","dimly","holes","stunt","parsi","peers","snell","mates","jules","rusty","myles","yules","sades","hobbs","booth","clean","liven",
               "gamer","howdy","stray","riser","wisps","lubes","tubes","rodeo","bigot","tromp","pimps","reeve","pumps","dined","still","terms","hines","purrs","roast",
               "dooms","lints","sells","swims","happy","spank","inset","meany","bobby","works","place","brook","haded","chide","slime","clair","zeros","britt","screw",
               "ducal","wroth","edger","basie","benin","unset","shade","doers","plank","betsy","bryce","cross","roped","weans","bliss","moist","corps","clara","notch",
               "sheep","weepy","bract","diced","carla","locks","sawed","covey","jocks","large","pasts","bumps","stile","stole","slung","mooed","souls","dupes","fairs",
               "lined","tunis","spelt","joked","wacky","moira","strut","soled","pints","axing","drank","weary","coifs","wills","gibes","ceded","gerry","tires","crazy",
               "tying","sites","trust","dover","bolds","tools","latex","capet","lanky","grins","brood","hitch","perts","dozes","keels","vault","laius","chung","deres",
               "glove","corms","wafer","coons","ponce","tumid","spinx","verge","soggy","fleas","middy","saiph","payer","nukes","click","limps","oared","white","chart",
               "nasty","perth","paddy","elisa","owing","gifts","manna","ofter","paley","fores","sough","wanda","doggy","antic","ester","swath","spoon","lamas","meuse",
               "hotel","weedy","quads","paled","blond","flume","pried","rates","petal","rover","marsh","grief","downy","pools","buffs","dunne","cruel","finny","cosby",
               "patch","polly","jerks","linen","cider","visas","beard","mewed","spill","trots","tares","pured","prior","build","throe","wends","baned","mario","misty",
               "golds","lacey","slags","jived","finis","inner","money","skews","sunks","fined","bauds","lapel","class","berne","rabin","roils","hyped","styes","evans",
               "towed","hawed","allow","modal","ports","erich","rills","humid","hooks","sedge","shirt","nippy","fundy","runes","smile","dolly","tisha","byers","goths",
               "sousa","mimed","welts","hoots","shown","winds","drays","slams","susan","frogs","peach","goody","boned","chewy","eliza","peary","pyxed","tiled","homer",
               "tokes","verdi","mabel","rolls","laden","loxed","phony","woods","brine","rooks","moods","hired","sises","close","slops","tined","creel","hindu","gongs",
               "wanes","drips","belly","leger","demon","sills","chevy","brads","drawn","donna","glean","dying","sassy","gives","hazes","cores","kayla","hurst","wheat",
               "wiled","vibes","kerry","spiny","wears","rants","sizer","asses","duked","spews","aired","merak","lousy","spurt","reeds","dared","paged","prong","deere",
               "clogs","brier","becks","taken","boxes","wanna","corny","races","spuds","jowls","mucks","milch","weest","slick","nouns","alley","bight","paper","lamps",
               "trace","types","sloop","devon","pedal","glint","gawky","eaves","herbs","felts","fills","naval","icing","eking","lauds","stats","kills","vends","capes",
               "chary","belle","moats","fonts","teems","wards","bated","fleet","renal","sleds","gases","loony","paced","holst","seeds","curie","joist","swill","seats",
               "lynda","tasks","colts","shops","toted","nuder","sachs","warts","pupal","scalp","heirs","wilma","pansy","berra","keeps","menus","grams","loots","heels",
               "caste","hypes","start","snout","nixes","nests","grand","tines","vista","copes","ellis","narks","feint","lajos","brady","barry","trips","forth","sales",
               "bests","hears","twain","plaid","hated","kraft","fared","cubit","jayne","heats","chums","pangs","glows","lopez","vesta","garbo","ethel","blood","roams",
               "mealy","clunk","rowed","hacks","davit","plane","fuses","clung","fitch","serer","wives","lully","clans","kinks","spots","nooks","plate","knits","greet",
               "loads","manic","scone","darin","pills","earth","gored","socks","fauna","ditch","wakes","savvy","quiet","nulls","sizes","diana","mayan","velds","dines",
               "punch","bales","sykes","spiky","hover","teats","lusts","ricky","think","culls","bribe","pairs","month","cored","packs","lobes","older","hefts","faxes",
               "cased","swain","bawdy","troop","woven","stomp","swags","beads","check","shill","broad","souse","pouch","lived","iambs","teaks","clams","outed","maxed",
               "plain","sappy","cabal","penal","shame","budge","offed","kooks","gybed","basin","thoth","arced","hypos","flows","fetch","needs","davis","jared","bongo",
               "added","sames","randy","tunes","jamar","smash","blows","grows","palmy","miler","chins","viola","tower","cream","molls","cello","sucks","fears","stone",
               "leans","zions","nutty","tasha","ratty","tenet","raven","coast","roods","mixes","kmart","looms","scram","chapt","lites","trent","baron","rasps","ringo",
               "fazed","thank","masts","trawl","softy","toils","romes","norma","teens","blank","chili","anise","truss","cheat","tithe","lawns","reese","slash","prate",
               "comet","runts","shall","hosed","harpy","dikes","knock","strip","boded","tough","spend","coats","husky","tyree","menes","liver","coins","axles","macho",
               "jawed","weeps","goods","pryor","carts","dumps","posts","donor","daunt","limbo","books","bowls","welds","leper","benny","couch","spell","burst","elvin",
               "limbs","regal","loyal","gaily","blade","wheal","zests","seine","hubby","sheen","tapes","slugs","bench","lungs","pipes","bride","selma","berry","burns",
               "skins","bowen","gills","conan","yucky","gauls","voled","crust","jerky","moans","plump","sided","disks","gleam","larry","billy","aloud","match","udder",
               "rises","wryer","deter","cling","brisk","lever","chaps","tansy","gland","rocky","lists","joins","tubed","react","farsi","dopes","chats","olsen","stern",
               "gully","youth","wiles","slink","cooke","arise","bores","maims","danny","rives","rusts","plots","loxes","troys","cleat","waxes","booze","haven","dilly",
               "shaun","gasps","rains","panda","quips","kings","frets","backs","arabs","rhino","beets","fiber","duffy","parry","sever","hunks","cheap","beeps","fifes",
               "deers","purls","hello","wolfs","stays","lands","hawks","feels","swiss","tyros","nerve","stirs","mixed","tombs","saves","cater","studs","dorky","cinch",
               "spice","shady","elder","plato","hairs","newts","slump","boots","lives","walls","spunk","bucks","mined","parch","disco","newel","doris","glues","brawn",
               "abner","piked","laxes","bulky","moran","cozen","tinge","dowry","snare","sagan","harms","burch","plows","sunni","fades","coach","girls","typed","slush",
               "saver","bulls","grass","holed","coven","dukes","ocher","texan","cakes","gilts","jenny","salon","divas","maris","costs","sulla","lends","gushy","pears",
               "teddy","huffy","sited","rhone","euler","solve","grace","snarl","taste","sally","allay","suers","bogey","pooch","songs","cameo","molts","snipe","cargo",
               "forge","reins","hoses","crams","fines","tings","wings","spoor","twice","waxed","mixer","bongs","stung","gages","yelps","croci","corks","bolls","madge",
               "honer","riled","camus","trick","bowed","overt","steed","ripes","stave","crick","great","scott","scald","point","finch","bulks","chant","kiddo","cover",
               "drunk","sered","dicky","wider","saith","mutts","blind","lyres","sized","darby","rebel","zones","title","yawns","laths","sting","taine","paris","route",
               "livia","roots","belay","daubs","spoof","camel","colds","foist","saned","doles","slays","woody","leads","stout","caper","erika","lance","earns","vines",
               "mercy","antis","terri","messy","lords","shims","serfs","jinni","caged","threw","rainy","bumpy","arias","wails","romeo","gorge","dolls","risks","skyed",
               "fumes","payed","mites","choir","piles","scene","flake","solon","brahe","bikes","dawes","goofs","payne","cried","slavs","hives","snack","cribs","aways",
               "fired","swarm","pumas","paved","smith","gooey","liefs","safer","banes","slake","doled","dummy","gazed","heaps","loped","scoff","crash","balmy","hexed",
               "lunch","guide","loges","alien","rated","stabs","whets","blest","poops","cowls","canes","story","cunts","tusks","pinto","scats","flier","chose","brute",
               "laked","swabs","preps","loose","merle","farms","gapes","lindy","share","floes","scary","bungs","smart","craps","curbs","vices","tally","beret","lenny",
               "waked","brats","carpi","night","junes","signs","karla","dowdy","devil","toned","araby","trait","puffy","dimer","honor","moose","synch","murks","doric",
               "muted","quite","sedan","snort","rumps","teary","heard","slice","alter","barer","whole","steep","catty","bidet","bayes","suits","dunes","jades","colin",
               "ferry","blown","bryon","sways","bayed","fairy","bevel","pined","stoop","smear","mitty","sanes","riggs","order","palsy","reels","talon","cools","retch",
               "olive","dotty","nanny","surat","gross","rafts","broth","mewls","craze","nerdy","barfs","johns","brims","surer","carve","beers","baker","deena","shows",
               "fumed","horde","kicky","wrapt","waits","shane","buffy","lurks","treat","savor","wiper","bided","funny","dairy","wispy","flees","midge","hooch","sired",
               "brett","putty","caked","witch","rearm","stubs","putts","chase","jesus","posed","dates","dosed","yawed","wombs","idles","hmong","sofas","capek","goner",
               "musts","tangy","cheer","sinks","fatal","rubin","wrest","crank","bared","zilch","bunny","islet","spies","spent","filth","docks","notes","gripe","flair",
               "quire","snuck","foray","cooks","godly","dorms","silos","camps","mumps","spins","cites","sulky","stink","strap","fists","tends","adobe","vivas","sulks",
               "hasps","poser","bethe","sudan","faust","bused","plume","yoked","silly","wades","relay","brent","cower","sasha","staci","haves","dumbs","based","loser",
               "genes","grape","lilia","acted","steel","award","mares","crabs","rocks","lines","margo","blahs","honda","rides","spine","taxed","salty","eater","bland",
               "sweat","sores","ovens","stash","token","drink","swans","heine","gents","reads","piers","yowls","risky","tided","blips","myths","cline","tiers","racer",
               "limed","poled","sluts","chump","greek","wines","mangy","fools","bands","smock","prowl","china","prove","oases","gilda","brews","sandy","leers","watch",
               "tango","keven","banns","wefts","crass","cloud","hunch","cluck","reams","comic","spool","becky","grown","spike","lingo","tease","fixed","linda","bleep",
               "funky","fanny","curve","josie","minds","musty","toxin","drags","coors","dears","beams","wooer","dells","brave","drake","merge","hippo","lodge","taper",
               "roles","plums","dandy","harps","lutes","fails","navel","lyons","magic","walks","sonic","voles","raped","stamp","minus","hazel","clods","tiffs","hayed",
               "rajah","pared","hates","makes","hinds","splay","flags","tempe","waifs","roved","dills","jonas","avers","balds","balks","perms","dully","lithe","aisha",
               "witty","ellie","dived","range","lefty","wined","booby","decor","jaded","knobs","roded","moots","whens","valet","talks","blare","heeds","cuing","needy",
               "knees","broke","bored","henna","rages","vises","perch","laded","emily","spark","tracy","tevet","faith","sweet","grays","teams","adder","miffs","tubae",
               "marin","folds","basis","drugs","prick","tucks","fifth","treks","taney","romps","jerry","bulgy","anton","codes","bones","quota","turns","melts","croat",
               "woken","wried","leash","spacy","bless","lager","rakes","pukes","cushy","silks","auden","dotes","hinge","noisy","coked","hiked","garth","natty","novel",
               "peeve","macaw","sloth","warns","soles","lobed","aimee","toads","plugs","chasm","pries","douse","ruled","venus","robes","aglow","waves","swore","strum",
               "stael","seeps","snots","freed","truck","hilly","fixer","rarer","rhyme","smugs","demos","ships","piped","jumpy","grant","dirty","climb","quell","pulps",
               "puers","comte","kirks","waver","fever","swear","straw","serum","cowed","blent","yuppy","ropes","conks","boozy","feeds","japes","auger","noons","wench",
               "tasty","honed","balms","trams","pasha","mummy","tides","shove","shyer","trope","clash","promo","harem","never","humus","burks","plans","tempi","crude",
               "vocal","lames","guppy","crime","cough","rural","break","codex","baggy","camry","muses","exile","harte","evens","uriel","bombs","wrens","goren","clark",
               "groom","tinny","alias","irwin","ruddy","twins","rears","ogden","joker","shaky","sodas","larch","lelia","longs","leeds","store","scars","plush","speck",
               "lamar","baser","geeky","wilda","sonny","gummy","porch","grain","testy","wreck","spurs","belie","ached","vapid","chaos","brice","finks","lamed","prize",
               "tsars","drubs","direr","shelf","ceres","swops","weirs","vader","benet","gurus","boors","mucky","gilds","pride","angus","hutch","vance","candy","pesky",
               "favor","glenn","denim","mines","frump","surge","burro","gated","badge","snore","fires","omens","sicks","built","baits","crate","nifty","laser","fords",
               "kneel","louse","earls","greed","miked","tunic","takes","align","robed","acres","least","sleek","motes","hales","idled","faked","bunks","biped","sowed",
               "lucky","grunt","clear","flops","grill","pinch","bodes","delta","lopes","booms","lifer","stunk","avery","wight","flaps","yokel","burgs","racks","claus",
               "haled","nears","finns","chore","stove","dunce","boles","askew","timid","panic","words","soupy","perks","bilge","elias","crush","pagan","silts","clive",
               "shuck","fulls","boner","claws","panza","blurb","soaks","skips","shape","yells","raved","poppy","lease","trued","minks","estes","aisle","penes","kathy",
               "combo","viper","chops","blend","jolly","gimpy","burma","cohan","gazer","drums","gnaws","clone","drain","morns","wages","moths","slues","slobs","warps",
               "brand","popes","triad","ounce","stilt","shins","greer","hodge","minos","tweed","sexed","alger","floss","timer","steve","birch","known","aryan","hedge",
               "fully","jumps","bites","shots","curer","board","lenin","corns","dough","named","kinda","truce","games","lanes","suave","leann","pesos","masks","ghats",
               "stows","mules","hexes","chuck","alden","aping","dives","thurs","nancy","kicks","gibed","burly","sager","filly","onset","anons","yokes","tryst","rangy",
               "pours","rotes","hided","touch","shads","tonya","finer","moors","texas","shoot","tears","elope","tills"}}, 21},
            #endif
        };

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto startGene = get<0>(v.first);
            auto endGene = get<1>(v.first);
            auto bank = get<2>(v.first);
            auto res = std::to_string(lc_127(startGene, endGene, bank, m));
            auto shouldBe = std::to_string(v.second);
            auto note = startGene + ">" + endGene;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"} << std::endl;
    }

}

int Solution::lc_433(string startGene, string endGene, vector<string>& bank, int mode) const{

    // lambda for sequential search
    auto lbfs = [ &bank ](auto begG, auto endG){
        queue<pair<string, int>> bfsQ;
        bfsQ.push({begG, 0});

        unordered_set<string> vis;
        vis.insert(begG);
        auto lres{-1};

        while (!bfsQ.empty()) {
            auto [curG, lres] = bfsQ.front();
            bfsQ.pop();

#if 0
            // cout << "000"
            //      << " begG="<< begG
            //      << " endG="<< endG
            //      << " curG="<< curG
            //      << endl;
#endif

            if (curG == endG) return lres;

            for (const string& v : bank) {
#if 0
                cout << "555"
                     << " curG="<< curG
                     << " v="<< v
                     << endl;
#endif

                auto diff = 0;
                for (auto i{0}; i < 8 && diff < 2; ++i) {
                    if (curG[i] != v[i]) {
                        ++diff;
                    }
#if 0
                    cout << "888"
                         << " i=" << std::to_string(i)
                         << " diff="<< std::to_string(diff)
                         << " curG[i]="<< curG[i]
                         << " v[i]="<< v[i]
                         << endl;
#endif
                }

                if (diff == 1 && vis.find(v) == vis.end() ) {
                    vis.insert(v);
                    bfsQ.push({v, lres +1});
                }
            }
        }

        return lres;
    };

    // lambda for binary search is about two times faster
    auto l2bfs = [ &bank ](auto begG, auto endG){
        queue<pair<string, int>> bfsQ;
        bfsQ.push({begG, 0});

        unordered_set<string> vis;
        vis.insert(begG);
        auto lres{-1};

        // lambda for finding diff like binary search
        auto ldiff = [](auto &&self, string cur, string b){
            auto len = cur.size();
            if (len == 1) return 1;

            auto lf = cur.substr(0,len/2);
            auto rt = cur.substr(len/2);
            auto blf = b.substr(0,len/2);
            auto brt = b.substr(len/2);

            auto lfdiff = ( lf == blf ? 0 : 1);
            auto rtdiff = ( rt == brt ? 0 : 1);

            if ((lfdiff + rtdiff) == 2) return 2;
            else if ((lfdiff + rtdiff) == 0) return 0;
            else if (lfdiff) return self(self, lf, blf);
            else if (rtdiff) return self(self, rt, brt);

            return 0;
        };

        while (!bfsQ.empty()) {
            auto [curG, lres] = bfsQ.front();
            bfsQ.pop();

            if (curG == endG) return lres;

            for (const string& v : bank) {

                if (ldiff(ldiff, curG, v) == 1 && vis.find(v) == vis.end() ) {
                    vis.insert(v);
                    bfsQ.push({v, lres +1});
                }
            }
        }

        return lres;
    };

    if (mode == 1) return l2bfs(startGene, endGene);
    return lbfs(startGene, endGene);
}


void Solution::lc_433_test() const {
    vector< pair< tuple<string, string, vector<string> >,int> >
        data ={
            {{"AACCGGTT", "AACCGGTA", {"AACCGGTA"}}, 1},
            {{"AACCGGTT", "AAACGGTA", {"AACCGGTA","AACCGCTA","AAACGGTA"}}, 2},
            // {{"", "",{}}, -1},
                };
    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto startGene = get<0>(v.first);
            auto endGene = get<1>(v.first);
            auto bank = get<2>(v.first);
            auto res = std::to_string(lc_433(startGene, endGene, bank, m));
            auto shouldBe = std::to_string(v.second);
            auto note = startGene + ">" + endGene;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

int Solution::lc_1371(string s, int mode) const
{
    int res{0};

    auto lresolve = [](const auto &v) {
        if (v == 'a') return 1;
        else if (v == 'e') return 2;
        else if (v == 'i') return 4;
        else if (v == 'o') return 8;
        else if (v == 'u') return 16;
        return 0;
    };

    size_t len{s.size()};
    auto total{0}, subtotal{0};
    // precalculate
    for (const auto &v : s) total ^= lresolve(v);

    if (total == 0) return static_cast<int>(len);

    auto i{0};
    size_t k{0};
    for (; i < len && res < (len - i); ++i){
        // cout << "000 s=" << s
        //      <<" str=" << s.substr(i, k - i)
        //      <<" i/k=" << std::to_string(i) << "/"  << std::to_string(k)
        //      << " res=" << res
        //      << endl;
        k = len;
        if (i > 0) total ^= lresolve(s[i-1]);
        if (total == 0) {
            if ((k-i) > res) res = static_cast<int>(k - i);
            continue;
        }
        subtotal = total;
        // cout << "TTT s=" << s
        //      <<" str=" << s.substr(i, k - i)
        //      <<" i/k=" << std::to_string(i) << "/"  << std::to_string(k)
        //      <<" total=" << std::to_string(total)
        //      <<" sub=" << std::to_string(subtotal)
        //      << " res=" << res
        //      << endl;
        for ( ; k > i && res < (k - i); --k) {
            if (k < len) subtotal ^= lresolve(s[k]);
            // cout << "AAA s=" << s
            //      <<" str=" << s.substr(i, k - i)
            //      <<" i/k=" << std::to_string(i) << "/"  << std::to_string(k)
            //      <<" total=" << std::to_string(total)
            //      <<" sub=" << std::to_string(subtotal)
            //      << " res=" << res
            //      << endl;
            if (subtotal == 0) {
                if ((k-i) > res) res = static_cast<int>(k - i);
                break;
            }
        }
    }
    // cout << "999 s=" << s
    //      <<" i/k=" << std::to_string(i) << "/"  << std::to_string(k)
    //      <<" total=" << std::to_string(total)
    //      <<"  2 ^ 2=" << std::to_string( 2 ^ 2)
    //      << endl;

    return res;
}

void Solution::lc_1371_test() const {
    vector< pair<std::string,int> >
        data ={
                {"leetminicoworoep",13},
            {"leetcodeisgreat",5},
            {"bcbcbc",6},
             {"qeee",3},
            {"aqee",3},
                };
    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_1371(inp,m));
            auto shouldBe = std::to_string(v.second);
            auto note = v.first;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}


string Solution::lc_726(string formula, int mode) const{
    // string nf{""};      // new formula
    // auto atoms = std::make_unique<std::unordered_map<string, int> >();
    std::map<string, int> atoms;
    // auto p{std::cbegin(formula)};
    auto i{0};
    auto len{std::size(formula)};

    auto li_dfs = [ &formula, &i, &len ] ( auto&& self, auto m) ->string{


        auto mn{m};
        string sdig{""}, tmp{""}, el{""};
        auto q{1};
        cout << "l000 mn=" << mn << " sdig=" << sdig
             << " i/len=" << i << "/" << len
             << " el=" << (i < len ? std::string(1,formula[i]) : "End")
             << " tmp=" << tmp
             << endl;

        if (m > 5) return tmp;      // qqq

        while (i < len){
            if (formula[i] == '(') {
                ++i;
                tmp += self(self, ++m);
            }

            if (formula[i] == ')') {
                ++i;
                q = 1;
                sdig = "";
                for ( ;  i < len && std::isdigit(formula[i], std::locale::classic()); ++i) {
                    sdig += formula[i];
                }
                cout << "l555 "
                     << " mn=" << mn
                     << " sdig=" << sdig
                     << " i/len=" << i << "/" << len
                     << " el=" << (i < len ? std::string(1,formula[i]) : "End")
                     << " tmp=" << tmp << " (" << std::size(tmp) << ")"
                     << endl;
                if (!(sdig.empty())) q = std::stoi(sdig);
                break;
            }

            if (!(i < len)) return "";      // qqq

            sdig = "";
            // q = 1;
            el = formula[i];
            ++i;
            for ( ;  i < len && std::islower(formula[i], std::locale::classic()); ++i) {
                el += formula[i];
            }
            for ( ;  i < len && std::isdigit(formula[i], std::locale::classic()); ++i) {
                sdig += formula[i];
            }
            // if (!(std::is_empty(sdig))) q = std::stoi(sdig);
            tmp += el + sdig;

            cout << "l_222 mn=" << mn << " sdig=" << sdig
                 << " i/len=" << i << "/" << len
                 << " el=" << (i < len ? std::string(1,formula[i]) : "End")
                 << " tmp=" << tmp
                 << endl;

        }

        string lres{""};
        for (auto k{0}; k < q; ++k) lres += tmp;
        cout << "l_999 "
                << " mn=" << mn
             << " sdig=" << sdig
             << " i/len=" << i << "/" << len
             << " el=" << (i < len ? std::string(1,formula[i]) : "End")
             << " lres=" << lres
             << endl;
        return lres;
    };

    auto li_count = [&atoms] (const string &s) {
        cout <<"COUNT 000 s=" << s << endl;
        auto len{std::size(s)};
        string nme{""}, sqty{""};
        auto qty{1};
        for ( auto j{0}; j < len; ) {
            nme = ""; sqty = ""; qty=1;
            while (1){
                if (std::isalpha(s[j], std::locale::classic())) {
                    nme += s[j];
                    ++j;
                    for ( ; j < len && std::islower(s[j], std::locale::classic()); ++j) nme += s[j];
                    if (!( j < len)) break;
                    if (std::isalpha(s[j], std::locale::classic())) break;
                    for ( ;  j < len && std::isdigit(s[j], std::locale::classic()); ++j) {
                        sqty += s[j];
                    }
                }
                break;
            }
            // cout <<"COUNT sqty=" << sqty << endl;
            if (!(std::empty(sqty))) qty = std::stoi(sqty);

            auto atom = atoms.find(nme);
            if (atom != atoms.end())
                atom->second += qty;
            else
                atoms.insert({nme, qty});
        }
        return;
    };

    auto l2_dfs = [ &formula, &i, &len ] ( auto&& self, auto m) ->vector<pair<string, int> >{

        vector<pair<string, int>> ats;
        auto mn{m};
        string sdig{""}, tmp{""}, el{""};
        auto q{1}, eq{1};
        // cout << "l000 mn=" << mn << " sdig=" << sdig
        //      << " i/len=" << i << "/" << len
        //      << " el=" << (i < len ? std::string(1,formula[i]) : "End")
        //      << " tmp=" << tmp
        //      << endl;

        // if (m > 5) return ats;      // qqq

        while (i < len){
            if (formula[i] == '(') {
                ++i;
                auto tt = self(self, ++m);
                for (auto const &v: tt) ats.emplace_back(v );
            }

            if (formula[i] == ')') {
                ++i;
                q = 1;
                sdig = "";
                for ( ;  i < len && std::isdigit(formula[i], std::locale::classic()); ++i) {
                    sdig += formula[i];
                }
                // cout << "l555 "
                //      << " mn=" << mn
                //      << " sdig=" << sdig
                //      << " i/len=" << i << "/" << len
                //      << " el=" << (i < len ? std::string(1,formula[i]) : "End")
                //      << " tmp=" << tmp << " (" << std::size(tmp) << ")"
                //      << endl;
                if (!(sdig.empty())) q = std::stoi(sdig);
                break;
            }

            if (!(i < len)) {
                // q = 1;
                break;;      // qqq
            }
            if (std::isupper(formula[i], std::locale::classic())) {
                sdig = "";
                eq = 1;
                el = formula[i];
                ++i;
                for ( ;  i < len && std::islower(formula[i], std::locale::classic()); ++i) {
                    el += formula[i];
                }
                for ( ;  i < len && std::isdigit(formula[i], std::locale::classic()); ++i) {
                    sdig += formula[i];
                }
                if (!(sdig.empty())) eq = std::stoi(sdig);
                // tmp += el + sdig;
                ats.push_back({el, eq});

            }

            // cout << "l_222 mn=" << mn << " sdig=" << sdig
            //      << " i/len=" << i << "/" << len
            //      << " el=" << (i < len ? std::string(1,formula[i]) : "End")
            //      << " tmp=" << tmp
            //      << endl;

        }

        // for (auto k{0}; k < q; ++k) lres += tmp;
        if (q > 1) std::transform(ats.cbegin(), ats.cend(), ats.begin(), [&q](pair<string, int> v) { return make_pair(v.first, q * v.second);});

        // string lres{""};
        // for (const auto &v : ats) lres += v.first +"."+ std::to_string(v.second) + " ";
        // cout << "l_999 "
        //      << " mn=" << mn
        //      << " sdig=" << sdig
        //      << " i/len=" << i << "/" << len
        //      << " el=" << (i < len ? std::string(1,formula[i]) : "End")
        //      << " lres=" << lres
        //      << endl;
        return ats;
    };


    auto l_dfs = [ &formula, &i, &len ] ( auto&& self ) ->vector<pair<string, int> >{

        vector<pair<string, int>> ats;
        string sdig{""},  el{""};
        auto q{1}, eq{1};

        while (i < len){
            if (formula[i] == '(') {
                ++i;
                auto tt = self(self);
                for (auto const &v: tt) ats.emplace_back(v );
            }

            if (formula[i] == ')') {
                ++i;
                q = 1;
                sdig = "";
                for ( ;  i < len && std::isdigit(formula[i], std::locale::classic()); ++i) {
                    sdig += formula[i];
                }
                if (!(sdig.empty())) q = std::stoi(sdig);
                break;
            }

            if (std::isupper(formula[i], std::locale::classic())) {
                sdig = "";
                eq = 1;
                el = formula[i];
                ++i;
                for ( ;  i < len && std::islower(formula[i], std::locale::classic()); ++i) {
                    el += formula[i];
                }
                for ( ;  i < len && std::isdigit(formula[i], std::locale::classic()); ++i) {
                    sdig += formula[i];
                }
                if (!(sdig.empty())) eq = std::stoi(sdig);
                ats.push_back({el, eq});

            }

        }

        if (q > 1) std::transform(ats.cbegin(), ats.cend(), ats.begin(), [&q](pair<string, int> v) { return make_pair(v.first, q * v.second);});
        return ats;
    };

    auto latoms = l_dfs(l_dfs);

    for (const auto &v: latoms) {
        auto atom = atoms.find(v.first);
        if (atom != atoms.end())
            atom->second += v.second;
        else
            atoms.insert({v.first, v.second});

    }

    // auto k{0};

    // for ( ; i < len; ++i){
    //     if (formula[i] == '(') {
    //         li_count(formula.substr(k,i-k));
    //         ++i;
    //         li_count(li_dfs(li_dfs, 0));
    //         k=i;
    //     }
    // }
    // if (k < len) li_count(formula.substr(k,i-k));

    // generate result string
    string res{""};
    for (const auto &v: atoms)
        res +=  v.first + (v.second > 1 ? std::to_string(v.second) : "");
        // cout << "RES"
        //      << " nme=" << v.first
        //      << " qty=" << v.second << endl;

    return res;
}

void Solution::lc_726_test() const {
    vector< pair<std::string,std::string> >
        data ={
                {"H2O", "H2O"},
                {"Mg(OH)2","H2MgO2"},
            {"K4(ON(SO3)2)2", "K4N2O14S4"},
            {"K(N(OH)2)3","H6KN3O6"},
            {"Mg(OH)2Ca","CaH2MgO2"},
            {"((N42)24(OB40Li30CHe3O48LiNN26)33(C12Li48N30H13HBe31)21(BHN30Li26BCBe47N40)15(H5)16)14", "B18900Be18984C4200H5446He1386Li33894N50106O22638"},
            // {"((N42)24(OB40Li30CHe3O48LiNN26)33)14","qwerty"},
            {"((N42)24(OQ4)33)14","N14112O462Q1848"},
            // {"",""},
                };
    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = lc_726(inp,m);
            auto shouldBe = v.second;
            auto note = v.first;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

string Solution::lc_394(string s, int mode) const{

    string res{""};
    auto p{std::cbegin(s)};

    auto l2_dfs = [ &s, &p ] ( auto&& self) ->string{
        string dstr{""}, tmp{""};
        // cout << "l2 dstr=" << dstr
        //      << " p=" << *p
        //      << endl;
        while (std::isdigit(*p, std::locale::classic())) {
            dstr += *p;
            std::advance(p,1);
        }
        auto q{std::stoi(dstr)};
        std::advance(p,1);
        for ( ; p != std::cend(s) && *p != ']'; std::advance(p,1)) {
            if (std::isdigit(*p, std::locale::classic()))  tmp += self(self);
              else tmp += *p;
        }
        string lres{""};
        for (auto k{0}; k < q; ++k) lres += tmp;
        return lres;
    };

    for ( ; p != std::cend(s); std::advance(p,1)){
        if (std::isdigit(*p, std::locale::classic()))  res += l2_dfs(l2_dfs);
          else  res += *p;
    }

    return res;
}

void Solution::lc_394_test() const{
    vector< pair<std::string,std::string> >
        data ={
            {"qwert1[y]", "qwerty"},
                {"gy3[a]2[bc]", "gyaaabcbc"},
                {"3[a2[c]]","accaccacc"},
            {"2[abc]3[cd]ef","abcabccdcdcdef"},
            {"q20[w]10[e]t","qwwwwwwwwwwwwwwwwwwwweeeeeeeeeet"},
            {"2[q]ry3[d]","qqryddd"},
                };
    for (auto m: {0}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = lc_394(inp,m);
            auto shouldBe = v.second;
            auto note = v.first;
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

long long Solution::lc_2971(vector<int>& nums, int mode){

    if (std::size(nums) < 3) return -1;

    long long res{std::reduce(std::cbegin(nums), std::cend(nums), 0ll)};

    auto l_std = [&nums](auto res)->long long{
        std::sort(std::begin(nums), std::end(nums));

        // res = std::reduce(std::cbegin(nums), std::cend(nums));
        auto i{std::crbegin(nums)};
        for ( ; i != std::crend(nums); std::advance(i, 1)){
            res -= *i;
            if (*i < res){
                res += *i;
                break;
            }
        }

        if (i == std::crend(nums)) return -1;
        return res;
    };

    // faster but space consumed
    auto l_pq = [&nums](auto s)->long long{
        long long res{-1};
        std::priority_queue<int> pq(std::begin(nums), std::end(nums));
        long long v{0};
        while (std::size(pq) > 2){
            v = pq.top();
            s -= pq.top();
            if (s > pq.top()){
                res = s + pq.top();
                break;
            }
            pq.pop();
        }
        return res;
    };

    if (mode == 1) return l_pq(res);
    return l_std(res);
}

void Solution::lc_2971_test(){
    vector< pair< vector<int>,long long> >
        data ={
                {{5,5,5},15},
                {{1,12,1,2,5,50,3},12},
                {{2,2,3,4,2,2,3,4,2,2,3,4,2,3,4,2,3,4},51},
                {{5,5,50},-1},
                {{300005055,352368231,311935527,315829776,327065463,388851949,319541150,397875604,311309167,391897750,366860048,359976490,325522439,390648914,359891976,369105322,
              350430086,398592583,354559219,372400239,344759294,379931363,308829137,335032174,336962933,380797651,378305476,336617902,393487098,301391791,394314232,387440261,316040738,
              388074503,396614889,331609633,374723367,380418460,349845809,318514711,308782485,308291996,375362898,397542455,397628325,392446446,368662132,378781533,372327607,378737987},17876942274},
                // {{},0},
                };
    vector<int> tmp(500);
    std::iota(std::begin(tmp), std::end(tmp), 100);
    data.push_back(std::make_pair(std::move(tmp), 174750)) ;

    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            const auto res = std::to_string(lc_2971(inp, m));
            const auto shouldBe = std::to_string(v.second);
            const auto note = vkstd::toString(v.first);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

int Solution::lc_611(vector<int>& nums, int mode){

    if (std::size(nums) < 3) return 0;

    std::sort(std::begin(nums), std::end(nums));

    auto l_std = [&nums](){
        auto res{0};
        std::ptrdiff_t r{0};
        for (auto i{std::begin(nums)}; i < std::next(std::end(nums),-2); std::advance(i,1)) {
            for (auto j{std::next(i,1)}; j < std::next(std::end(nums),-1); std::advance(j,1)) {

                r = std::distance(std::begin(nums), lower_bound(std::next(j, 1), std::end(nums), *i + *j)) - 1;

                res += r - std::distance(std::begin(nums),j);
            }
        }
        return res;
    };

    auto l_const = [&nums](){
        auto res{0};
        std::ptrdiff_t r{0};
        for (auto i{std::cbegin(nums)}; i < std::next(std::cend(nums),-2); std::advance(i,1)) {
            for (auto j{std::next(i,1)}; j < std::next(std::cend(nums),-1); std::advance(j,1)) {

                r = std::distance(std::cbegin(nums), lower_bound(std::next(j, 1), std::cend(nums), *i + *j)) - 1;

                res += r - std::distance(std::cbegin(nums),j);
            }
        }
        return res;
    };
    
// l_fast is alien, to compare velocity
    auto l_fast = [&nums](){
        auto res{0};

        for(size_t i = nums.size() - 1; i >= 0; i--)
        {
            size_t low = 0, high = i - 1;
            while(low < high)
            {
                if(nums[low] + nums[high] > nums[i])
                {
                    res += (high - low);
                    high--;
                }
                else
                    low++;
            }
        }
        return res;
    };

    if (mode == 1) return l_const();
    else if(mode == 2) return l_fast();

    return l_std();
}

void Solution::lc_611_test(){
    vector< pair< vector<int>,int> >
        data ={
            {{2,2,3,4},3},
            {{4,2,3,4},4},
            {{2,2,3,4,2,2,3,4,2,2,3,4,2,3,4,2,3,4},676},
            {{3,4},-1},
            {{2},-1},
            {{},-1},
            };
    vector<int> tmp(500);
    std::iota(std::begin(tmp), std::end(tmp), 100);
    data.push_back(std::make_pair(std::move(tmp), 15355200)) ;

    for (auto m: {0,1,2}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            const auto res = std::to_string(lc_611(inp, m));
            const auto shouldBe = std::to_string(v.second);
            const auto note = vkstd::toString(v.first);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

int Solution::lc_3091(int k, int mode){

    if (k < 2) return 0;
    // if (k < 3) return 1;

    auto  l_medium = [&k]() {
        auto lres{0};
        double sqrt = std::sqrt(k);
        int f = std::floor(sqrt);
        int c = std::ceil(sqrt);
        if (f * c >= k) {
            lres = (f-1) + (c-1);
        } else {
            lres = 2*(c-1);
        }
        return lres;
    };

    auto l_my = [&k](){
        auto res{0};
        auto i{1};
        for (; i * i < k; i <<=1 ) {}
        auto lf{i/2}, rt{i};
        // auto j{0};
        // cout << "555 k=" << k << " lf=" << lf << " rt=" << rt << endl;

        while ( (rt-lf) > 1 /*&& j < 10*/){
            // ++j;
            i = lf + (rt-lf)/2;
            if ((i * i) < k) lf = i;
            else rt = i;
            // cout << "k=" << k << " lf=" << lf << " rt=" << rt << " res=" << res << endl;
        }
        res = k/rt + rt - 1;
        if (!(k % rt)) --res;;
        return res;
    };


    if (mode == 1) return l_my();
    return l_medium();
}

void Solution::lc_3091_test(){
    vector< pair<int,int> >
        data ={
            {11,5},
            {1,0},
            {41,11},
            {333,35},
            {2,1},
            {3,2},
            {4,2},
            {5,3},
            {6,3},
            {8,4},
            {9,4},
            {555,46},
            {556,46},
            {557,46},
            {558,46},
            {559,46},
            {560,46},
            {561,46},
            {562,46},
            {563,46},
            {564,46},
            {565,46},
            {566,46},
        };
    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            // auto inp = v.first;
            const auto res = std::to_string(lc_3091(v.first, m));
            const auto shouldBe = std::to_string(v.second);
            const auto note = std::to_string(v.first);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

int Solution::lc_150(vector<string>& tokens, int mode){

    // stack version
    auto l_st = [&tokens](){
        if (std::size(tokens) == 0
        //     && !std::isdigit(tokens[0][0])
            ){

            return 0;
        }
        auto st = std::make_unique<std::stack<int>>();
        st->push(0); st->push(0);   // case {"+","+","+"}
        auto op1{0}, op2{0};
        // auto cur{0};
        for (auto i{std::cbegin(tokens)}; i != std::cend(tokens); std::advance(i,1)){
            // cout << " i=" << *i;
            if (std::isdigit((*i)[std::size(*i)-1])){
                st->push(std::stoi(*i));
                continue;
            }

            op2 = st->top();
            st->pop();
            op1 = st->top();
            st->pop();
            if (st->empty()) st->push(0);

            if ((*i).compare("+") == 0) st->push(op1+op2);
            else if ((*i).compare("-") == 0) st->push(op1-op2);
            else if ((*i).compare("*") == 0) st->push(op1*op2);
            else if ((*i).compare("/") == 0) st->push(op1/op2);

        }
        // cout << endl;

        return st->top();
    };

    auto l_iap = [&tokens](){
        // cout << "vec=" << vkstd::toString(tokens) << endl;
        // if (std::size(tokens) == 1) {
        //     if(std::isdigit(tokens[0][tokens[0].size()-1]))
        //         return std::stoi(tokens[0]);
        //     return 0;
        // }

        // cout << "000" << endl;
        auto posA{-1}, posB{-1};
        auto valA{0}, valB{0};

        auto tmp{0};
        auto op{0};
        for (auto i{0}; i < std::size(tokens); ++i){
            if (tokens[i].compare("+") == 0) op = 1;
            else if (tokens[i].compare("-") == 0) op = -1;
            else if (tokens[i].compare("*") == 0) op = 2;
            else if (tokens[i].compare("/") == 0) op = 3;
            else {
                posA = posB;
                posB = i;
                continue;
            }
            if (posA >=0 && tokens[posA].empty()){
                for (posA = posB-1; posA >= 0 && (tokens[posA].empty() || !std::isdigit(tokens[posA][tokens[posA].size()-1])); --posA){;}
            }
            // cout << "555" << " i=" << i << " A=" << posA << " B=" << posB << " vec=" << vkstd::toString(tokens) << endl;
            valA = posA < 0 ? 0 : std::stoi(tokens[posA]);
            valB = posB < 0 ? 0 : std::stoi(tokens[posB]);
            if (posA >= 0) tokens[posA] = std::string("");
            if (posB >= 0) tokens[posB] = std::string("");
            // cout << "777" << endl;

            switch (op) {
            case 2: tmp = valA * valB; break;
            case 3: tmp = valA / valB; break;
            default:
                tmp = valA + op * valB;
                break;
            }
            tokens[i] = std::to_string(tmp);
            posB = i;

        }
        // cout << "vec=" << vkstd::toString(tokens) << endl;

        return std::stoi(tokens[std::size(tokens)-1]);
    };

    if (mode == 1) return l_iap();

    return l_st();
    // return l_fwd();
}

void Solution::lc_150_test(){
    vector< pair<std::vector<std::string>,int> >
        data ={
            {{"2","1","+","3","*"}, 9},
            {{"4","13","5","/","+"}, 6},
            {{"10","6","9","3","+","-11","*","/","*","17","+","5","+"}, 22},
            {{"1","2","4","+","+"}, 7},
            {{"5","3","2","*","+"}, 11},
            {{"6","3","/"}, 2},
            {{"2","3","4","-","-"}, 3},
            {{"3"}, 3},
            {{"+","+","-"}, 0},
            {{"+"}, 0},
            {{"3","11","+","5","-"},9},
                };
    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (const auto &v: data) {
            // auto p = make_unique<Node<int>*>(n);
            auto inp = v.first;
            auto res = std::to_string(lc_150(inp,m));
            auto shouldBe = std::to_string(v.second);
            auto note = vkstd::toString(v.first);
            prn(res, shouldBe, note);
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }

}

int Solution::lc_224(string s){

    auto si{std::cbegin(s)};

    auto lcalc = [&si, &s](auto&& self/*, auto tmp*/) mutable ->int {
        auto lres{0};
        int coef{1};    // coef 1\-1 for +|-
        auto crnt{0};
        // if (tmp>4) return lres;

        for (; si != std::cend(s); ++si){
            // cout << "000  *si=" << *si << endl;
            if ( static_cast<int>(*si) > 47 && static_cast<int>(*si) < 58 ) crnt = 10 * crnt +(*si - '0');
            else if (*si == ' ') continue;
            else if (*si == '+') {
                // cout << "555 *si="<<*si<< " lres="<<lres<<" crnt="<<crnt<<" coef="<<coef<<endl;
                lres += coef * crnt;
                crnt = 0;
                coef = 1;
            }
            else if (*si == '-') {
                lres += coef * crnt;
                crnt = 0;
                coef = -1;
            } else if (*si == ')') break;
            else if (*si == '(') {
                // cout << "recursion lres =" << lres << endl;
                std::advance(si,1);
                lres += coef * self(self/*,++tmp*/);
            }

        }

        return lres + coef * crnt;
    };

    return lcalc(lcalc/*,0*/);
}

void Solution::lc_224_test(){
    vector< pair<string,int> >
        data ={
                {"1 + 1", 2},
            {" 2-1 + 2 ", 3},
            {"(2)", 2},
            {"-(2)", -2},
            {"(1+(4+5+2)-3)+(6+8)", 23},
            {"(1-(4+5-2)-3)+(6+8)", 5},
            {"-(1-(4+5-2)-3)+(6+8)", 23},
            // {, },
                // {, },
                };
    for (const auto &v: data) {
        // auto p = make_unique<Node<int>*>(n);
        auto res = lc_224(v.first);
        cout << (res == v.second ? "+++ " : "\033[31m--- ")     // \033[32m green
             << "data= " << v.first
             << " res=" << res
             << " target= " << v.second
             << "\033[0m" << endl;
    }

}


int Solution::lc_227(string s){
    auto res{0};
    auto a{0},z{0}; // numbers current, extra(*|/)
    auto op{0};      // previous operation +|->0 *>3 />4
    int coef{1};    // coef 1\-1 for +|-

    auto lcalc = [](auto la, auto lz, auto lop, auto lc){
        auto lres{0};
        if (lop == 0) lres = lc * la;
        else if (lop == 3) lres = lc * la * lz;
        else if (lop == 4) lres = lc * la / lz;
        return lres;
    };

    for (auto i{std::cbegin(s)}; i != std::cend(s); ++i){
        // cout << *i;
        // if (*i=='0' || *i=='1' || *i=='2' || *i=='3' || *i=='4' || *i=='5' || *i=='6' || *i=='7' || *i=='8' || *i=='9' ) {
        if ( static_cast<int>(*i) > 47 && static_cast<int>(*i) < 58 ) {
            if (op==3 || op==4){
                z *= 10;
                z += (*i - '0');
            } else {
                a *= 10;
                a += (*i - '0');
            }
            // cout <<"(" << a << " " << z << ")";
        } else if (*i == ' '){
            continue;
        } else if (*i == '+'){
            // cout << " a=" << a << " z=" << z << endl;
            res += lcalc(a,z,op,coef);
            a = 0;
            op = 0;
            coef = 1;
            // cout <<"P";
        } else if (*i == '-'){
            res += lcalc(a,z,op,coef);
            a = 0;
            op = 0;
            coef = -1;
        } else if (*i == '*'){
            if (op == 3) a *= z;
            else if (op == 4) a /= z;
            z = 0;
            op = 3;
        } else if (*i == '/'){
            if (op == 3) a *= z;
            else if (op == 4) a /= z;
            z = 0;
            op = 4;
        }

        // cout <<", ";
    }
    res += lcalc(a,z,op,coef);


    // cout << " a=" << a << " z=" << z << " res=" << res << endl;
    return res;
}

void Solution::lc_227_test(){
    vector< pair<string,int> >
        data ={
            {"5-3 + 2 +1", 5},
            {"3+2+1", 6},
            {"3+2*2 +4", 11},
            {"3+4/2 +4", 9},
            {"3+4/2 -4", 10},
            {" 3/2 ", 1},
            {" 3+5 / 2 ", 5},
            {" 2*3*4 +6 / 2 ", 27},
            {" 2*3*4/12 +6 / 2-1 ", 4},
            // {, },
            {"35+24/12", 37},
            };
    for (const auto &v: data) {
        // auto p = make_unique<Node<int>*>(n);
        auto res = lc_227(v.first);
        cout << (res == v.second ? "+++ " : "\033[31m--- ")     // \033[32m green
             << "data= " << v.first
             << " res=" << res
             << " target= " << v.second
            << "\033[0m" << endl;
    }

}

int Solution::lc_1855(vector<int>& nums1, vector<int>& nums2, int mode){
    // iterators way
    // about two times slower then counters way
    auto l_iter = [&nums1, &nums2](){
        std::ptrdiff_t lres{0};
        std::ptrdiff_t dist{0};
        for (auto n1i{std::cbegin(nums1)}; n1i != std::cend(nums1); ++n1i ) {
            dist = std::distance(std::cbegin(nums1), n1i);
            if ((dist < std::size(nums2)) && *n1i <= *std::next(std::cbegin(nums2), dist)) {
                auto it = std::find_if(std::crbegin(nums2), std::next(std::crend(nums2),-(dist+1)),
                                       [&n1i](const int& v){return *n1i <= v;}
                                       );
                // cout << " 2200 n1i=" << *n1i << " it=" << *it << " dist=" << std::distance(it, std::crend(nums2))  << endl;

                if (lres < ((std::distance(it, std::crend(nums2)) - 1)- dist))
                    lres = ((std::distance(it, std::crend(nums2)) - 1) - dist);

            }
        }
        return lres;
    };

    // counters way
    // about two times faster then iterators way
    auto l_count = [&nums1, &nums2](){
        size_t lres{0};
        size_t n1len = std::size(nums1);
        size_t n2len = std::size(nums2);
        size_t left{0}, right{0};
        for (auto n1i{0}; n1i < n1len; ++n1i ) {

            if (n1i < n2len && nums1[n1i] <= nums2[n1i]){
                left = n1i; right = n2len - 1;
                // auto i{0};
                while (/*i < 15 && */ ((right - n1i) > lres) && ((right - left) > 1)){
                    // ++i;
                    // cout << " 444 BEFORE lf=" << left << " rt=" << right << endl;
                    if (nums1[n1i] <= nums2[left + (right-left)/2]){
                        left += (right-left)/2;
                    } else right -= (right-left)/2;
                    // cout << " 777 AFTER lf=" <<left << " rt=" << right << endl;
                }
                if (nums1[n1i] <= nums2[right]) left = right;
                // cout << "000 n1/n2=" << to_string(nums1[n1i]) << "/" << to_string(nums2[n1i])
                //      << "(" << to_string(n1i) << "/" << left << ")"
                //      <<" lf=" << left << " rt=" << right
                // << ", " << endl;
                if (lres < (left - n1i)) lres = left - n1i;
            }
        }
        return lres;
    };

    int res{0};

    if (mode == 1) res = static_cast<int>(l_count());
    else res = static_cast<int>(l_iter());

    return res;
}

void Solution::lc_1855_test(){
    vector< tuple<vector<int>, vector<int>, int > > data =
        {
         { {55,30,5,4,2}, {100,20,10,10,5}, 2},
         { {2,2,2}, {10,10,1}, 1},
         { {30,29,19,5}, {25,25,25,25,25}, 2},
         { {99998,99997,99994,99993,99990,99989,99987,99982,99978,99977,99969,99965,99965,99962,99962,99958,99953,99952,99950,99946,99944,99942,99940,99940,99937,99936,99935,99933,
             99931,99931,99926,99925,99922,99922,99917,99913,99911,99909,99908,99906,99900,99898,99895,99894,99893,99891,99887,99887,99887,99886,99885,99882,99882,99881,99881,99879,
             99879,99876,99873,99870,99868,99861,99860,99857,99855,99855,99853,99852,99851,99849,99848,99848,99847,99846,99845,99832,99829,99827,99827,99826,99826,99823,99818,99817,
             99807,99804,99804,99802,99800,99800,99797,99797,99792,99789,99789,99789,99787,99786,99786,99783,99779,99778,99776,99775,99772,99770,99768,99768,99767,99758,99756,99756,
             99756,99755,99753,99751,99749,99747,99744,99742,99740,99737,99733,99732,99731,99725,99725,99721,99716,99715,99714,99709,99708,99707,99704,99703,99701,99700,99700,99699,
             99699,99699,99697,99697,99694,99694,99692,99691,99688,99683,99679,99676,99674,99672,99671,99670,99669,99669,99668,99668,99668,99667,99666,99662,99661,99658,99658,99654,
             99654,99651,99649,99647,99645,99642,99641,99637,99633,99625,99623,99621,99617,99614,99609,99607,99606,99605,99604,99603,99596,99590,99589,99586,99584,99582,99581,99580,
             99578,99577,99567,99567,99564,99563,99562,99560,99558,99555,99551,99546,99538,99537,99537,99535,99532,99530,99529,99529,99528,99528,},
         {100000,100000,100000,100000,99999,99999,99999,99999,99999,99998,99998,99998,99997,99997,99997,99996,99996,99996,99996,99996,99995,99995,99994,99994,99994,99994,99993,99993,
             99993,99993,99993,99993,99992,99991,99991,99990,99990,99990,99990,99990,99989,99989,99989,99989,99988,99988,99988,99988,99988,99988,99988,99988,99988,99987,99987,99987,
             99987,99986,99986,99986,99986,99986,99986,99986,99986,99986,99986,99985,99985,99985,99984,99984,99983,99983,99983,99983,99983,99983,99983,99982,99982,99982,99981,99981,
             99981,99981,99980,99980,99980,99980,99980,99980,99979,99979,99979,99979,99979,99979,99979,99978,99978,99978,99978,99978,99977,99977,99977,99977,99977,99977,99977,99977,
             99977,99977,99976,99976,99976,99976,99976,99975,99975,99975,99975,99975,99974,99974,99974,99974,99973,99973,99973,99973,99973,99973,99973,99972,99972,99972,99972,99971,
             99971,99971,99971,99971,99971,99971,99970,99970,99970,99970,99970,99969,99969,99969,99969,99969,99968,99967,99967,99967,99966,99965,99965,99965,99965,99965,99965,99964,
             99964,99964,99963,99963,99963,99963,99963,99963,99963,99962,99962,99962,99962,99962,99962,99962,99962,99961,99961,99961,99961,99960,99960,99960,99960,99959,99959,99959,
             99959,99959,99959,99958,99958,99958,99958,99958,99958,99957,99957,99957,99957,99956,99956,99956,99956,99956,99955,99955,99955,99955,99955,99954,99954,99954,99953,99953,
             99953,99953,99952,99952,99952,99952,99952,99951,99951,99950,99950,99950,99950,99949,99949,99949,99948,99948,99948,99948,99948,99947,99947,99947,99946,99946,99946,99946,
             99946,99945,99945,99945,99945,99945,99944,99944,99944,99944,99944,99944,99944,99944,99944,99944,99943,99943,99943,99942,99942,99942,99942,99942,99942,99941,99941,99940,
             99940,99940,99940,99940,99940,99940,99940,99940,99939,99939,99939,99939,99939,99939,99938,99938,99937,99937,99937,99937,99936,99936,99936,99936,99936,99936,99935,99935,
             99934,99934,99933,99933,99933,99933,99933,99933,99931,99931,99931,99931,99931,99931,99931,99931,99931,99930,99930,99930,99930,99930,99929,99928,99928,99928,99928,99928,
             99928,99928,99928,99928,99927,99927,99926,99926,99925,99925,99925,99925,99925,99925,99925,99925,99924,99924,99924,99924,99923,99923,99923,99923,99922,99922,99922,99921,
             99921,99921,99921,99920,99920,99920,99919,99919,99919,99919,99919,99918,99918,99918,99917,99917,99917,99917,99917,99917,99916,99916,99916,99916,99916,99915,99915,99915,
             99915,99914,99914,99914,99914,99913,99913,99912,99912,99912,99911,99911,99911,99911,99911,99910,99910,99910,99910,99909,99909,99909,99909,99908,99908,99908,99908,99908,
             99908,99908,99908,99907,99907,99907,99907,99906,99906,99906,99906,99906,99905,99905,99905,99905,99904,99904,99904,99904,99904,99904,99903,99903,99903,99903,99902,99902,
             99902,99902,99902,99901,99901,99901,99901,99901,99901,99899,99899,99898,99898,99898,99897,},
         420},
         };
    // auto uptr = std::make_unique<Lc_189>();
    // std::string s{"abcdefg"};
    // std::cout << "BEFORE s=" << s << std::endl;
    // uptr->reverseStr(s, 2);

    // std::cout << "AFTER s=" << s << std::endl;

    // return;
    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (auto v: data) {
            // cout << "1 or=" << vkstd::toString(get<0>(v)) << " k=" << std::to_string(get<1>(v))<< " sB=" << vkstd::toString(get<2>(v)) << std::endl;
            auto orig = stringify(get<0>(v));
            // const std::string ti =  std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"};
            auto res = lc_1855(get<0>(v),get<1>(v),m);
            auto shouldBe = get<2>(v);
            std::cout << ((res == shouldBe) ? "+++ " : "--- ")
                      << " nums1= " << orig
                      << " nums2= " << stringify(get<1>(v))
                      << " res= " << to_string(res)
                      << " sB=" << to_string(shouldBe)
                      << std::endl;
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }


}


// static members
// s-show size; e-add endl
string Solution::stringify(vector<int>& vec, bool s){
    std::string res{""};
    auto len = 0;
    for( auto v : vec){
        ++len;
        res += std::to_string(v) + ",";
        // res += (res==""?"":",");
        // res += v + '0';
    }
    // res = "["+res+"]"
    // + "(" + to_string(len)+")"
    // ;
    return "["+res+"](" +( s ? to_string(len) : "")+")";
}
