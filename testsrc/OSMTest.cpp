#include "gtest/gtest.h"
#include "StringDataSource.h"
#include "XMLReader.h"
#include "OpenStreetMap.h"
#include "StreetMap.h"


//ID for node
TEST(OpenStreetMapTests, NodeIDRetrieval) {
    OpenStreetMap::SNode node(12345, {11.2233, -44.5566});
    EXPECT_EQ(node.ID(), 12345);
}

//ID for way
TEST(OpenStreetMapTests, WayIDRetrieval) {
    OpenStreetMap::SWay way(67890);
    EXPECT_EQ(way.ID(), 67890);
}

//setattri and getattri for node
TEST(OpenStreetMapTests, SetAndGetAttributesNode) {
    OpenStreetMap::SNode node(1, {11.2233, -44.5566});
    node.SetAttribute("name", "testNode");
    node.SetAttribute("attri", "test");

    EXPECT_EQ(node.GetAttribute("name"), "testNode");
    EXPECT_EQ(node.GetAttribute("attri"), "test");
}

//setattri and getattri for way
TEST(OpenStreetMapTests, SetAndGetAttributesWay) {
    OpenStreetMap::SWay way(1, {11.2233, -44.5566});
    way.SetAttribute("name", "testNode");
    way.SetAttribute("attri", "test");

    EXPECT_EQ(way.GetAttribute("name"), "testNode");
    EXPECT_EQ(way.GetAttribute("attri"), "test");
}


//attributecount node
TEST(OpenStreetMapTests, AttributeCountNode) {
    OpenStreetMap::SNode node(1, {11.2233, -44.5566});
    node.SetAttribute("name", "testNode");
    node.SetAttribute("attri", "test");

    EXPECT_EQ(node.AttributeCount(), 2);
}

//attributecount way
TEST(OpenStreetMapTests, AttributeCountWay) {
    OpenStreetMap::SNode node(1, {11.2233, -44.5566});
    node.SetAttribute("name", "testNode");
    node.SetAttribute("attri", "test");

    EXPECT_EQ(node.AttributeCount(), 2);
}

//test for non exist
TEST(OpenStreetMapTests, NonExistentAttribute) {
    OpenStreetMap::SNode node(1, {11.2233, -44.5566});
    EXPECT_EQ(node.GetAttribute("nonexistent"), "");
}

TEST(OpenStreetMapTests, GetAttributeKeyOutOfBounds) {
    OpenStreetMap::SNode node(1, {11.2233, -44.5566});
    node.SetAttribute("name", "TestNode");
    EXPECT_EQ(node.GetAttributeKey(2), ""); //if out of boundary returen empty string
}



//node count
TEST(OpenStreetMapTests, NodeCountTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>\n"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n"
        "\t<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n"
        "\t<node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>\n"
        "\t<node id=\"395033730\" lat=\"38.5517247\" lon=\"-121.7352138\">\n"
        "\t\t<tag k=\"highway\" v=\"turning_circle\"/>\n"
        "\t</node>\n"
        "\t<way id=\"10747878\">\n"
        "\t\t<nd ref=\"95714626\"/>\n"
        "\t\t<nd ref=\"95722842\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Laurel Place\"/>\n"
        "\t</way>\n"
        "\t<way id=\"10747880\">\n"
        "\t\t<nd ref=\"95711208\"/>\n"
        "\t\t<nd ref=\"95709342\"/>\n"
        "\t\t<nd ref=\"274489608\"/>\n"
        "\t\t<nd ref=\"256045610\"/>\n"
        "\t\t<nd ref=\"274489609\"/>\n"
        "\t\t<nd ref=\"364126459\"/>\n"
        "\t\t<nd ref=\"95722271\"/>\n"
        "\t\t<nd ref=\"95722843\"/>\n"
        "\t\t<nd ref=\"282317446\"/>\n"
        "\t\t<nd ref=\"95719474\"/>\n"
        "\t\t<nd ref=\"95720329\"/>\n"
        "\t\t<nd ref=\"95719177\"/>\n"
        "\t\t<nd ref=\"95719330\"/>\n"
        "\t\t<nd ref=\"95721027\"/>\n"
        "\t\t<nd ref=\"95718759\"/>\n"
        "\t\t<tag k=\"cycleway\" v=\"lane\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Villanova Drive\"/>\n"
        "\t</way>\n"
        "</osm>"
    );
    CXMLReader Reader(InputStream);
    auto map = std::make_unique<OpenStreetMap>(Reader);
    EXPECT_EQ(map->NodeCount(), 3);
}


