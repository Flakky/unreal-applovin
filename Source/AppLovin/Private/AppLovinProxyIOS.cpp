// Copyright Epic Games, Inc. All Rights Reserved.

#if PLATFORM_IOS

#include "AppLovinProxyIOS.h"
#include "Async/Async.h"

#import <AppLovinSDK/AppLovinSDK.h>

UAppLovinProxy* Proxy;

// Interstitial

@interface ALInterstitialViewController : NSObject <MAAdDelegate>
@property (nonatomic, strong) MAInterstitialAd *interstitialAd;
@property (nonatomic, assign) NSInteger retryAttempt;

- (void)createInterstitialAd:(NSString *)unitId;
- (void)loadAd;
- (void)showAd;

- (void)didLoadAd:(MAAd *)ad;
- (void)didFailToLoadAdForAdUnitIdentifier:(NSString *)adUnitIdentifier withError:(MAError *)error;
- (void)didDisplayAd:(MAAd *)ad;
- (void)didClickAd:(MAAd *)ad;
- (void)didHideAd:(MAAd *)ad;
- (void)didFailToDisplayAd:(MAAd *)ad withError:(MAError *)error;
@end

@implementation ALInterstitialViewController

- (void)createInterstitialAd:(NSString *)unitId
{
	self.interstitialAd = [[MAInterstitialAd alloc] initWithAdUnitIdentifier: unitId];
	self.interstitialAd.delegate = self;

	// Load the first ad
	[self.interstitialAd loadAd];
}

- (void)loadAd
{
	[self.interstitialAd loadAd];
}

- (void)showAd
{
	if ( [self.interstitialAd isReady] )
	{
		[self.interstitialAd showAd];
	}
}

#pragma mark - MAAdDelegate Protocol

- (void)didLoadAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Loaded);
		}
	});
}

- (void)didFailToLoadAdForAdUnitIdentifier:(NSString *)adUnitIdentifier withError:(MAError *)error
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnInterstitialErrorEvent.Broadcast(EAppLovinInterstitialErrorEventType::FailedToLoad, 0, "");
		}
	});
}

- (void)didDisplayAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Showed);
		}
	});
}

- (void)didClickAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Clicked);
		}
	});
}

- (void)didHideAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnInterstitialEvent.Broadcast(EAppLovinInterstitialEventType::Closed);
		}
	});
}

- (void)didFailToDisplayAd:(MAAd *)ad withError:(MAError *)error
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnInterstitialErrorEvent.Broadcast(EAppLovinInterstitialErrorEventType::FailedToShow, 0, "");
		}
	});
}

@end

// Rewarded
@interface ALRewardedVideoViewController : NSObject <MARewardedAdDelegate>
@property (nonatomic, strong) MARewardedAd *rewardedAd;
@property (nonatomic, assign) NSInteger retryAttempt;

- (void)createRewardedAd:(NSString *)unitId;
- (void)didLoadAd:(MAAd *)ad;
- (void)didFailToLoadAdForAdUnitIdentifier:(NSString *)adUnitIdentifier withError:(MAError *)error;
- (void)didDisplayAd:(MAAd *)ad;
- (void)didClickAd:(MAAd *)ad;
- (void)didHideAd:(MAAd *)ad;
- (void)didFailToDisplayAd:(MAAd *)ad withError:(MAError *)error;
- (void)didStartRewardedVideoForAd:(MAAd *)ad;
- (void)didCompleteRewardedVideoForAd:(MAAd *)ad;
- (void)didRewardUserForAd:(MAAd *)ad withReward:(MAReward *)reward;
@end

@implementation ALRewardedVideoViewController

- (void)createRewardedAd:(NSString *)unitId
{
	self.rewardedAd = [MARewardedAd sharedWithAdUnitIdentifier: unitId];
	self.rewardedAd.delegate = self;

	// Load the first ad
	[self.rewardedAd loadAd];
}

- (void)loadAd
{
	[self.rewardedAd loadAd];
}

- (void)showAd
{
	if ( [self.rewardedAd isReady] )
	{
		[self.rewardedAd showAd];
	}
}

