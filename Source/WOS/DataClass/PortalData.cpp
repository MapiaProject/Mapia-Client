// Fill out your copyright notice in the Description page of Project Settings.


#include "DataClass/PortalData.h"

PortalData::PortalData()
{

}

PortalData::PortalData(FString LinkName, Vector2Int Position)
{
	this->LinkName = LinkName;
	this->Position = Position;
}

PortalData::~PortalData()
{
}
