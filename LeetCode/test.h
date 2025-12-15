#ifndef TEST_H
#define TEST_H

#include <atomic>
#include <thread>
// #include <thread>

#include <chrono>
#include <fstream>
#include <ranges>
#include <string>
#include <tuple>

#include "solution.h"
#include "lc_81.h"
#include "lc_189.h"
#include "lc_282.h"
#include "lc_344.h"
#include "lc_497.h"
#include "lc_519m.h"
#include "lc_541.h"
#include "lc_2772.h"

using namespace std;


// namespace lc_test {

string vecToString(const vector<int>& vec) {

    string rslt = "";
    auto count = 0;
    for( const auto &v : vec){
        ++count;
        rslt += (rslt.empty() ? "" : ",") + std::to_string(v);
        // rslt += (rslt==""?"":",");
        // rslt += v + '0';
    }
    return "["+rslt+"](" + to_string(count)+")";

}
// string Solution::vecToString(const vector<int>& vec) {

//     string rslt = "";
//     auto count{0};
//     for( const auto &v : vec){
//         ++count;
//         rslt += (rslt.empty() ? "" : ", ") + std::to_string(v);
//         if (count > 10) {
//             rslt += ", ...";
//             break;
//         }
//     }
//     return "["+rslt+"](" + to_string(std::size(vec))+")";

// }

string vecToString(const vector<std::string>& vec) {

    string rslt = "";
    auto count = 0;
    for(const auto &v : vec){
        ++count;
        rslt += (rslt.empty() ? "" : ",") + v;
    }
    return "["+rslt+"](" + to_string(count)+")";

}

string vecToString(vector<char>& vec) {
    string rslt = "";
    auto count = 0;
    for( const auto &v : vec){
        ++count;
        rslt += (rslt.empty() ? "" : ",") + std::string(1,v);
    }
    return "["+rslt+"](" + to_string(count)+")";

}

void TEST_prn( std::string &res, std::string &shouldBe, std::string &note ) {

    std::cout << ((res.compare(shouldBe)==0 ) ? "+++" : "\033[31m---")     // \033[32m green
              << " res= " << res
              << " sB=" << shouldBe
              << " orig= " << note
              << "\033[0m" << std::endl;

}
// TODO
vector<int> vectFromRaw(const std::string& filePath = "./data/vec1.txt") {
    vector<int> res{};
    std::ifstream file(filePath); // Open the file for reading

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return res;; // Return an empty string or handle the error appropriately
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    file.close(); // Close the file stream

    // res = std::initializer_list<int>(content);
    std::cout << "content: " << content << std::endl;
    return res;
}

void TEST_282(){
    vector< tuple<std::string, int, vector<std::string> > > data =
        {
        { "123", 6, {"1*2*3","1+2+3"} },
        { "232", 8, {"2*3+2","2+3*2"} },
        { "3456237490", 9191, {}},
        // { , },
         };

    auto uptr = std::make_unique<Lc_282>();

    for (const auto& v: data) {
        // auto orig = v.first;
        // cout << "ORIG "  << orig << endl;
        auto res = uptr->addOperators(std::get<0>(v), std::get<1>(v));
        std::sort(std::begin(res), std::end(res));
        auto sres = vecToString(res);
        auto shouldBe = vecToString(std::get<2>(v));
        auto note = std::get<0>(v) + " " + std::to_string(std::get<1>(v));

        TEST_prn(sres, shouldBe, note );
    }
}

void TEST_497(){
    vector<vector<vector<int> > > data ={
        {{-2, -2, 1, 1},{2, 2, 4, 6}},
        {{-2, -2, 1, 1}},

    };
    auto i{0};
    auto uptr = std::make_unique<Lc_497>(data[i]);
    string inp{""};
    for (const auto &v : data[i]) inp += vecToString(v);
    auto res = vecToString(uptr->pick());
    for (auto v: {1,2,3,4}) res += "," + vecToString(uptr->pick());

    auto shouldBe = string("whatever");
    TEST_prn(res, shouldBe, inp);
}