#pragma mark - MAAdDelegate Protocol

- (void)didLoadAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Loaded);
		}
	});
}

- (void)didFailToLoadAdForAdUnitIdentifier:(NSString *)adUnitIdentifier withError:(MAError *)error
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoErrorEvent.Broadcast(EAppLovinRewardedErrorEventType::FailedToLoad, 0, FString(""));
		}
	});
}

- (void)didDisplayAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Showed);
		}
	});
}

- (void)didClickAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Clicked);
		}
	});
}

- (void)didHideAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Closed);
		}
	});
}

- (void)didFailToDisplayAd:(MAAd *)ad withError:(MAError *)error
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoErrorEvent.Broadcast(EAppLovinRewardedErrorEventType::FailedToShow, 0, FString(""));
		}
	});
}

#pragma mark - MARewardedAdDelegate Protocol

- (void)didStartRewardedVideoForAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Started);
		}
	});
}

- (void)didCompleteRewardedVideoForAd:(MAAd *)ad
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Completed);
		}
	});
}

- (void)didRewardUserForAd:(MAAd *)ad withReward:(MAReward *)reward
{
	AsyncTask(ENamedThreads::GameThread, [self]() {
		if (Proxy)
		{
			Proxy->OnRewardedVideoEvent.Broadcast(EAppLovinRewardedVideoEventType::Rewarded);
		}
	});
}

@end

static ALInterstitialViewController *interstitialViewController;
static ALRewardedVideoViewController *rewardedViewController;
static ALSdkConfiguration* alConfiguration;

// Unreal

void UAppLovinProxyIOS::Init()
{
	Proxy = this;

	[ALSdk shared].mediationProvider = @"max";
    
	[[ALSdk shared] initializeSdkWithCompletionHandler:^(ALSdkConfiguration *configuration) {
		alConfiguration = configuration;
	}];

	interstitialViewController = [ALInterstitialViewController alloc];
	rewardedViewController = [ALRewardedVideoViewController alloc];
}

void UAppLovinProxyIOS::ShowDebugger()
{
	[[ALSdk shared] showMediationDebugger];
}

void UAppLovinProxyIOS::ShowRewardedVideo(FString Placement)
{
	if(rewardedViewController)
	{
		if(rewardedViewController.rewardedAd)
		{
			[rewardedViewController showAd];
		}
	}
}

void UAppLovinProxyIOS::LoadRewardedVideo(FString Placement)
{
	if(rewardedViewController)
	{
		if(rewardedViewController.rewardedAd)
		{
			[rewardedViewController loadAd];
		}
		else
		{
			[rewardedViewController createRewardedAd:[NSString stringWithFString:Placement]];
		}
	}
}

void UAppLovinProxyIOS::ShowInterstitial(FString Placement)
{
	if(interstitialViewController)
	{
		if(interstitialViewController.interstitialAd)
		{
			[interstitialViewController showAd];
		}
	}
}

void UAppLovinProxyIOS::LoadInterstitial(FString Placement)
{
	if(interstitialViewController)
	{
		if(interstitialViewController.interstitialAd)
		{
			[interstitialViewController loadAd];
		}
		else
		{
			[interstitialViewController createInterstitialAd:[NSString stringWithFString:Placement]];
		}
	}
}

void UAppLovinProxyIOS::SetPrivacyHasUserConsent(bool HasUserConsent)
{
	[ALPrivacySettings setHasUserConsent: HasUserConsent ? YES : NO];
}
	
void UAppLovinProxyIOS::SetPrivacyAgeRestrictedUser(bool IsAgeRestrictedUser)
{
	[ALPrivacySettings setIsAgeRestrictedUser: IsAgeRestrictedUser ? YES : NO];
}

void UAppLovinProxyIOS::SetPrivacyDoNotSell(bool DoNotSell)
{
	[ALPrivacySettings setDoNotSell: DoNotSell ? YES : NO];
}

bool UAppLovinProxyIOS::DoesUserApplyToGDPR()
{
	return alConfiguration.consentDialogState == ALConsentDialogStateApplies;
}
#endif