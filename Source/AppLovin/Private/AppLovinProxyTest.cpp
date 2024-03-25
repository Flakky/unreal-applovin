// Fill out your copyright notice in the Description page of Project Settings.

#include "AppLovinProxyTest.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "AppLovinAdsWidgetTest.h"
#include "AppLovinSettings.h"

void UAppLovinProxyTest::ShowRewardedVideo(FString Placement)
{
	const TSubclassOf<UAppLovinAdsWidgetTest> TestWidgetClass = GetDefault<UAppLovinSettings>()->TestWidgetClass;
	if(!TestWidgetClass) return;
	
	UAppLovinAdsWidgetTest* AdsWidget = CreateWidget<UAppLovinAdsWidgetTest, UWorld>(GetWorld(), TestWidgetClass);
	if(!AdsWidget) return;
	
	AdsWidget->Init(this, false);
	AdsWidget->AddToViewport(99999);
	
	OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Showed);
}

void UAppLovinProxyTest::LoadRewardedVideo(FString Placement)
{
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(LoadRewardedVideoTimer, this, &UAppLovinProxyTest::OnRewardedVideoLoaded, FMath::RandRange(3.f, 10.f));
}

void UAppLovinProxyTest::ShowInterstitial(FString Placement)
{
	UAppLovinAdsWidgetTest* AdsWidget = CreateWidget<UAppLovinAdsWidgetTest, UWorld>(GetWorld(), GetDefault<UAppLovinSettings>()->TestWidgetClass);
	if(!AdsWidget) return;
	AdsWidget->Init(this, true);
	AdsWidget->AddToViewport(99999);
	
	OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Showed);
}

void UAppLovinProxyTest::LoadInterstitial(FString Placement)
{
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(LoadInterstitialTimer, this, &UAppLovinProxyTest::OnInterstitialLoaded, FMath::RandRange(3.f, 10.f));
		return;
	}

	OnInterstitialLoaded();
}

void UAppLovinProxyTest::ShowDebugger()
{
	// TODO: Allow debugger to be shown even with test proxy
}

void UAppLovinProxyTest::OnRewardedVideoLoaded() const
{
	OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Loaded);
}

void UAppLovinProxyTest::OnInterstitialLoaded() const
{
	OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Loaded);
}
