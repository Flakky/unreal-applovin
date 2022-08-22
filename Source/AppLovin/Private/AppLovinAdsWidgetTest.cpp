// Fill out your copyright notice in the Description page of Project Settings.

#include "AppLovinAdsWidgetTest.h"
#include "AppLovinProxyTest.h"

void UAppLovinAdsWidgetTest::Init(UAppLovinProxyTest* ProxyTest, bool IsInterstitial)
{
	Proxy = ProxyTest;
	bIsInterstitial = IsInterstitial;
}


void UAppLovinAdsWidgetTest::CloseAds()
{
	if(Proxy)
	{
		if(bIsInterstitial) Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Closed);
		else Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Rewarded);
	}

	RemoveFromParent();
}
