//
// Created by Ivana on 10/18/2016.
//
#include <gtest/gtest.h>
#include "../../src/KeyDetector.h"
#include "../../src/key/Key.h"

TEST(keyTest, test_eq) {
//    std::string test = Key::getKey("Gm")->toString();
//    EXPECT_EQ(test, "G ionian");

    // Test minor - Am
    Key *key = Key::getKey("Am");
    EXPECT_EQ(key->getKeyCode()->toString(true), "08A");
    EXPECT_EQ(key->getKeyCode()->toString(), "08A");
    EXPECT_EQ(key->getKeyNotationFlat(), "Am");
    EXPECT_EQ(key->getKeyNotationSharp(), "Am");
    EXPECT_EQ(key->getRootValue(), 0.0);
    EXPECT_EQ(key->isMinor(), true);
}