// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/Ini.h"

Ini::Ini(FStringView filename) : m_filename(filename)
{

}

Ini::Section Ini::operator[](FStringView section)
{
    return Section(m_filename, section);
}

Ini::Section::Section(FStringView filename, FStringView section) : m_filename(filename), m_section(section)
{
}