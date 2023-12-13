#include "AVLTree.cc"
#include <gtest/gtest.h>
#include <iostream>

TEST(AVLTreeTest, TestIsEmpty) {
	AVLTree avltree;

	int isEmpty = avltree.empty();

	ASSERT_EQ(1, isEmpty);
}

class STLSetTestFixture : public testing::Test {
public:
	STLSetTestFixture();
	virtual ~STLSetTestFixture();
	void SetUp() override;
	void TearDown() override;
	static void SetUpTestCase();
	static void TearDownTestCase();
protected:
	AVLTree avltree_;
};

STLSetTestFixture::STLSetTestFixture() {
	std::cout << "Constructor called\n";
}

STLSetTestFixture::~STLSetTestFixture() {
	std::cout << "Destructor called\n";
}

void STLSetTestFixture::SetUpTestCase() {
	std::cout << "SetUpTestCase called\n";
}

void STLSetTestFixture::TearDownTestCase() {
	std::cout << "TearDownTestCase called\n";
}

void STLSetTestFixture::SetUp() {
	std::cout << "SetUp called\n";

	std::vector<int> input_key{ 1, 4, 9, 16, 25, 36, 49, 64, 81 };

	for (vector<int>::size_type i: input_key) {
		avltree_.insert(i);
	}
}

void STLSetTestFixture::TearDown(){
	std::cout <<"TearDown called\n";
}

TEST_F(STLSetTestFixture, TestSize) {
	std::cout << "Test : Size\n";

	ASSERT_EQ(9, avltree_.size());
}

TEST_F(STLSetTestFixture, TestMaximumAndRank) {
	std::cout << "Test : Maximum And Rank\n";

	int max = avltree_.maximum(avltree_.getRoot()->key);
	pair<int, int> result = avltree_.rankAndDepth(avltree_.getRoot(), max, 0, 0);
	int rank = result.first;

	ASSERT_EQ(81, max);
	EXPECT_EQ(9, rank);
}

TEST_F(STLSetTestFixture, TestMaxAfterErase) {
	std::cout << "Test : Maximum After Erase 10\n";
	avltree_.erase(81);

	int max = avltree_.maximum(avltree_.getRoot()->key);

	ASSERT_EQ(64, max);
}

TEST_F(STLSetTestFixture, TestMinimumAndRank) {
	std::cout << "Test : Minimum And Rank\n";

	int min = avltree_.minimum(avltree_.getRoot()->key);
	pair<int, int> result = avltree_.rankAndDepth(avltree_.getRoot(), min, 0, 0);
	int rank = result.first;

	ASSERT_EQ(1, min);
	EXPECT_EQ(1, rank);
}

TEST_F(STLSetTestFixture, TestMinAfterInsert) {
	std::cout << "Test : Minimum After Insert 0\n";
	avltree_.insert(0);

	int min = avltree_.minimum(avltree_.getRoot()->key);

	ASSERT_EQ(0, min);
}

TEST_F(STLSetTestFixture, TestEmpty) {
	std::cout << "Test : Empty\n";

	int isEmpty = avltree_.empty();

	ASSERT_EQ(0, isEmpty);
}

class STLSetTestFixtureWithParam : public testing::TestWithParam<int>{
	protected:
		AVLTree avltree_;
	
	void SetUp() override{
		std::vector<int> initialValue = {11, 33, 55, 22, 44};
		for (const auto& i: initialValue) {
			avltree_.insert(i);
		}
	}
};

INSTANTIATE_TEST_SUITE_P(
	AVLTreeTest, STLSetTestFixtureWithParam,
	testing::ValuesIn({11, 22, 33, 44, 55})
);

TEST_P(STLSetTestFixtureWithParam, TestFind){
	int key = GetParam();
	
	EXPECT_NE(avltree_.find(key), nullptr);
};

TEST_P(STLSetTestFixtureWithParam, TestErase){
	int key = GetParam();
	int initialSize = avltree_.size();
	avltree_.erase(key);
	std::cout << "The initialSize is " << initialSize << " and currentSize is " << avltree_.size() <<"\n";

	EXPECT_EQ(initialSize - 1, avltree_.size());
};

TEST(AVLTreeTest, TestInsertAndCheck){
	using namespace testing;
	AVLTree tree;
	tree.insert(10);
	tree.insert(5);
	tree.insert(15);

	EXPECT_EQ(10, tree.find(10)->key);
	ASSERT_EQ(5, tree.find(5)->key);
	ASSERT_EQ(3, tree.size());
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