void TEST_556(){
    vector< pair<int, int > > data =
        {
        { 12, 21},
         { 123, 132},
         { 41321, 42113},
         { 42543321, 43122345},
        { 42543321, 43122345},
        { 42543321, 43122345},
        { 42543321, 43122345},
        { 42543321, 43122345},
        { 42543321, 43122345},
         { 4321, -1},
         { 2147483640, -1},     // INT_MAX
         };
    auto uptr = std::make_unique<Solution>();
    for (const auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();

        for (const auto& v: data) {
            auto orig = v.first;
            // cout << "ORIG "  << orig << endl;
            auto res = uptr->lc_556(v.first, m);
            auto shouldBe = v.second;
            // cout << "AFTER "  << vecToString(v.first) << endl << endl;
            std::cout << ((res == shouldBe) ? "+++ " : "--- ")
                      << "orig= " << std::to_string(orig)
                      << " res= " << std::to_string(res)
                      << " sB=" << std::to_string(shouldBe)
                      << std::endl;
        }
    const auto t2 = std::chrono::steady_clock::now();
    std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }
}


void TEST_31(){
    vector< pair<vector<int>, vector<int> > > data =
    {
        { {1,2,3}, {1,3,2}},
        { {4,1,3,2,1}, {4,2,1,1,3}},
        { {4,2,5,4,3,3,2,1}, {4,3,1,2,2,3,4,5}},
        { {4,3,2,1}, {1,2,3,4}},
    };
    auto uptr = std::make_unique<Solution>();
    for (auto v: data) {
        auto orig = vecToString(v.first);
        // cout << "ORIG "  << orig << endl;
        uptr->lc_31(v.first);
        auto res = vecToString(v.first);
        auto shouldBe = vecToString(v.second);
        // cout << "AFTER "  << vecToString(v.first) << endl << endl;
        std::cout << ((res == shouldBe) ? "+++ " : "--- ")
                  << "orig= " << orig
                  << " res= " << res
                  << " sB=" << shouldBe
                  << std::endl;
    }
}

void TEST_189(){
    vector< tuple<vector<int>, int, vector<int> > > data =
        {
        { {1,2,3,4,5,6,7}, 3, {5,6,7,1,2,3,4}},
        // { {1,2,3,4,5,6,7}, 3, {1,2,3,4,5,6,7}},
        { {1,2,3,4,5,6,7,8,9,10,11}, 4, {8,9,10,11,1,2,3,4,5,6,7}},
        { {1,2,3,4,5,6,7}, 1, {7,1,2,3,4,5,6}},
        { {1,2,3,4,5,6,7,8,9,10,11}, 5, {7,8,9,10,11,1,2,3,4,5,6}},
        { {1,2,3,4,5,6,7,8,9,10,11}, 4, {8,9,10,11,1,2,3,4,5,6,7}},
        { {-1,-100,3,99}, 2, {3,99,-1,-100}},
        { {-1}, 2, {-1}},
        { {}, 5, {}},
        };
    auto uptr = std::make_unique<Lc_189>();
    // std::string s{"abcdefg"};
    // std::cout << "BEFORE s=" << s << std::endl;
    // uptr->reverseStr(s, 2);

    // std::cout << "AFTER s=" << s << std::endl;

    // return;
    for (auto m: {0,1}){
        std::cout << "mode=" << std::to_string(m) << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        for (auto v: data) {
            // cout << "1 or=" << vecToString(get<0>(v)) << " k=" << std::to_string(get<1>(v))<< " sB=" << vecToString(get<2>(v)) << std::endl;
            auto orig = vecToString(get<0>(v));
            uptr->rotate(get<0>(v), get<1>(v));
            // const std::string ti =  std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"};
            auto res = vecToString(get<0>(v));
            // get<0>(v);
            auto shouldBe = vecToString(get<2>(v));
            std::cout << ((res == shouldBe) ? "+++ " : "--- ")
                      << "orig= " << orig
                      << " k= " << to_string(get<1>(v))
                      << " res= " << res
                      << " sB=" << shouldBe
                      << std::endl;
        }
        const auto t2 = std::chrono::steady_clock::now();
        std::cout << std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"}<< std::endl;
    }


}

