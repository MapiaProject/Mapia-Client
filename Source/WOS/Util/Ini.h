// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <windows.h>

class Ini
{
    class Section
    {
    public:
        Section(FStringView filename, FStringView section);
    public:
        template<class T>
        T Get(FString key)
        {
            T buffer;
            GetPrivateProfileStruct(*m_section, *key, &buffer, sizeof(buffer), *m_filename);
            return buffer;
        }
        template<>
        int Get<int>(FString key)
        {
            return GetPrivateProfileInt(*m_section, *key, 0, *m_filename);
        }
        template<>
        FString Get<FString>(FString key)
        {
            TCHAR buffer[1024] = L"";
            GetPrivateProfileString(*m_section, *key, L"", buffer, 1024, *m_filename);
            return buffer;
        }
    private:
        FString m_section;
        FString m_filename;
    };
public:
    Ini(FStringView filename);
public:
    Section operator[](FStringView section);
private:
    FString m_filename;
};