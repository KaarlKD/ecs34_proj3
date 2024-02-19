#include "gtest/gtest.h"
#include "StringDataSource.h"
#include "XMLReader.h"
#include "OpenStreetMap.h"
#include "StreetMap.h"

TEST(OpenStreetMap, BasicTest) {
    auto InputStream = std::make_shared<CStringDataSource>(
    "<?xml version='1.0' encoding='UTF-8'?>\n
    <osm version=\"0.6\" generator=\"osmconvert 0.8.5\">\n\t
    <node id=\"62208369\" lat=\"38.5178523\" lon=\"-121.7712408\"/>\n\t
    <node id=\"62209104\" lat=\"38.535052\" lon=\"-121.7408606\"/>"
    );
    CXMLReader Reader(InputStream);
    map = std::make_unique<OpenStreetMap>(Reader);
    









}