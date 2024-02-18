#include "DSVReader.h"
#include "DataSource.h"
#include<iostream>

struct CDSVReader::SImplementation{
    std::shared_ptr<CDataSource>src;
    char delimiter;
    char ch;
    SImplementation(std::shared_ptr< CDataSource > src, char delimiter) : src(src), delimiter(delimiter)
    {
    }
    ~SImplementation() {
    }
    bool ReadRow(std::vector<std::string> &row) {
    row.clear();
    std::vector<char> buffer;
    bool quoteflag = false;
    if(delimiter == '\"') {
        delimiter = ',';
    }
    while(src->Get(ch)) {
        if(quoteflag == false) {
            if(ch == '\"') {
                quoteflag = true;
            }
            else if (ch == '\n' || ch == delimiter || ch == EOF) {
                if(buffer.empty()){
                    row.push_back("");
                }
                else{
                    std::string column(buffer.begin(), buffer.end());
                    row.push_back(column);
                    if(ch == '\n') {
                        ch = buffer.back();
                        buffer.clear();
                        return true;
                    }
                    buffer.clear();
                }
            }
            else{
                buffer.push_back(ch);
            }
        }
        else{
            if(ch == '\"') {
                if(src->Peek(ch) && ch == '\"'){                
                    buffer.push_back('\"');
                }    
                else{
                    quoteflag = false;
                }
                
            }
            else if(ch == EOF) {
                if(buffer.empty()){
                    row.push_back("");
                }
                else{
                std::string column(buffer.begin(), buffer.end());
                row.push_back(column);
                //std::cout<<column<<std::endl;
                buffer.clear();
                }
            }
            else {
                buffer.push_back(ch);
            }
        }
    }
    if(!buffer.empty()) {
            std::string column(buffer.begin(), buffer.end());
            row.push_back(column);
            //std::cout<<column<<std::endl;
            buffer.clear();     
    }
        return !row.empty();
    }

    bool End() {
        char ch;
        while (src->Peek(ch)) {
        src->Get(ch);
    }
    return true;
    }


};




// Constructor implementation
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delimiter) {
    DImplementation = std::make_unique<SImplementation>(src, delimiter);
    
}


// Destructor implementation
CDSVReader::~CDSVReader(){

}


// End method implementation
bool CDSVReader::End() const {
    return DImplementation->End();
}

// ReadRow method implementation
bool CDSVReader::ReadRow(std::vector<std::string> &row) {
    return DImplementation->ReadRow(row);
}