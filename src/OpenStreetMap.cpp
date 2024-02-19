#include"OpenStreetMap.h"
#include "XMLReader.h"


struct COpenStreetMap::SImplementation {

    struct SNode : public CStreetMap::SNode {
        TNodeID DID;
        TLocation DLocation;
        std::unordered_map<std::string, std::string> DAttributes;
        std::vector<std::string> DAttributeKeys;
        SNode(TNodeID id, TLocation location) {
            DID = id;
            DLocation = location;
        }

        ~SNode(){
        }

        TNodeID ID() const noexcept override {
            return DID;
        }

        TLocation Location() const noexcept override {
            return DLocation;
        }

        std::size_t AttributeCount() const noexcept override {
            return DAttributeKeys.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if(index < DAttributeKeys.size()) {
                return DAttributeKeys[index];
            }
            return std::string();
        }

        bool HasAttribute(const std::string &key) const noexcept override {
            auto Search = DAttributes.find(key);
            return DAttributes.end() != Search;
        }

        std::string GetAttribute(const std::string &key) const noexcept override {
            auto Search = DAttributes.find(key);
            if(DAttributes.end() != Search) {
                return Search->second;
            }
            return std::string();
        }
        void SetAttribute(const std::string &key, const std::string &value) {
            DAttributeKeys.push_back(key);
            DAttributes[key] = value;
        }
    };

    struct SWay : public CStreetMap::SWay {
        TWayID TID;
        std::unordered_map<std::string, std::string> WayAttributes;
        std::vector<std::string> WayAttributeKeys;
        SWay(TWayID id) {
            TID = id;
        }

        ~SWay(){
        }

        TWayID ID() const noexcept override {
            return TID;
        }

        std::size_t NodeCount() const noexcept override {
            return NodeRefVector.size();
        }
        TNodeID GetNodeID(std::size_t index) const noexcept override {
            if(NodeRefVector.size() < index) {
                return NodeRefVector[index];
            }
            return TNodeID;
        }
        std::size_t AttributeCount() const noexcept override {
            return WayAttributes.size();
        }
        std::string GetAttributeKey(std::size_t index) const noexcept override {
            if(WayAttributeKeys.size() < index) {
                return WayAttributeKeys[index];
            }
            return std::string();
        }
        bool HasAttribute(const std::string &key) const noexcept override {
            auto Search = WayAttributes.find(key);
            if(WayAttributes.end() != Search) {
                return Search->second;
            }
            return std::string();
        }
        std::string GetAttribute(const std::string &key) const noexcept override {
            auto Search = WayAttributes.find(key);
            if(WayAttributes.end() != Search) {
                return Search->second;
            }
            return std::string();
        }
        void SetAttribute(const std::string &key, const std::string &value) {
            WayAttributeKeys.push_back(key);
            WayAttributes[key] = value;
        }
    };

    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode> > DNodeIdToNode;
    std::vector < std::shared_ptr<CStreetMap::SNode> >DNodesByIndex;

    std::unordered_map<TWayID, std::shared_ptr<CStreetMap::SWay> > WayIDToNode;
    std::vector < std::shared_ptr<CStreetMap::SWay> >WaysByIndex;
    std::vector<TNodeID> NodeRefVector;

    SImplementation(std::shared_ptr<CXMLReader> src) {
        SXMLEntity TempEntity;
        while(src->ReadEntity(TempEntity, true)) {
            if((TempEntity.DNameData == "osm") && (SXMLEntity::Etype::EndElement == TempEntity.DType)) {
                break; //reached end 
            }
            else if ((TempEntity.DNameData == "node") && (SXMLEntity::Etype::StartElement == TempEntity.DType)) {
                //parse node
                TNodeID NewNodeID = std::stoull(TempEntity.AttributeValue("id"));
                double Lat = std::stod(TempEntity.AttributeValue("lat"));
                double Lon = std::stod(TempEntity.AttributeValue("lon"));
                TLocation NewNodeLocation = std::make_pair(Lat, Lon);
                auto NewNode = std::make_shared<SNode>(NewNodeID, NewNodeLocation);
                DNodesByIndex.push_back(NewNode);
                DNodeIdToNode[NewNodeID] = NewNode;
                //handle tag elements
                while(src->ReadEntity(TempEntity, true)) {
                    if((TempEntity.DNameData == "node") && (SXMLEntity::EType::EndElement == TempEntity.DType)) {
                        break;
                    }
                    else if((TempEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TempEntity.DType)) {
                        NewNode->SetAttribute(TempEntity.AttributeValue("k"), TempEntity.AttributeValue("v"));
                    }
                }
            }
            else if ((TempEntity.DNameData == "way") && (SXMLEntity::Etype::StartElement == TempEntity.DType)) {
                //parse way
                TWayID NewWayID = std::stoull(TempEntity.AttributeValue("id"));
                //store the node refs and store the attributes
                auto NewWay = std::make_shared<SWay>(NewWayID);
                WaysByIndex.push_back(NewWay);
                WayIDToNode[NewWayID] = NewWay;
                while(src->ReadEntity(TempEntity, true)) {
                    if((TempEntity.DNameData == "way") && (SXMLEntity::EType::EndElement == TempEntity.DType)) {
                        break;
                    }
                    else if((TempEntity.DNameData == "tag") && (SXMLEntity::Etype::StartElement == TempEntity.DType)) {
                        NewWay->SetAttribute(TempEntity.AttributeValue("k"), TempEntity.AttributeValue("v"));
                    }
                    else if((TempEntity.DNameData == "nd") && (SXMLEntity::Etype::StartElement == TempEntity.Dtype)) {
                        NodeRefVector.push_back(TempEntity.AttributeValue("ref"));
                    }

                }

            }
        }
    }

    std::size_t NodeCount() const{
        return DNodesByIndex.size();
    }
    std::size_t WayCount() const{
        return NodeRefVector.size();
    }
    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const{
        if(index < DNodesByIndex.size()) {
            return DNodesByIndex[index];
        }
        return nullptr;

    }
    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const {
        auto Search = DNodeIdToNode.find(id);
        if(DNodeIdToNode.end() != Search) {
            return Search->second;
        }
        return nullptr;
    }
    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const {
        if(index < WayByIndex.size()) {
            return WayByIndex[index];
        }
        return nullptr;

    }
    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const {
        auto Search = WayByID.find(id);
        if(Search != WayByID.end()) {
            return Search->second;
        }
        return nullptr;
    }
}

COpenStreetMap::COpenStreetMap(std::shared_ptr<CXMLReader> src) {
    DImplementation = std::make_unique<SImplementation>(src);
}
COpenStreetMap::~COpenStreetMap() {

}

std::size_t COpenStreetMap::NodeCount() const {
    return DImplementation->NodeCount();
}
std::size_t COpenStreetMap::WayCount() const {
    return DImplementation->WayCount();
}
std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByIndex(std::size_t index) const {
    return DImplementation->NodeByIndex(index);
}
std::shared_ptr<CStreetMap::SNode> COpenStreetMap::NodeByID(TNodeID id) const {
    return DImplementation->NodeByID(id);
}
std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByIndex(std::size_t index) const {
    return DImplementation->WayByIndex(index);
}
std::shared_ptr<CStreetMap::SWay> COpenStreetMap::WayByID(TWayID id) const {
    return DImplementation->WayByID(id);
}