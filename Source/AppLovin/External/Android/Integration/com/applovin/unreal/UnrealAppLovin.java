package com.applovin.unreal;

import android.app.NativeActivity;

import com.applovin.sdk.AppLovinSdk;
import com.applovin.sdk.AppLovinSdkConfiguration;

import com.applovin.unreal.UnrealALRewardedVideo;
import com.applovin.unreal.UnrealALInterstitial;
import com.applovin.unreal.UnrealALPrivacy;

public class UnrealAppLovin
{
    private static UnrealAppLovin unrealAL;
    private static AppLovinSdk sdk = null;
    private static boolean initialized = false;

    public static void init(NativeActivity appActivity)
    {
        if(initialized) return;
        
        sdk = AppLovinSdk.getInstance(appActivity);
        
        sdk.setMediationProvider( "max" );
        sdk.getSettings().setVerboseLogging( true );
        
        AppLovinSdk.initializeSdk(appActivity, new AppLovinSdk.SdkInitializationListener() {
            @Override
            public void onSdkInitialized(final AppLovinSdkConfiguration configuration)
            {
                UnrealALRewardedVideo.init(appActivity, sdk);
                UnrealALInterstitial.init(appActivity, sdk);
                
                UnrealALPrivacy.init(appActivity, configuration);
                
                initialized = true;
            }
        });
    }
    
    public void showDebugger(){
        sdk.showMediationDebugger();
    }
}