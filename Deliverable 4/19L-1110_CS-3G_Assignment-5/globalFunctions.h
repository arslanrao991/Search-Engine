//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

//String copy function
void StrCopy(char* destinatio, char* source)
{
	int size=strlen(source)+1;
	for (int i=0;i<size;i++)
		destinatio[i]=source[i];
}

//It will create the dynamic char* of source and return their address 
char* GetString(char* source)		//use for helping Purpose
{
	if (source == NULL)
		return NULL;
	int size=strlen(source);
	char* destination = new char[size + 1];
	for (int i = 0;i < (size + 1);i++)
		destination[i] = source[i];
	return destination;
}

//Convert all letters of string into smaller one; e.g:- Drug -> drug
void ConvertStrIntoSmallLetter(char* str)
{
	int size=strlen(str);
	for (int i=0;i<size;i++)
	{
		if (str[i]>=65 && str[i]<=90)
			str[i]=str[i]+32;
	}
}

//Compare two strings by their ASCII value and return the Smaller one
char* GetSmallerStr(char* str1, char* str2)
{
	char name1[25];
	char name2[25];
	int size;
	StrCopy(name1,str1);
	StrCopy(name2,str2);
	ConvertStrIntoSmallLetter(name1);
	ConvertStrIntoSmallLetter(name2);
	if (strlen(str1)<strlen(str2))
		size=strlen(str1);
	else if (strlen(str1)>=strlen(str2))
		size=strlen(str2);
	for (int i=0;i<size;i++)
	{
		if (name1[i]<name2[i])
			return str1;
	}
	if (strlen(str1)<strlen(str2))
		return str1;
	return str2;
}