//way count
TEST(OpenStreetMapTests, WayCountTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>\n"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n"
        "\t<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n"
        "\t<node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>\n"
        "\t<node id=\"395033730\" lat=\"38.5517247\" lon=\"-121.7352138\">\n"
        "\t\t<tag k=\"highway\" v=\"turning_circle\"/>\n"
        "\t</node>\n"
        "\t<way id=\"10747878\">\n"
        "\t\t<nd ref=\"95714626\"/>\n"
        "\t\t<nd ref=\"95722842\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Laurel Place\"/>\n"
        "\t</way>\n"
        "\t<way id=\"10747880\">\n"
        "\t\t<nd ref=\"95711208\"/>\n"
        "\t\t<nd ref=\"95709342\"/>\n"
        "\t\t<nd ref=\"274489608\"/>\n"
        "\t\t<nd ref=\"256045610\"/>\n"
        "\t\t<nd ref=\"274489609\"/>\n"
        "\t\t<nd ref=\"364126459\"/>\n"
        "\t\t<nd ref=\"95722271\"/>\n"
        "\t\t<nd ref=\"95722843\"/>\n"
        "\t\t<nd ref=\"282317446\"/>\n"
        "\t\t<nd ref=\"95719474\"/>\n"
        "\t\t<nd ref=\"95720329\"/>\n"
        "\t\t<nd ref=\"95719177\"/>\n"
        "\t\t<nd ref=\"95719330\"/>\n"
        "\t\t<nd ref=\"95721027\"/>\n"
        "\t\t<nd ref=\"95718759\"/>\n"
        "\t\t<tag k=\"cycleway\" v=\"lane\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Villanova Drive\"/>\n"
        "\t</way>\n"
        "</osm>"
    );
    CXMLReader Reader(InputStream);
    auto map = std::make_unique<OpenStreetMap>(Reader);
    EXPECT_EQ(map->WayCount(), 2);
}


// node attribute
TEST(OpenStreetMapTests, NodeAttributeExistenceTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>\n"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n"
        "\t<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n"
        "\t<node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>\n"
        "\t<node id=\"395033730\" lat=\"38.5517247\" lon=\"-121.7352138\">\n"
        "\t\t<tag k=\"highway\" v=\"turning_circle\"/>\n"
        "\t</node>\n"
        "\t<way id=\"10747878\">\n"
        "\t\t<nd ref=\"95714626\"/>\n"
        "\t\t<nd ref=\"95722842\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Laurel Place\"/>\n"
        "\t</way>\n"
        "\t<way id=\"10747880\">\n"
        "\t\t<nd ref=\"95711208\"/>\n"
        "\t\t<nd ref=\"95709342\"/>\n"
        "\t\t<nd ref=\"274489608\"/>\n"
        "\t\t<nd ref=\"256045610\"/>\n"
        "\t\t<nd ref=\"274489609\"/>\n"
        "\t\t<nd ref=\"364126459\"/>\n"
        "\t\t<nd ref=\"95722271\"/>\n"
        "\t\t<nd ref=\"95722843\"/>\n"
        "\t\t<nd ref=\"282317446\"/>\n"
        "\t\t<nd ref=\"95719474\"/>\n"
        "\t\t<nd ref=\"95720329\"/>\n"
        "\t\t<nd ref=\"95719177\"/>\n"
        "\t\t<nd ref=\"95719330\"/>\n"
        "\t\t<nd ref=\"95721027\"/>\n"
        "\t\t<nd ref=\"95718759\"/>\n"
        "\t\t<tag k=\"cycleway\" v=\"lane\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Villanova Drive\"/>\n"
        "\t</way>\n"
        "</osm>"
    );
    CXMLReader Reader(InputStream);
    auto map = std::make_unique<OpenStreetMap>(Reader);
    auto node = map->NodeByID(395033730);
    EXPECT_TRUE(node != nullptr);
    EXPECT_TRUE(node->HasAttribute("highway"));
    EXPECT_EQ(node->GetAttribute("highway"), "turning_circle");
}

//wat attribute
TEST(OpenStreetMapTests, WayAttributeValuesTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>\n"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n"
        "\t<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n"
        "\t<node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>\n"
        "\t<node id=\"395033730\" lat=\"38.5517247\" lon=\"-121.7352138\">\n"
        "\t\t<tag k=\"highway\" v=\"turning_circle\"/>\n"
        "\t</node>\n"
        "\t<way id=\"10747878\">\n"
        "\t\t<nd ref=\"95714626\"/>\n"
        "\t\t<nd ref=\"95722842\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Laurel Place\"/>\n"
        "\t</way>\n"
        "\t<way id=\"10747880\">\n"
        "\t\t<nd ref=\"95711208\"/>\n"
        "\t\t<nd ref=\"95709342\"/>\n"
        "\t\t<nd ref=\"274489608\"/>\n"
        "\t\t<nd ref=\"256045610\"/>\n"
        "\t\t<nd ref=\"274489609\"/>\n"
        "\t\t<nd ref=\"364126459\"/>\n"
        "\t\t<nd ref=\"95722271\"/>\n"
        "\t\t<nd ref=\"95722843\"/>\n"
        "\t\t<nd ref=\"282317446\"/>\n"
        "\t\t<nd ref=\"95719474\"/>\n"
        "\t\t<nd ref=\"95720329\"/>\n"
        "\t\t<nd ref=\"95719177\"/>\n"
        "\t\t<nd ref=\"95719330\"/>\n"
        "\t\t<nd ref=\"95721027\"/>\n"
        "\t\t<nd ref=\"95718759\"/>\n"
        "\t\t<tag k=\"cycleway\" v=\"lane\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Villanova Drive\"/>\n"
        "\t</way>\n"
        "</osm>"
    );
    CXMLReader Reader(InputStream);
    auto map = std::make_unique<OpenStreetMap>(Reader);
    auto way = map->WayByID(10747880);
    EXPECT_TRUE(way != nullptr);
    EXPECT_EQ(way->GetAttribute("name"), "Villanova Drive");
    EXPECT_EQ(way->GetAttribute("cycleway"), "lane");
}

