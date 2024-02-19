#include "StringUtils.h"
namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    ssize_t length = str.length();
    std::string currentString;
    std::string reversedString;

    if (start > length || (end >0 && end < start)){ 
        return ""; 
    }
    
    if (start < 0){
        start += length;
        currentString = str.substr((start-end+1), start);
        for (int i=currentString.length()-1; i>=0; i--){ 
            reversedString += currentString[i];
        }
        return reversedString;
    }

    if (end <= 0){
        end += length;
        if (start > end){
            currentString = str.substr(end, start);
            for (int i=currentString.length()-1; i>=0; i--){  
                reversedString += currentString[i];
            }
            return reversedString;
        }

    }

    return str.substr(start, end);
}

std::string Capitalize(const std::string &str) noexcept{
    std::string outString;

    for (int i= 0; i<str.length(); i++){
        if (i==0){
            outString += std::toupper(str[i]);
        }
        else{
            outString += std::tolower(str[i]);
        }
    }

    return outString;
}

std::string Upper(const std::string &str) noexcept{
    std::string outString;
    for (int i= 0; i<str.length(); i++){
        outString += std::toupper(str[i]);
    }
    return outString;
}

std::string Lower(const std::string &str) noexcept{
    std::string outString;
    for (int i= 0; i<str.length(); i++){
        outString += std::tolower(str[i]);
    }
    return outString;
}

std::string LStrip(const std::string &str) noexcept{
    size_t notSpaceStart = str.find_first_not_of(" \t");
    
    return StringUtils::Slice(str, notSpaceStart, 0);
}

std::string RStrip(const std::string &str) noexcept{
    size_t notSpaceEnd = str.find_last_not_of(" \t");
    return StringUtils::Slice(str, 0, notSpaceEnd+1);
}

std::string Strip(const std::string &str) noexcept{
    size_t notSpaceStart = str.find_first_not_of(" \t");
    size_t notSpaceEnd = str.find_last_not_of(" \t");
    return StringUtils::Slice(str, notSpaceStart, (notSpaceEnd - notSpaceStart) + 1);
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    ssize_t length = str.length();
    if (width <= length){
        return str;
    }

    int leftSpace = (width-length)/2;
    int rightSpace = width-(length+leftSpace);

    std::string outString = std::string(leftSpace, fill)+str+std::string(rightSpace, fill);



    return outString;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    ssize_t length = str.length();
    if (width <= length){
        return str;
    }

    int rightSpace = (width-length);

    std::string outString = str+std::string(rightSpace, fill);

    return outString;

}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    ssize_t length = str.length();
    if (width <= length){
        return str;
    }
    int leftSpace = (width-length);

    std::string outString = std::string(leftSpace, fill)+str;

    return outString;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    std::string outString;
    for (int i=0; i<str.length(); i++){
        if (i <= str.length()-old.length() && str.substr(i, old.length())==old){
            outString +=rep;
            i += old.length()-1;
        }else{
        outString += str[i];
    }

    }
    return outString;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> outString;
    std::string restString = str+splt;

    int position = str.find(splt);


    while (position != std::string::npos){
        std::string tempString = restString.substr(0,position);
        outString.push_back(tempString);
        restString = restString.substr(position+1);
        position=restString.find(splt);

    }

    return outString;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string outString;
    int position=0;


    for (int i = 0; i < vect.size(); i++){
        outString.append(vect[i]);
        if (i<vect.size()-1){
            outString.append(str);
        }
    }


    return outString;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string outString;
    for (int i=0; i<str.length(); i++){
        if (str[i] == '\t'){
            for (int j=0; j<tabsize; j++){
                outString += " ";
            }
        }else{
            outString += str[i];
        }
    }
    return outString;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    int distance = abs(left.length()-right.length());
    return distance;
}

};