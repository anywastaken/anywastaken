#include "pch.h"
#include "jungtable.h"
#include "gtest/gtest.h"

// Ňĺńň íŕ äîáŕâëĺíčĺ ýëĺěĺíňîâ
TEST(jungtableTest, PushTest) {
    jungtable table;

    EXPECT_EQ(table.push(5), 0);  // Óńďĺříîĺ äîáŕâëĺíčĺ 5
    EXPECT_EQ(table.push(3), 0);  // Äîáŕâëĺíčĺ 3
    EXPECT_EQ(table.push(7), 0);  // Äîáŕâëĺíčĺ 7
    EXPECT_EQ(table.push(5), 404); // Ďîâňîđíîĺ äîáŕâëĺíčĺ 5 äîëćíî âĺđíóňü 404
}

// Ňĺńň íŕ óäŕëĺíčĺ
TEST(jungtableTest, DeleteTest) {
    jungtable table;
    table.push(10);
    table.push(5);
    table.push(15);
    table.push(7);
    table.push(3);

    EXPECT_EQ(table.del(1, 1), 404); // Íĺâĺđíűé číäĺęń
    EXPECT_EQ(table.del(1, 2), 404);
    EXPECT_EQ(table.del(2, 1), 404);
    EXPECT_EQ(table.del(2, 2), 0);
    std::vector<std::vector<int>> expected = { { 3, 15 }, { 5 }, { 10 } };
    EXPECT_EQ(table.body, expected);
    EXPECT_EQ(table.del(3, 1), 0); // Óäŕëĺíčĺ ďĺđâîăî ýëĺěĺíňŕ 
    expected = { { 5, 15 }, { 10 } };
    EXPECT_EQ(table.body, expected);
}

// Ňĺńň íŕ ńîđňčđîâęó ýëĺěĺíňîâ
TEST(jungtableTest, OrderTest) {
    jungtable table;
    table.push(10);
    table.push(5);
    table.push(15);
    table.push(7);
    table.push(3);

    std::vector<std::vector<int>> expected = { { 3, 7 }, { 5, 15 }, { 10 } };
    EXPECT_EQ(table.body, expected);
}

// Ďđîâĺđęŕ ďóńňîé ňŕáëčöű
TEST(jungtableTest, EmptyTest) {
    jungtable table;
    EXPECT_TRUE(table.body.empty());  // Äîëćíî áűňü ďóńňî â íŕ÷ŕëĺ
}

// Ňĺńň íŕ âűâîä (ďđîâĺđ˙ĺň, ÷ňî ďđîăđŕěěŕ íĺ ďŕäŕĺň)
TEST(jungtableTest, PrintTest) {
    jungtable table;
    table.push(8);
    table.push(2);
    table.print();
}

// Çŕďóńę âńĺő ňĺńňîâ
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
