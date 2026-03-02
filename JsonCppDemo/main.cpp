#include <iostream>
#include <json/json.h>
using namespace std;

int main(int argc, char const *argv[])
{
    Json::Value root;
    root["name"] = "JsonCppDemo";
    root["version"] = "1.0.0";
    root["description"] = "A demo for using JsonCpp library in C++ project.";
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  "; // 设置缩进为两个空格
    string jsonString = Json::writeString(builder, root);
    cout << jsonString << endl;
    return 0;
}
