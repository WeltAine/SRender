#include "../../Header/Tool/Tool.h"

std::wstring StringToWideString(const std::string& str, UINT codePage) {

    int wstringLength = MultiByteToWideChar(codePage, 0, str.c_str(), -1, NULL, 0);//ȷ����С�����Ǳ�Ҫ��ô��Ϊʲô������ת��ʱֱ�Ӹ�ֵ
    
    std::wstring wstr(wstringLength, 0);
    MultiByteToWideChar(codePage, 0, str.c_str(), -1, &wstr[0], str.size());//ת���ַ�����str.size()�����һ������string��˵����������������
    return wstr;

}