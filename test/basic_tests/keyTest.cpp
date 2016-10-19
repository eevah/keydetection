//
// Created by Ivana on 10/18/2016.
//
#include <gtest/gtest.h>
#include "../../src/KeyDetector.h"
#include "../../src/key/Key.h"

TEST(keyTest, test_eq) {
    std::string test = Key::getKey("G")->toString();
    EXPECT_EQ(test, "G ionian");

    // Test minor - Am
    Key *key = Key::getKey("Am");
    EXPECT_EQ(key->getKeyCode()->toString(true), "08A");
    EXPECT_EQ(key->getKeyCode()->toString(), "08A");
    EXPECT_EQ(key->getKeyNotationFlat(), "Am");
    EXPECT_EQ(key->getKeyNotationSharp(), "Am");
    EXPECT_EQ(key->getRootValue(), 0.0);
    EXPECT_EQ(key->isMinor(), true);

    // Test major - A
    key = Key::getKey("A");
    EXPECT_EQ(key->getKeyCode()->toString(true), "11B");
    EXPECT_EQ(key->getKeyCode()->toString(), "11B");
    EXPECT_EQ(key->getKeyNotationFlat(), "A");
    EXPECT_EQ(key->getKeyNotationSharp(), "A");
    EXPECT_EQ(key->getRootValue(), 0.0);
    EXPECT_EQ(key->isMinor(), false);

    // Test minor - Fm
    key = Key::getKey("Fm");
    EXPECT_EQ(key->getKeyCode()->toString(true), "04A");
    EXPECT_EQ(key->getKeyCode()->toString(), "04A");
    EXPECT_EQ(key->getKeyNotationFlat(), "Fm");
    EXPECT_EQ(key->getKeyNotationSharp(), "Fm");
    EXPECT_EQ(key->getRootValue(), 8.0);
    EXPECT_EQ(key->isMinor(), true);

    // Test key code
    key = Key::getKey("04A");
    EXPECT_EQ(key->getKeyCode()->toString(true), "04A");
    EXPECT_EQ(key->getKeyCode()->toString(), "04A");
    EXPECT_EQ(key->getKeyNotationFlat(), "Fm");
    EXPECT_EQ(key->getKeyNotationSharp(), "Fm");
    EXPECT_EQ(key->getRootValue(), 8.0);
    EXPECT_EQ(key->isMinor(), true);


}

TEST(boost_test, test_eq){
    EXPECT_EQ(boost::contains("am", "m"), true);
}