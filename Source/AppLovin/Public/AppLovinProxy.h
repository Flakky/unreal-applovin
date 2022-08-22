// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AppLovinModule.h"
#include "AppLovinProxy.generated.h"

UENUM(BlueprintType)
enum class EAppLovinRewardedVideoEventType : uint8
{
	Loaded,
	Showed,
	Started,
	Clicked,
	Closed,
	Completed,
	Rewarded
};

UENUM(BlueprintType)
enum class EAppLovinRewardedErrorEventType : uint8
{
	FailedToShow,
	FailedToLoad
};

UENUM(BlueprintType)
enum class EAppLovinInterstitialEventType : uint8
{
	Loaded,
	Showed,
	Clicked,
	Closed
};

UENUM(BlueprintType)
enum class EAppLovinInterstitialErrorEventType : uint8
{
	FailedToShow,
	FailedToLoad
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAppLovinRewardedVideoEvent, EAppLovinRewardedVideoEventType, EventType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAppLovinRewardedVideoErrorEvent, EAppLovinRewardedErrorEventType, EventType, int, Code, FString, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAppLovinInterstitialEvent, EAppLovinInterstitialEventType, EventType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAppLovinInterstitialErrorEvent, EAppLovinInterstitialErrorEventType, EventType, int, Code, FString, Message);

UCLASS()
class APPLOVIN_API UAppLovinProxy : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FAppLovinRewardedVideoEvent OnRewardedVideoEvent;

	UPROPERTY(BlueprintAssignable)
	FAppLovinRewardedVideoErrorEvent OnRewardedVideoErrorEvent;
	
	UPROPERTY(BlueprintAssignable)
	FAppLovinInterstitialEvent OnInterstitialEvent;
	
	UPROPERTY(BlueprintAssignable)
	FAppLovinInterstitialErrorEvent OnInterstitialErrorEvent;

	/** Show rewarded video to a user
	* @Placement - Placement name, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
    virtual void Init(){}

	/** Load interstitial for certain placement
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LoadRewardedVideo(FString Placement){}

	/** Show rewarded video to a user
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ShowRewardedVideo(FString Placement){}

	/** Load interstitial for certain placement
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LoadInterstitial(FString Placement){}

	/** Show interstitial ad to a user
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ShowInterstitial(FString Placement){}
	
	/** Show rewarded video to a user
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetPrivacyHasUserConsent(bool HasUserConsent){}

	/** Show rewarded video to a user
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetPrivacyAgeRestrictedUser(bool IsAgeRestrictedUser){}

	/** Show rewarded video to a user
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetPrivacyDoNotSell(bool DoNotSell){}

	/** Show rewarded video to a user
	* @Placement - Placement ID, which you setup in your AppLovin dashboard
	*/
	UFUNCTION(BlueprintPure)
	virtual bool DoesUserApplyToGDPR(){return false;}

	/** Show AppLovin debugger
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ShowDebugger(){}

	/**
	 * Returns Applovin proxy object to call functions
	*/
	UFUNCTION(BlueprintPure)
	static UAppLovinProxy* GetApplovin()
	{
		return FAppLovinModule::Get().AppLovinProxy;
	}
};