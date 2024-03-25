// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppLovinProxy.h"
#include "AppLovinProxyTest.generated.h"

UCLASS()
class APPLOVIN_API UAppLovinProxyTest : public UAppLovinProxy
{
	GENERATED_BODY()

private:

	FTimerHandle LoadRewardedVideoTimer;
	FTimerHandle LoadInterstitialTimer;

public:
	
	virtual void ShowRewardedVideo(FString Placement) override;
	
	virtual void LoadRewardedVideo(FString Placement) override;
	
	virtual void ShowInterstitial(FString Placement) override;
	
	virtual void LoadInterstitial(FString Placement) override;
	
	virtual void ShowDebugger() override;

protected:

	UFUNCTION()
	void OnRewardedVideoLoaded() const;

	UFUNCTION()
	void OnInterstitialLoaded() const;
};
