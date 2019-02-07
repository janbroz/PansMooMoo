// Fill out your copyright notice in the Description page of Project Settings.

#include "MooPlayerState.h"

AMooPlayerState::AMooPlayerState()
{
	bAlwaysRelevant = true;
	Gold = 10;

	
}

bool AMooPlayerState::BuyItem(int32 Price)
{
	if (Gold >= Price)
	{
		Gold -= Price;
		return true;
	}
	else
	{
		return false;
	}
}