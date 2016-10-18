//
// Created by Ivana on 10/18/2016.
//
#include <gtest/gtest.h>
#include "../../src/KeyDetector.h"
#include "../../src/key/Key.h"

TEST(keyTest, test_eq) {
    //std::string test = Key::getKey("Gm")->toString();
    EXPECT_EQ("test", "G ionaian");
}