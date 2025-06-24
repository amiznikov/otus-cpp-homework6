#include <gtest/gtest.h>

#include "../CustomForwardList.hpp"
#include "../CustomList.hpp"
#include "../CustomVector.hpp"

class CustomInt {
private:
    int value_;
    bool* isDestroyed_;
public:
    CustomInt() : value_(0) {}
    CustomInt(int value) : value_(value) {}

    CustomInt(int value, bool* destroyed) : value_(value), isDestroyed_(destroyed) {}

    CustomInt(const CustomInt& other) : value_(other.value_), isDestroyed_(other.isDestroyed_) {}

    ~CustomInt() {
        value_ = 0;
        if (isDestroyed_) {
            *isDestroyed_ = true;
        }
        isDestroyed_ = nullptr;
    }

    operator int() const {
        return value_;
    }

    bool operator==(const CustomInt& other) const {
        return value_ == other.value_;
    }

    bool operator==(const int& other) const {
        return value_ == other;
    }

    bool operator!=(const CustomInt& other) const {
        return value_ != other.value_;
    }

    bool operator<(const CustomInt& other) const {
        return value_ < other.value_;
    }

    bool operator>(const CustomInt& other) const {
        return value_ > other.value_;
    }

    bool operator<=(const CustomInt& other) const {
        return value_ <= other.value_;
    }

    bool operator>=(const CustomInt& other) const {
        return value_ >= other.value_;
    }
};

template <typename ContainerType>
class CustomContainerTest : public ::testing::Test {
public:
    ContainerType container;

    CustomInt ten{10};
    CustomInt twenty{20};
    CustomInt thirty{30};
    void SetUp() override {
        container.push_back(ten);
        container.push_back(twenty);
        container.push_back(thirty);
    }
    void TearDown() override {
        container.clear();
    }
};

using ContainerTypes = ::testing::Types<CustomList<CustomInt>, CustomVector<CustomInt>, CustomForwardList<CustomInt>>;

TYPED_TEST_SUITE(CustomContainerTest, ContainerTypes);

TYPED_TEST(CustomContainerTest, InitializeContainer) {
    ASSERT_GT(this->container.size(), 0);
}

TYPED_TEST(CustomContainerTest, PushBack) {
    ASSERT_EQ(this->container.size(), 3);
    ASSERT_EQ(this->container[2], 30);
}

TYPED_TEST(CustomContainerTest, InsertInFront) {
    this->container.insert(CustomInt{5}, 0);
    ASSERT_EQ(this->container.size(), 4);
    ASSERT_EQ(this->container[0], 5);
}

TYPED_TEST(CustomContainerTest, InsertInMiddle) {
    this->container.insert(CustomInt{5}, 1);
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

// TYPED_TEST(CustomContainerTest, DestructorCall) {
//     bool isDestroyed2 = false;
//     bool isDestroyed4 = false;
//     {
//         CustomInt two{2, &isDestroyed2};
//         CustomInt four{4, &isDestroyed4};
//         TypeParam new_container{2.0};
//         std::cout << "CustomInt will add 1 element" << std::endl;
//         new_container.push_back(two);
//         std::cout << "CustomInt will add 2 element" << std::endl;
//         new_container.push_back(four);
//         std::cout << "CustomInt destructor should be call" << std::endl;
//         ASSERT_FALSE(isDestroyed2);
//         ASSERT_FALSE(isDestroyed4);
//     }
//     ASSERT_TRUE(isDestroyed2);
//     ASSERT_TRUE(isDestroyed4);
// }

TYPED_TEST(CustomContainerTest, MoveContainer) {
    size_t size = this->container.size();
    TypeParam newContainer{std::move(this->container)};
    ASSERT_EQ(size, newContainer.size());
    ASSERT_EQ(this->container.size(), 0);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}