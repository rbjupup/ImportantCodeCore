//自己对map的一个简单实现
#pragma once
#include "atltypes.h"
#include "XFunCom.h"
#include <vector>
using namespace std;

struct AttributeMap 
{
	enum Mapstatus
	{
		exist,
		noexist
	};
	vector<CString> AttributeValue;
	vector<CString> AttributeKey;
	AttributeMap()
	{
		AttributeValue.clear();
		AttributeKey.clear();
	}
	CString GetAttributeValue(CString &Key)
	{
		CString Zero = "";
		if (AttributeKey.size() == 0) return Zero;
		for (int i = 0;i<AttributeKey.size();i++)
		{
			if(strcmp(AttributeKey[i],Key) == 0) return AttributeValue[i];

		}
		return Zero;
	}
	Mapstatus SetAttributeValue(CString &Key,CString &Value)
	{
		CString Zero = "";
		for (int i = 0;i<AttributeKey.size();i++)
		{
			if(strcmp(AttributeKey[i],Key) == 0) {
				AttributeValue[i] = Value;
				return exist;
			}
		}
		AttributeKey.push_back(Key);
		AttributeValue.push_back(Value);
		return noexist;
	}
};
