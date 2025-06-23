#include <gtest/gtest.h>

#include "../CustomForwardList.hpp"
#include "../CustomList.hpp"
#include "../CustomVector.hpp"


template <typename ContainerType>
class CustomContainerTest : public ::testing::Test {
protected:
    ContainerType container;
    void SetUp() override {
        container.push_back(10);
        container.push_back(20);
        container.push_back(30);
    }
};

using ContainerTypes = ::testing::Types<CustomList<int>, CustomVector<int>, CustomForwardList<int>>;

TYPED_TEST_SUITE(CustomContainerTest, ContainerTypes);

TYPED_TEST(CustomContainerTest, InitializeContainer) {
    ASSERT_GT(this->container.size(), 0);
}

TYPED_TEST(CustomContainerTest, PushBack) {
    ASSERT_EQ(this->container.size(), 3);
    ASSERT_EQ(this->container[2], 30);
}

TYPED_TEST(CustomContainerTest, InsertInFront) {
    this->container.insert(5, 0);
    ASSERT_EQ(this->container.size(), 4);
    ASSERT_EQ(this->container[0], 5);
}

TYPED_TEST(CustomContainerTest, InsertInMiddle) {
    this->container.insert(5, 1);
    ASSERT_EQ(this->container.size(), 4);
    ASSERT_EQ(this->container[1], 5);
}

TYPED_TEST(CustomContainerTest, RemoveFromBack) {
    this->container.erase(2);
    ASSERT_EQ(this->container.size(), 2);
    ASSERT_EQ(this->container[1], 20);
}

TYPED_TEST(CustomContainerTest, RemoveFromBegin) {
    this->container.erase(0);
    ASSERT_EQ(this->container.size(), 2);
    ASSERT_EQ(this->container[0], 20);
}

TYPED_TEST(CustomContainerTest, RemoveFromMiddle) {
    this->container.erase(1);
    ASSERT_EQ(this->container.size(), 2);
    ASSERT_EQ(this->container[1], 30);
}

TYPED_TEST(CustomContainerTest, CopyContainer) {
    TypeParam newContainer{this->container};
    ASSERT_EQ(newContainer.size(), this->container.size());
    for (size_t i = 0; i < this->container.size(); ++i) {
        ASSERT_EQ(this->container[i], newContainer[i]);
    }
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}