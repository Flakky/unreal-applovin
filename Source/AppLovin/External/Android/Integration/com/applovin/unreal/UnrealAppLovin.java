package com.applovin.unreal;

import android.app.NativeActivity;
import android.util.Log;
import android.net.Uri;

import com.applovin.sdk.*;

import com.applovin.unreal.UnrealALRewardedVideo;
import com.applovin.unreal.UnrealALInterstitial;
import com.applovin.unreal.UnrealALPrivacy;

public class UnrealAppLovin
{
    private static UnrealAppLovin unrealAL;
    private static AppLovinSdk sdk = null;
    private static boolean initialized = false;
    private static NativeActivity activity = null;
    
    static public class UnrealAppLovinInitParams{
        public boolean enableConsentFlow = false;
        public String privacyPolicyURL = "";
        public String termsOfServiceURL = "";
    }

    public static void init(NativeActivity appActivity, UnrealAppLovinInitParams params)
    {
        if(initialized) return;
        
        activity = appActivity;
        
        sdk = AppLovinSdk.getInstance(appActivity);
        
        sdk.setMediationProvider(AppLovinMediationProvider.MAX);
        
        AppLovinSdkSettings settings = new AppLovinSdkSettings(appActivity);
        settings.getTermsAndPrivacyPolicyFlowSettings().setEnabled(params.enableConsentFlow);
        settings.getTermsAndPrivacyPolicyFlowSettings().setPrivacyPolicyUri(Uri.parse(params.privacyPolicyURL));
        settings.getTermsAndPrivacyPolicyFlowSettings().setTermsOfServiceUri(Uri.parse(params.termsOfServiceURL));
        
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
    
    public static void showDebugger(){
        Log.d("ApplovinLog", "Show debugger");
        sdk.showMediationDebugger();
    }
    
}