void TEST_541(){
    vector< tuple<string, int, string> > data =
    {
        {"abcdefg", 2, "bacdfeg"},
        {"abcd", 2, "bacd"},
        {"ab", 3, "ba"},
        {"abcdefg", 3, "cbadefg"},
        {"ab", 1, "ab"},
    };
    auto uptr = std::make_unique<Lc_541>();
    // std::string s{"abcdefg"};
    // std::cout << "BEFORE s=" << s << std::endl;
    // uptr->reverseStr(s, 2);

    // std::cout << "AFTER s=" << s << std::endl;

    // return;
    for (auto v: data) {
        // cout << "BEFORE rev=" << vecToString(v.first) << std::endl;
        auto orig = get<0>(v);
        auto reverse = uptr->reverseStr(get<0>(v), get<1>(v));
        // get<0>(v);
        // auto shouldBe = get<2>(v);
        // cout << "rev=" << vecToString(v.first) << std::endl;
        std::cout << ((reverse == get<2>(v)) ? "+++ " : "--- ")
                  << "orig= " << orig
                  << " reverse= " << reverse
                  << " shouldBe=" << get<2>(v)
                  << std::endl;
    }
}


void TEST_344(){
    vector< pair< vector<char>,  vector<char> > >  data =
    {
        {{'h','e','l','l','o'},{'o','l','l','e','h'}},
        {{'H','a','n','n','a','h'},{'h','a','n','n','a','H'}},
    };
    auto uptr = std::make_unique<Lc_344>();
    for (auto v: data) {
        // cout << "BEFORE rev=" << vecToString(v.first) << std::endl;
        auto orig = vecToString(v.first);
        uptr->reverseString(v.first);
        auto reverse = vecToString(v.first);
        auto shouldBe = vecToString(v.second);
        // cout << "rev=" << vecToString(v.first) << std::endl;
        std::cout << ((reverse == shouldBe) ? "+++ " : "--- ")
             << "orig= " << orig
             << " reverse= " << reverse
             << " shouldBe=" << shouldBe
             << std::endl;
    }
}


void TEST_519(){
    auto row = 3, col = 1;
    auto uptr = std::make_unique<Lc_519>(row,col);
    for (auto i{0}; i < 3; ++i)
        uptr->flip();
    uptr->reset();
    uptr->flip();

}


void TEST_81(Lc_81& T){

    // Lc_81 tst;

    vector< pair<pair<vector<int>,int>, bool> >
        data = {
                {{{2,5,6,0,0,1,1,1,1,1,1,1,2}, 0}, true }
                ,{{{2,5,6,0,0,1,2},3}, false }
                ,{{{2},2}, true }
                ,{{{2},3}, false }
                ,{{{2,2},2}, true }
                ,{{{2,2},3}, false }
                ,{{{2,5,6,0,0,1,1,1,1,1,1,1,2}, 6}, true }
                ,{{{2,5,6,0,0,1,1,1,1,1,1,1,2}, 7}, false }
                ,{{{1,0,1,1,1},0}, true },
                {{{1,1,1,0,1},0}, true },
                {{{1,3,1,1,1},3}, true },
                {{{1,1,1,3,1},3}, true },
                {{{2,1,1,2,2,2,2},1}, true },
                };
    // string res{""};
    auto comp{false} ;
    for (auto &v: data) {
        comp = T.search(v.first.first, v.first.second );
        cout << ((comp ? 1 : 0) == (v.second ? 1 : 0) ? "+++ " : "--- ")
             << "data= " << vecToString(v.first.first)
             << " t= " << v.first.second
             << " res=" << (comp ? "TRUE " : "FALSE ")
             << endl;
    }

}