//none-exist node
TEST(OpenStreetMapTests, NonExistentNodeTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>\n"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n"
        "\t<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n"
        "\t<node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>\n"
        "\t<node id=\"395033730\" lat=\"38.5517247\" lon=\"-121.7352138\">\n"
        "\t\t<tag k=\"highway\" v=\"turning_circle\"/>\n"
        "\t</node>\n"
        "\t<way id=\"10747878\">\n"
        "\t\t<nd ref=\"95714626\"/>\n"
        "\t\t<nd ref=\"95722842\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Laurel Place\"/>\n"
        "\t</way>\n"
        "\t<way id=\"10747880\">\n"
        "\t\t<nd ref=\"95711208\"/>\n"
        "\t\t<nd ref=\"95709342\"/>\n"
        "\t\t<nd ref=\"274489608\"/>\n"
        "\t\t<nd ref=\"256045610\"/>\n"
        "\t\t<nd ref=\"274489609\"/>\n"
        "\t\t<nd ref=\"364126459\"/>\n"
        "\t\t<nd ref=\"95722271\"/>\n"
        "\t\t<nd ref=\"95722843\"/>\n"
        "\t\t<nd ref=\"282317446\"/>\n"
        "\t\t<nd ref=\"95719474\"/>\n"
        "\t\t<nd ref=\"95720329\"/>\n"
        "\t\t<nd ref=\"95719177\"/>\n"
        "\t\t<nd ref=\"95719330\"/>\n"
        "\t\t<nd ref=\"95721027\"/>\n"
        "\t\t<nd ref=\"95718759\"/>\n"
        "\t\t<tag k=\"cycleway\" v=\"lane\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Villanova Drive\"/>\n"
        "\t</way>\n"
        "</osm>"
    );
    CXMLReader Reader(InputStream);
    auto map = std::make_unique<OpenStreetMap>(Reader);
    auto node = map->NodeByID(99999999); //assuming id not exist
    EXPECT_EQ(node, nullptr);
}

// non exist way
TEST(OpenStreetMapTests, NonExistentWayTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>\n"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n"
        "\t<node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n"
        "\t<node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>\n"
        "\t<node id=\"395033730\" lat=\"38.5517247\" lon=\"-121.7352138\">\n"
        "\t\t<tag k=\"highway\" v=\"turning_circle\"/>\n"
        "\t</node>\n"
        "\t<way id=\"10747878\">\n"
        "\t\t<nd ref=\"95714626\"/>\n"
        "\t\t<nd ref=\"95722842\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Laurel Place\"/>\n"
        "\t</way>\n"
        "\t<way id=\"10747880\">\n"
        "\t\t<nd ref=\"95711208\"/>\n"
        "\t\t<nd ref=\"95709342\"/>\n"
        "\t\t<nd ref=\"274489608\"/>\n"
        "\t\t<nd ref=\"256045610\"/>\n"
        "\t\t<nd ref=\"274489609\"/>\n"
        "\t\t<nd ref=\"364126459\"/>\n"
        "\t\t<nd ref=\"95722271\"/>\n"
        "\t\t<nd ref=\"95722843\"/>\n"
        "\t\t<nd ref=\"282317446\"/>\n"
        "\t\t<nd ref=\"95719474\"/>\n"
        "\t\t<nd ref=\"95720329\"/>\n"
        "\t\t<nd ref=\"95719177\"/>\n"
        "\t\t<nd ref=\"95719330\"/>\n"
        "\t\t<nd ref=\"95721027\"/>\n"
        "\t\t<nd ref=\"95718759\"/>\n"
        "\t\t<tag k=\"cycleway\" v=\"lane\"/>\n"
        "\t\t<tag k=\"highway\" v=\"residential\"/>\n"
        "\t\t<tag k=\"name\" v=\"Villanova Drive\"/>\n"
        "\t</way>\n"
        "</osm>"
    );
    CXMLReader Reader(InputStream);
    auto map = std::make_unique<OpenStreetMap>(Reader);
    auto way = map->WayByID(99999999); //assuming id not exist
    EXPECT_EQ(way, nullptr);
}