// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AppLovinAdsWidgetTest.generated.h"

class UAppLovinProxyTest;

UCLASS()
class APPLOVIN_API UAppLovinAdsWidgetTest : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
	UAppLovinProxyTest* Proxy;

	bool bIsInterstitial;

public:

	void Init(UAppLovinProxyTest* ProxyTest, bool IsInterstitial);

protected:

	UFUNCTION(BlueprintCallable)
	void CloseAds();
};
