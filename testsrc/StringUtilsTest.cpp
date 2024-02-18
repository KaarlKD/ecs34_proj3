#include <gtest/gtest.h>
#include "StringUtils.h"
TEST(StringUtilsTest, SliceTest){
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",0,3),"asd");
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",0,0),"asdfghjkl");
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",-1,3),"lkj");
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",8,-3),"lkj");
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",6,8),"jkl");
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",100,109),"");
    EXPECT_EQ(StringUtils::Slice("asdfghjkl",7,4),"");
}

TEST(StringUtilsTest, Capitalize){
    EXPECT_EQ(StringUtils::Capitalize("asdfghjkl"),"Asdfghjkl");
    EXPECT_EQ(StringUtils::Capitalize("asdfGhjkl"),"Asdfghjkl");
    EXPECT_EQ(StringUtils::Capitalize("AsdfGHJkl"),"Asdfghjkl");
    EXPECT_EQ(StringUtils::Capitalize("AsdfG HJkl,"),"Asdfg hjkl,");

    
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper("asdfghjkl"),"ASDFGHJKL");
    EXPECT_EQ(StringUtils::Upper("AsdfgHjkl"),"ASDFGHJKL");
    EXPECT_EQ(StringUtils::Upper("asdfgh  jkl,*"),"ASDFGH  JKL,*");

}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower("ASDFGHJKL"),"asdfghjkl");
    EXPECT_EQ(StringUtils::Lower("aSdfGHjKL"),"asdfghjkl");
    EXPECT_EQ(StringUtils::Lower("ASDFGH  JK@#$L"),"asdfgh  jk@#$l");
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip("hello   "),"hello   ");
    EXPECT_EQ(StringUtils::LStrip("   hello"),"hello");
    EXPECT_EQ(StringUtils::LStrip("\thello"),"hello");
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip("   hello   "),"   hello");
    EXPECT_EQ(StringUtils::RStrip("hello   "),"hello");
    EXPECT_EQ(StringUtils::RStrip("hello\t"),"hello");
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip("   hello   "),"hello");
    EXPECT_EQ(StringUtils::Strip("   hello"),"hello");
    EXPECT_EQ(StringUtils::Strip("hello   "),"hello");
    EXPECT_EQ(StringUtils::Strip("\thello\t"),"hello");
    EXPECT_EQ(StringUtils::Strip("hello\t"),"hello");
    EXPECT_EQ(StringUtils::Strip("\thello"),"hello");

}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("hello",5, ' '),"hello");
    EXPECT_EQ(StringUtils::Center("hello",9, ' '),"  hello  ");
    EXPECT_EQ(StringUtils::Center("hello",9, '$'),"$$hello$$");
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("hello",5, ' '),"hello");
    EXPECT_EQ(StringUtils::LJust("hello",9, ' '),"hello    ");
    EXPECT_EQ(StringUtils::LJust("hello",9, '$'),"hello$$$$");
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("hello",5, ' '),"hello");
    EXPECT_EQ(StringUtils::RJust("hello",9, ' '),"    hello");
    EXPECT_EQ(StringUtils::RJust("hello",9, '$'),"$$$$hello");
    
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("hello world, hi", "world", "abcde"),"hello abcde, hi");
}

TEST(StringUtilsTest, Split){
    std::string testString = "Hello World Hi";
    std::string splitsign = " ";

    std::vector<std::string> ans = {"Hello", "World", "Hi"};
    std::vector<std::string> result = StringUtils::Split(testString, splitsign);

    ASSERT_EQ(result.size(), ans.size());
    for (size_t i=0; i<ans.size(); i++) {
        EXPECT_EQ(result[i], ans[i]);
    }

}

TEST(StringUtilsTest, Join){
    EXPECT_EQ(StringUtils::Join(" ",{"Hello", "World", "Hi!"}),"Hello World Hi!");
    EXPECT_EQ(StringUtils::Join("",{"Hello", "World", "Hi!"}),"HelloWorldHi!");
    EXPECT_EQ(StringUtils::Join("&",{"Hello", "World", "Hi!"}),"Hello&World&Hi!");
    
}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(StringUtils::ExpandTabs("Hello\tWorld\tHi", 6), "Hello      World      Hi");
    
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(StringUtils::EditDistance("human","humans", false), 1);
    
}
