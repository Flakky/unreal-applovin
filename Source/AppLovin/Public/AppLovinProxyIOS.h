// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AppLovinProxy.h"
#include "AppLovinProxyIOS.generated.h"

UCLASS()
class APPLOVIN_API UAppLovinProxyIOS : public UAppLovinProxy
{
	GENERATED_BODY()

#if PLATFORM_IOS

	virtual void ShowRewardedVideo(FString Placement) override;
	
	virtual void LoadRewardedVideo(FString Placement) override;
	
	virtual void ShowInterstitial(FString Placement) override;
	
	virtual void LoadInterstitial(FString Placement) override;

	virtual void Init() override;
	
	virtual void ShowDebugger() override;

	virtual void SetPrivacyHasUserConsent(bool HasUserConsent) override;
	
	virtual void SetPrivacyAgeRestrictedUser(bool IsAgeRestrictedUser) override;

	virtual void SetPrivacyDoNotSell(bool DoNotSell) override;

	virtual bool DoesUserApplyToGDPR() override;

#endif
};