package com.applovin.unreal;

import android.app.NativeActivity;

import com.applovin.sdk.AppLovinPrivacySettings;
import com.applovin.sdk.AppLovinSdkConfiguration;

import android.util.Log;

public class UnrealALPrivacy
{
    private static NativeActivity activity;
    private static AppLovinSdkConfiguration configuration;
    
    static public void init(NativeActivity appActivity, AppLovinSdkConfiguration alconfiguration)
    {
        activity = appActivity;
        configuration = alconfiguration;
    }
    
    static public void setHasUserConsent(boolean HasUserConsent)
    {
        AppLovinPrivacySettings.setHasUserConsent( HasUserConsent, activity );
        
        Log.d("ApplovinLog", "Set Has User Content");
    }
    
    static public void setIsAgeRestrictedUser(boolean HasUserConsent)
    {
        AppLovinPrivacySettings.setIsAgeRestrictedUser( HasUserConsent, activity );
        
        Log.d("ApplovinLog", "Set Is Age Restricted User");
    }
    
    static public void setDoNotSell(boolean HasUserConsent)
    {
        AppLovinPrivacySettings.setDoNotSell( HasUserConsent, activity );
        
        Log.d("ApplovinLog", "Set Do Not Sell");
    }
    
    static public boolean doesUserApplyToGDPR()
    {
        return configuration.getConsentDialogState() == AppLovinSdkConfiguration.ConsentDialogState.APPLIES;
    }
    
}
