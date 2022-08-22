// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AppLovinSettings.generated.h"

class UAppLovinAdsWidgetTest;

UCLASS(config = Engine, defaultconfig)
class UAppLovinSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = "Widgets")
	TSubclassOf<UAppLovinAdsWidgetTest> TestWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category = "Widgets")
	bool UseLibraryInDevBuilds;
};
