#include "XMLWriter.h"
#include "StringDataSink.h"
#include "gtest/gtest.h"
#include "StringDataSource.h"
#include "XMLReader.h"

TEST(XMLWriter1, BasicTest) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}}));

    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");
}

TEST(XMLWriter2, CharDataTest) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "person", {{"id", "123"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "John Doe"}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "person", {}}));

    EXPECT_EQ(OutputStream->String(),"<person id=\"123\">John Doe</person>");
}

TEST(XMLWriter3, EscCharTest) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "spread", {{"id", "123"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Peanut & Butter"}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Peanut \"Butter\""}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "spread", {}}));

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "book", {{"isbn", "123456"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "title", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Percy Jackson & the Lightning Thief"}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "title", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "author", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Rick 'Riordan'"}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "author", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "book", {}}));

    EXPECT_EQ(OutputStream->String(), "<spread id=\"123\">Peanut &amp; ButterPeanut &quot;Butter&quot;</spread><book isbn=\"123456\"><title>Percy Jackson &amp; the Lightning Thief</title><author>Rick &apos;Riordan&apos;</author></book>");
}
TEST(XMLWriter4, CompleteType) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CompleteElement, "selfClosingElement", {{"attribute", "value"}}}));
    EXPECT_EQ(OutputStream->String(), "<selfClosingElement attribute=\"value\"/>");
}

TEST(XMLWriter2, FlushTest) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"><example/>");
}
TEST(XMLWriter, FlushTest2) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Peanut & Butter"}));
    Writer.Flush();
    EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\">Peanut &amp; Butter<example/>");
}
//"<example attr=\"Hello World\"><example>"
//"<example attr=\"Hello World\"></example>"


TEST(XMLReaderTest, BasicTest){

    auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);

}

TEST(XMLReaderTest, NestedElementsTest) {
    auto InputStream = std::make_shared<CStringDataSource>("<aaa><bbb attr=\"111\">Hello World!</bbb></aaa>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    
    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "aaa");

    
    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "bbb");
    EXPECT_EQ(E.AttributeValue("attr"), "111");

    
    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(E.DNameData, "Hello World!");

    
    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(E.DNameData, "bbb");

    
    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
    EXPECT_EQ(E.DNameData, "aaa");
}

TEST(XMLReaderTest, MultipleAttributesTest) {
    auto InputStream = std::make_shared<CStringDataSource>("<aaa attr1=\"111\" attr2=\"222\"></aaa>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "aaa");
    EXPECT_EQ(E.AttributeValue("attr1"), "111");
    EXPECT_EQ(E.AttributeValue("attr2"), "222");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLReaderTest, SkipCharacterDataTest) {
    auto InputStream = std::make_shared<CStringDataSource>("<aaa>Hello !<bbb/>World !</aaa>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    
    EXPECT_TRUE(Reader.ReadEntity(E, true));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "aaa");

    
    EXPECT_TRUE(Reader.ReadEntity(E, true));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.DNameData, "bbb");

    
    EXPECT_TRUE(Reader.ReadEntity(E, true));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);

    
    EXPECT_TRUE(Reader.ReadEntity(E, true));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}