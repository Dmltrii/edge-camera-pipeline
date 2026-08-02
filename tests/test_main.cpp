// tests/test_main.cpp
#include <gtest/gtest.h>
#include <algorithm>   // для std::reverse — я забыл его в прошлый раз, лови
#include <string>

std::string reverseString(std::string s) {
    std::reverse(s.begin(), s.end());
    return s;
}

TEST(ReverseStringTest, HandlesBasicInput) {
    EXPECT_EQ(reverseString("abc"), "cba");
}
