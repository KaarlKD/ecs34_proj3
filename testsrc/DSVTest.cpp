#include "gtest/gtest.h"
#include "StringDataSource.h"
#include "StringDataSink.h"
#include "DSVReader.h"
#include "DSVWriter.h"

#include<memory>
#include<vector>
#include<string>
#include<cstdio>

TEST(DSVReaderTest2, TestingRead2) {

    auto Source2 = std::make_shared< CStringDataSource >("\"abc\" hi,12,83");
    CDSVReader reader2(Source2, ',');
    std::vector<std::string> output2;
    EXPECT_TRUE(reader2.ReadRow(output2));
    
    EXPECT_EQ(output2[0], "abc hi");
    EXPECT_EQ(output2[1], "12");
    EXPECT_EQ(output2[2], "83");
    ASSERT_EQ(output2.size(), 3);
    EXPECT_TRUE(reader2.End());

}


TEST(DSVReaderTest, TestingEndandRead) {
    
    auto Source = std::make_shared< CStringDataSource >("A,B,C,D");
    CDSVReader reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(reader.ReadRow(output));
    EXPECT_TRUE(reader.End());
    //ASSERT_EQ(output.size(), 4);
    EXPECT_EQ(output[0], "A");
    EXPECT_EQ(output[1], "B");
    EXPECT_EQ(output[2], "C");
    EXPECT_EQ(output[3], "D");
}


TEST(DSVReaderTest3, TestingRead3) {
    auto Source3 = std::make_shared< CStringDataSource >("are,a,,\n,");
    CDSVReader reader3(Source3, ',');
    std::vector<std::string> output3;
    EXPECT_TRUE(reader3.ReadRow(output3));
    
    EXPECT_EQ(output3[0],"are");
    EXPECT_EQ(output3[1], "a");
    EXPECT_EQ(output3[2], "");
    EXPECT_EQ(output3[3], "");
    EXPECT_TRUE(reader3.End());
    ASSERT_EQ(output3.size(), 5);
}

TEST(DSVReaderTest4, TestingRead4) {
    auto Source4 = std::make_shared< CStringDataSource >("\"rabbit, \",monkey");
    CDSVReader reader4(Source4, ',');
    std::vector<std::string> output4;
    EXPECT_TRUE(reader4.ReadRow(output4));
    
    EXPECT_EQ(output4[0],"rabbit, ");
    EXPECT_EQ(output4[1], "monkey");
    EXPECT_TRUE(reader4.End());
    ASSERT_EQ(output4.size(), 2);
}

TEST(DSVReaderTest5, TestingRead5) {
    auto Source5 = std::make_shared< CStringDataSource >("rabbit,monkey");
    CDSVReader reader5(Source5, '"');
    std::vector<std::string> output5;
    EXPECT_TRUE(reader5.ReadRow(output5));
    
    EXPECT_EQ(output5[0],"rabbit");
    EXPECT_EQ(output5[1], "monkey");
    EXPECT_TRUE(reader5.End());
    ASSERT_EQ(output5.size(), 2);
}

TEST(DSVReaderTest6, TestingRead6) {
    auto Source6 = std::make_shared< CStringDataSource >("rabbit\"\n\",monkey");
    CDSVReader reader6(Source6, '"');
    std::vector<std::string> output6;
    EXPECT_TRUE(reader6.ReadRow(output6));
    
    EXPECT_EQ(output6[0],"rabbit\n");
    EXPECT_EQ(output6[1], "monkey");
    EXPECT_TRUE(reader6.End());
    ASSERT_EQ(output6.size(), 2);
}

TEST(DSVReaderTest7, TestingRead7) {
    auto Source7 = std::make_shared< CStringDataSource >("\"rabbit\n, monkey, elephant\"");
    CDSVReader reader7(Source7, '"');
    std::vector<std::string> output7;
    EXPECT_TRUE(reader7.ReadRow(output7));
    
    EXPECT_EQ(output7[0],"rabbit\n, monkey, elephant");
    EXPECT_TRUE(reader7.End());
    ASSERT_EQ(output7.size(), 1); 
}
TEST(DSVReaderTest8, TestingReadForClearing) {
    auto Source8 = std::make_shared< CStringDataSource >("tiger,eagle\nelephant,monkey");
    CDSVReader reader8(Source8, ',');
    std::vector<std::string> output8;
    EXPECT_TRUE(reader8.ReadRow(output8));

    EXPECT_EQ(output8[0], "tiger");
    EXPECT_EQ(output8[1], "eagle");

    EXPECT_TRUE(reader8.ReadRow(output8));
    EXPECT_EQ(output8[0], "elephant");
    EXPECT_EQ(output8[1], "monkey");
    
}



TEST(DSVWriterTest, TestingWrite) {
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,',');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello,World!");

    std::vector<std::string> input2 = {"Hi","again"};
    EXPECT_TRUE(Writer.WriteRow(input2));
    EXPECT_EQ(Sink->String(), "Hello,World!\nHi,again");

    std::vector<std::string> input3 = {"Third\ntime"};
    EXPECT_TRUE(Writer.WriteRow(input3));
    EXPECT_EQ(Sink->String(), "Hello,World!\nHi,again\n\"Third\ntime\"");
}

TEST(DSVWriterTest, TestingWritewithflag) {
    auto Sink1 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer1(Sink1,',', true);
    std::vector<std::string> input1 = {"Hello", "World!"};

    EXPECT_TRUE(Writer1.WriteRow(input1));
    EXPECT_EQ(Sink1->String(),"\"Hello\",\"World!\"");
}

TEST(DSVWriterTest, TestingWriteWithSpecialChar) {
    auto Sink1 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer1(Sink1,',');
    std::vector<std::string> input1 = {"Hello\nand", "World!"};

    EXPECT_TRUE(Writer1.WriteRow(input1));
    EXPECT_EQ(Sink1->String(),"\"Hello\nand\",World!");
}

TEST(DSVWriterTest, TestingLastwordSpecialChar) {
    auto Sink1 = std::make_shared<CStringDataSink>();
    CDSVWriter Writer1(Sink1,',');
    std::vector<std::string> input1 = {"Hello", "and\nWorld!"};

    EXPECT_TRUE(Writer1.WriteRow(input1));
    EXPECT_EQ(Sink1->String(),"Hello,\"and\nWorld!\"");
}