void TEST_2772(){
    vector< pair<pair<vector<int>,int>, bool> > data =
        {
            {{{2,2,3,1,1,0},3}, true },
            {{{1,3,1,1},2}, false },
            {{{2,2,3,1,1,0},1}, true },
            {{{2,3,4,5},4}, false },
            {{{0,72},2},false},
            {{{1,2,3,4,5,6,7,8,9,10},3},false}
        };
    std::vector<int> tvec(100000);
    std::iota(tvec.begin(), tvec.end(), 1);

    // unique_ptr<Lc_2772> uptr = std::make_unique<Lc_2772>();

    std::atomic<bool> stopFlag(false);
    std::string note{""};

    auto lambdaTest = [&data, &tvec, &stopFlag, &note](std::function<bool(vector<int>&, int)> fn){
        auto res{false} ;
        // std::string note{fn.target_type().name()};
        // std::string note{n};
        // note += std::string{"\n"};
        const auto t1 = std::chrono::steady_clock::now();
        for (auto &v: data) {
            // res = false;
            // if (stopFlag) break;
            // cout << "LAMBDA stopFlag=" << stopFlag << endl;
            if (!stopFlag) res = fn(v.first.first, v.first.second ); else res = false;
            note += ((res ? 1 : 0) == (v.second ? 1 : 0) ? "+++ " : "--- ")
                 + std::string{"data= "} + vecToString(v.first.first)
                   + std::string{" t= "} + std::to_string(v.first.second)
                   + std::string{" res="} + std::string{(res ? "TRUE " : "FALSE ")}
                 + std::string{"\n"};

        }
        // if (!stopFlag) {
            if (!stopFlag) res = fn(tvec, 40000 );
                    else res = false;
            note += std::string{((res ? 1 : 0) == (0) ? "+++ " : "--- ")}
                    + std::string{"data= [iota::100000]"}
                    + std::string{" t= 40000"}
                    + std::string{" res="} + std::string{(res ? "TRUE " : "FALSE ")}
                    + std::string{"\n"};
        // }
        const auto t2 = std::chrono::steady_clock::now();
        const std::string ti =  std::string{" time="} + to_string(chrono::duration_cast<chrono::microseconds>(t2-t1).count()) + std::string{" μs\n"};
        note += ti;
        if (stopFlag) note += std::string("FAILED !!! Time estimated.\n");
        else note += std::string("PASSED ALL TESTS\n");
        // cout << "END LAMBDA stopFlag=" << stopFlag << endl;
        // cout << note;
        return;
    };

    // note = std::string("checkArray_m1\n");
    // auto ff = std::bind(&Lc_2772::checkArray_n1, checkArray_n1);
    // std::thread tmpwork(lambdaTest, ff);
    // tmpwork.join();
    // cout << note  << endl;
    // cout << "uptr=" << uptr->checkArray_m1  << endl;
    // return;


    std::vector< std::pair< std::function<bool(vector<int>&, int)>, std::string > > fnlist{
        {Lc_2772::checkArray_m1, std::string("checkArray_m1")},
                {Lc_2772::checkArray_n1, std::string("checkArray_n1")},
                        {Lc_2772::checkArray_n2, std::string("checkArray_n2")},
    };
    std::thread work, stopper;
    for (auto &fn : fnlist) {
        stopFlag = false;
        note = fn.second + std::string("\n");
        stopper = std::thread ([&stopFlag]()
                            {
                                std::this_thread::sleep_for(std::chrono::microseconds(10000));
                                stopFlag.store(true);
                                // cout << "SET stopFlag=" << stopFlag << endl;
                            });
        work = std::thread(lambdaTest, fn.first);

        // cout << "BEFORE join stopFlag=" << stopFlag << endl;
        stopper.join();
        work.join();
        // cout << "AFTER join stopFlag=" << stopFlag << endl;
        cout << note  << endl;

    }

    // std::thread th2(lf, Lc_2772::checkArray_n1, "checkArray_n1");
    // th2.join();
    // cout << endl;

    // std::thread th3(lf, Lc_2772::checkArray_n2, "checkArray_n2");
    // th3.join();
    // cout << endl;

}


// }

#endif // TEST_H
