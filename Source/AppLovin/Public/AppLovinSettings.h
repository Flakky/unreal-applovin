// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AppLovinSettings.generated.h"

class UAppLovinAdsWidgetTest;

UCLASS(config = Engine, defaultconfig)
class UAppLovinSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = "Applovin")
    FString SDKKeyIOS;

    UPROPERTY(Config, EditAnywhere, Category = "Applovin")
    FString SDKKeyAndroid;

	UPROPERTY(Config, EditAnywhere, Category = "Applovin")
	FString AdmobKeyIOS;

	UPROPERTY(Config, EditAnywhere, Category = "Applovin")
	FString AdmobKeyAndroid;

	UPROPERTY(Config, EditAnywhere, Category = "Debug")
	TSubclassOf<UAppLovinAdsWidgetTest> TestWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category = "Debug")
	bool UseLibraryInDevBuilds;

	UPROPERTY(Config, EditAnywhere, Category = "Debug")
	bool VerboseLogging;

	UPROPERTY(Config, EditAnywhere, Category = "Constent")
	bool ConsentFlow;

	UPROPERTY(Config, EditAnywhere, Category = "Constent")
	FString PrivacyPolicyURL;

	UPROPERTY(Config, EditAnywhere, Category = "Constent")
	FString TermsOfServiceURL;
};
