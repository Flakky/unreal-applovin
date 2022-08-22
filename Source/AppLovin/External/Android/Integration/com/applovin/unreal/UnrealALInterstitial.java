package com.applovin.unreal;

import android.app.NativeActivity;

import com.applovin.sdk.AppLovinSdk;
import com.applovin.sdk.AppLovinSdkConfiguration;

import com.applovin.mediation.MaxAd;
import com.applovin.mediation.MaxAdListener;
import com.applovin.mediation.MaxAdRevenueListener;
import com.applovin.mediation.MaxError;
import com.applovin.mediation.ads.MaxInterstitialAd;

import android.util.Log;
import java.util.Map;
import java.util.HashMap;
import java.lang.reflect.Method;

public class UnrealALInterstitial
{
    private static NativeActivity activity;
    private static Map<String, MaxInterstitialAd> InterstitialAds;
    
    private native static void onInterstitialAdLoadedThunkCpp();
    private native static void onInterstitialAdShowedThunkCpp();
    private native static void onInterstitialAdClosedThunkCpp();
    private native static void onInterstitialAdLoadFailedThunkCpp(int errorCode, String errorMessage);
    private native static void onInterstitialAdShowFailedThunkCpp(int errorCode, String errorMessage);
    private native static void onInterstitialAdClickedThunkCpp();
    
    static public void init(NativeActivity appActivity)
    {
        activity = appActivity;
        
        InterstitialAds = new HashMap<String, MaxInterstitialAd>();
        
        Log.d("ApplovinLog", "Init Interstitial Class");
    }
    
    static private void createInterstitial(String uintId)
    {
        Log.d("ApplovinLog", "Init AppLovin Interstitial");
        
        MaxInterstitialAd Ad = new MaxInterstitialAd( uintId, activity );
        
        MaxAdListener AdListener = new MaxAdListener(){
        
            @Override
            public void onAdLoaded(final MaxAd maxAd)
            {
                Log.d("ApplovinLog", "Loaded Interstitial ad");
                    
                // Rewarded ad is ready to be shown. interstitialAd.isReady() will now return 'true'
                onInterstitialAdLoadedThunkCpp();
            }
                
            @Override
            public void onAdLoadFailed(final String adUnitId, final MaxError error)
            {
                Log.d("ApplovinLog", "Load Interstitial failed: "+error.getCode()+" msg: "+error.getMessage());
                
                // Interstitial ad failed to load 
                // We recommend retrying with exponentially higher delays up to a maximum delay (in this case 64 seconds)
                onInterstitialAdLoadFailedThunkCpp(error.getCode(), error.getMessage());
                
            }
        
            @Override
            public void onAdDisplayFailed(final MaxAd maxAd, final MaxError error)
            {
                Log.d("ApplovinLog", "Show Interstitial failed: "+error.getCode()+" msg: "+error.getMessage());
                onInterstitialAdShowFailedThunkCpp(error.getCode(), error.getMessage());
            }
        
            @Override
            public void onAdDisplayed(final MaxAd maxAd) 
            {
                Log.d("ApplovinLog", "Displayed Interstitial ad");
                onInterstitialAdShowedThunkCpp();
            }
        
            @Override
            public void onAdClicked(final MaxAd maxAd) 
            {
                Log.d("ApplovinLog", "Clicked Interstitial ad");
                onInterstitialAdClickedThunkCpp();
            }
        
            @Override
            public void onAdHidden(final MaxAd maxAd)
            {
                Log.d("ApplovinLog", "Hide Interstitial ad");
                onInterstitialAdClosedThunkCpp();
            }
        };
        
        Ad.setListener(AdListener);
        
        InterstitialAds.put(uintId, Ad);
        
        Ad.loadAd();
        
    }
    
    static public void loadInterstitial(String uintId)
    {
        MaxInterstitialAd Ad = InterstitialAds.get(uintId);
        if(Ad != null){
            Ad.loadAd();
        }
        else{
            createInterstitial(uintId);
        }
    }
    
    static public void showInterstitial(String uintId)
    {
        Log.d("ApplovinLog", "Show Interstitial ad");
        MaxInterstitialAd Ad = InterstitialAds.get(uintId);
        
        if(Ad != null && Ad.isReady()){
            Ad.showAd();
        }
        else {
            Log.d("ApplovinLog", "No Interstitial ad or it is not ready! Load it!");
        }
    }
}
