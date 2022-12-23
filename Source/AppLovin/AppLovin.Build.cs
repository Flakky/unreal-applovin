// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class AppLovin : ModuleRules
{
	public AppLovin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "UMG" });
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
			);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"Settings"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			//
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "AppLovin_UPL_IOS.xml"));
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"AppLovinSDK",
					"../../ThirdParty/iOS/AppLovinSDK.embeddedframework.zip",
					"AppLovinSDKResources.bundle"
				)
			);
			
			// ADAPTERS -----
			
			// Facebook --

			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationFacebookAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationFacebookAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 // We also need FBAudienceNetwork, but we have Facebook integration in Facebook plugin
			 
			 // Ironsource --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationIronSourceAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationIronSourceAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"IronSource",
			 		"../../ThirdParty/iOS/IronSource.embeddedframework.zip"
			 	)
			 );					 
			 
			 // Google AdMob --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationGoogleAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationGoogleAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"GoogleMobileAds",
			 		"../../ThirdParty/iOS/GoogleMobileAds.embeddedframework.zip"
			 	)
			 );		
			 
			 // AdColony --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationAdColonyAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationAdColonyAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AdColony",
			 		"../../ThirdParty/iOS/AdColony.embeddedframework.zip"
			 	)
			 );
			 
			 // Pangle --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationByteDanceAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationByteDanceAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"BUAdSDK",
			 		"../../ThirdParty/iOS/BUAdSDK.embeddedframework.zip",
			        "BUAdSDK.bundle"
			 	)
			 );			 
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "BUCNAuxiliary",
					 "../../ThirdParty/iOS/BUCNAuxiliary.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "BUFoundation",
					 "../../ThirdParty/iOS/BUFoundation.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "BUVAAuxiliary",
					 "../../ThirdParty/iOS/BUVAAuxiliary.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "CSJAdSDK",
					 "../../ThirdParty/iOS/CSJAdSDK.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "PAGAdSDK",
					 "../../ThirdParty/iOS/PAGAdSDK.embeddedframework.zip",
					 "PAGAdSDK.bundle"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "HM",
					 "../../ThirdParty/iOS/HM.embeddedframework.zip"
				 )
			 );	
 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "BURelyFoundation_Global",
					 "../../ThirdParty/iOS/BURelyFoundation_Global.embeddedframework.zip"
				 )
			 );
			 
			 // Pangle needs these to compile
			 PublicSystemLibraries.Add("c++");
			 PublicSystemLibraries.Add("z");
			 PublicSystemLibraries.Add("bz2");
			 PublicSystemLibraries.Add("c++abi");
			 PublicSystemLibraries.Add("resolv");
			 PublicSystemLibraries.Add("sqlite3");
			 PublicSystemLibraries.Add("xml2");
			 PublicSystemLibraries.Add("iconv");
			 
			 // Smaato --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationSmaatoAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationSmaatoAdapter.embeddedframework.zip"
			 	)
			 );

			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"SmaatoSDKCore",
			 		"../../ThirdParty/iOS/SmaatoSDKCore.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"SmaatoSDKInAppBidding",
			 		"../../ThirdParty/iOS/SmaatoSDKInAppBidding.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKBanner",
					 "../../ThirdParty/iOS/SmaatoSDKBanner.embeddedframework.zip"
				 )
			 );	
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKCMP",
					 "../../ThirdParty/iOS/SmaatoSDKCMP.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKInterstitial",
					 "../../ThirdParty/iOS/SmaatoSDKInterstitial.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKNative",
					 "../../ThirdParty/iOS/SmaatoSDKNative.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKOpenMeasurement",
					 "../../ThirdParty/iOS/SmaatoSDKOpenMeasurement.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKOutstream",
					 "../../ThirdParty/iOS/SmaatoSDKOutstream.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKRewardedAds",
					 "../../ThirdParty/iOS/SmaatoSDKRewardedAds.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKRichMedia",
					 "../../ThirdParty/iOS/SmaatoSDKRichMedia.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKUnifiedBidding",
					 "../../ThirdParty/iOS/SmaatoSDKUnifiedBidding.embeddedframework.zip"
				 )
			 );
			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "SmaatoSDKVideo",
					 "../../ThirdParty/iOS/SmaatoSDKVideo.embeddedframework.zip"
				 )
			 );
			 
			 // Smaato dynam lib (also gets copied in UPL_IOS)
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "OMSDK_Smaato",
					 "../../ThirdParty/iOS/OMSDK_Smaato.embeddedframework.zip"
				 )
			 );	

			 // Mintegral --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationMintegralAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationMintegralAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"MTGSDK",
			 		"../../ThirdParty/iOS/MTGSDK.embeddedframework.zip"
			 	)
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKBanner",
					 "../../ThirdParty/iOS/MTGSDKBanner.embeddedframework.zip"
				 )
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKBidding",
					 "../../ThirdParty/iOS/MTGSDKBidding.embeddedframework.zip"
				 )
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKInterstitial",
					 "../../ThirdParty/iOS/MTGSDKInterstitial.embeddedframework.zip"
				 )
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKInterstitialVideo",
					 "../../ThirdParty/iOS/MTGSDKInterstitialVideo.embeddedframework.zip"
				 )
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKNativeAdvanced",
					 "../../ThirdParty/iOS/MTGSDKNativeAdvanced.embeddedframework.zip"
				 )
			 );			 
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKNewInterstitial",
					 "../../ThirdParty/iOS/MTGSDKNewInterstitial.embeddedframework.zip"
				 )
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKReward",
					 "../../ThirdParty/iOS/MTGSDKReward.embeddedframework.zip"
				 )
			 );
			 PublicAdditionalFrameworks.Add(
				 new Framework(
					 "MTGSDKSplash",
					 "../../ThirdParty/iOS/MTGSDKSplash.embeddedframework.zip"
				 )
			 );
			 
			// InMobi --
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"AppLovinMediationInMobiAdapter",
					"../../ThirdParty/iOS/AppLovinMediationInMobiAdapter.embeddedframework.zip"
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"InMobiSDK",
					"../../ThirdParty/iOS/InMobiSDK.embeddedframework.zip"
				)
			);
			
			// Tapjoy --
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"AppLovinMediationTapjoyAdapter",
					"../../ThirdParty/iOS/AppLovinMediationTapjoyAdapter.embeddedframework.zip"
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"Tapjoy",
					"../../ThirdParty/iOS/Tapjoy.embeddedframework.zip"
				)
			);
			
			// Fyber --
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"AppLovinMediationFyberAdapter",
					"../../ThirdParty/iOS/AppLovinMediationFyberAdapter.embeddedframework.zip"
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"IASDKCore",
					"../../ThirdParty/iOS/IASDKCore.embeddedframework.zip",
					"IASDKResources.bundle"
				)
			);

			// UnityAds --
			
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"AppLovinMediationUnityAdsAdapter",
			 		"../../ThirdParty/iOS/AppLovinMediationUnityAdsAdapter.embeddedframework.zip"
			 	)
			 );
			 
			 PublicAdditionalFrameworks.Add(
			 	new Framework(
			 		"UnityAds",
			 		"../../ThirdParty/iOS/UnityAds.embeddedframework.zip"
			 	)
			 );
			 
			// VungleSDK --
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"AppLovinMediationVungleAdapter",
					"../../ThirdParty/iOS/AppLovinMediationVungleAdapter.embeddedframework.zip"
				)
			);
			
			PublicAdditionalFrameworks.Add(
				new Framework(
					"VungleSDK",
					"../../ThirdParty/iOS/VungleSDK.embeddedframework.zip"
				)
			);
		}

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Launch"
			});

			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "AppLovin_UPL_Android.xml"));
		}
	}
}
