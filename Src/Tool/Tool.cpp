#include "../../Header/Tool/Tool.h"

std::wstring StringToWideString(const std::string& str, UINT codePage) {

    int wstringLength = MultiByteToWideChar(codePage, 0, str.c_str(), -1, NULL, 0);//确定大小？这是必要的么，为什么不能在转换时直接赋值
    
    std::wstring wstr(wstringLength, 0);
    MultiByteToWideChar(codePage, 0, str.c_str(), -1, &wstr[0], str.size());//转换字符串，str.size()无需加一，对于string来说，它们是面向对象的
    return wstr;

}