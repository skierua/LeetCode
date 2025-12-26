//
//  main.cpp
//  LeetCode
//
//  Created by Iurii Vasurchak on 15.12.2025.
//

#include <iostream>
#include "node.h"
#include "solution.h"

//#include "test.h"
#include "vkstd.h"

int main(int argc, const char * argv[]) {
    // DONE 31, 81, 189*, 344, 556, 2772

    // TEST_31();
    // TEST_81(*(std::make_unique<Lc_81>()));
    // TEST_189();
    // TEST_282();
    // TEST_344();
    // TEST_497();
    // TEST_519();
    // TEST_541();
    // TEST_556();
    // TEST_2772();
    // TEST_2772(std::move(*std::make_unique<Lc_2772>()));

    auto sol = std::make_unique<Solution>();
            // Solution sol;

    sol->lc_81_test();
//   sol->lc_1027_test();
    // sol->lc_658_test();
    // sol->lc_400_test();
    // sol->lc_825_test();
    // sol->lc_792_test();
    // sol->lc_300_test();
    // sol->lc_209_test();
    // sol->lc_3153_test();
    // sol->lc_477_test();
    // sol->lc_397_test();
    // sol->lc_318_test();
    // sol->lc_1191_test();
    // sol->lc_2266_test();
    // sol->lc_91_test();
    // sol->lc_127_test();
    // sol->lc_433_test();
    // sol->lc_1371_test();
    // sol->lc_726_test();
    // sol->lc_394_test();
    // sol->lc_2971_test();
    // sol->lc_611_test();
    // sol->lc_3091_test();
    // sol->lc_150_test();
    // sol->lc_224_test();
    // sol->lc_227_test();
    // sol->lc_1855_test();
    // sol->mlc_2095_test();
    // sol->mlc_143_test();
    // sol->mlc_151_test();
    // sol->mlc_82_test();
    // sol->elc_83_test();
    // Lc_81 lc81;
    // auto p = std::make_unique<Lc_81>();


/*
    Lc_519 lc519 ( 1,1);
    for (auto i{0}; i < 3; ++i)
    lc519.flip();
    lc519.reset();
    lc519.flip();
*/

 //    return 0;
    std::cout << "Hello, World!\n";
    return EXIT_SUCCESS;
}
