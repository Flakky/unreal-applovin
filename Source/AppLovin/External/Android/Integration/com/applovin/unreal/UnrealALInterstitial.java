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
    private static UnrealALInterstitialListener interstitialListener;
    private static AppLovinSdk sdk;
    private static NativeActivity activity;
    private static Map<String, MaxInterstitialAd> InterstitialAds;
    
    private native static void onInterstitialAdLoadedThunkCpp();
    private native static void onInterstitialAdShowedThunkCpp();
    private native static void onInterstitialAdClosedThunkCpp();
    private native static void onInterstitialAdLoadFailedThunkCpp(int errorCode, String errorMessage);
    private native static void onInterstitialAdShowFailedThunkCpp(int errorCode, String errorMessage);
    private native static void onInterstitialAdClickedThunkCpp();
    private native static void onAppLovinRevenueThunkCpp(double revenue, String network, String unitId, String placement, String country);
    
    static public void init(NativeActivity appActivity, AppLovinSdk appLovinSDK)
    {
        activity = appActivity;
        sdk = appLovinSDK;
        InterstitialAds = new HashMap<String, MaxInterstitialAd>(); // Ok
        UnrealALInterstitial.interstitialListener = new UnrealALInterstitialListener(); // Error
        
        Log.d("ApplovinLog", "Init Interstitial Class");
    }
    
    static private void createInterstitial(String uintId)
    {
        if(uintId == null) return;
        
        Log.d("ApplovinLog", "Init AppLovin Interstitial " + uintId);
        
        MaxInterstitialAd Ad = new MaxInterstitialAd( uintId, activity );
        
        Ad.setListener(interstitialListener);
        Ad.setRevenueListener(interstitialListener);
        
        InterstitialAds.put(uintId, Ad);
        
        Ad.loadAd();
    }
    
    static public void loadInterstitial(String uintId)
    {
        if(InterstitialAds == null || uintId == null) return;
        
        Log.d("ApplovinLog", "Load Interstitial ad " + uintId);
        
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
        Log.d("ApplovinLog", "Show Interstitial ad " + uintId);
        
        if(InterstitialAds == null || uintId == null) return;
        
        MaxInterstitialAd Ad = InterstitialAds.get(uintId);
        
        if(Ad != null && Ad.isReady()){
            Ad.showAd();
        }
        else {
            Log.d("ApplovinLog", "No Interstitial ad or it is not ready! Load it!");
        }
    }
    
    private static class UnrealALInterstitialListener
        implements MaxAdListener, MaxAdRevenueListener
    {
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
        
        @Override
        public void onAdRevenuePaid(final MaxAd ad)
        {
            if(ad == null){
                onAppLovinRevenueThunkCpp(0.0, "", "", "", "");
                return;
            }
            
            double revenue = ad.getRevenue(); // In USD
            
            // Miscellaneous data
            String countryCode = sdk.getConfiguration().getCountryCode(); // "US" for the United States, etc - Note: Do not confuse this with currency code which is "USD" in most cases!
            String networkName = ad.getNetworkName(); // Display name of the network that showed the ad (e.g. "AdColony")
            String adUnitId = ad.getAdUnitId(); // The MAX Ad Unit ID
            String placement = ad.getPlacement(); // The placement this ad's postbacks are tied to
            String networkPlacement = ad.getNetworkPlacement(); // The placement ID from the network that showed the ad
            
            Log.d("ApplovinLog", "Interstitial revenue: " + revenue + " adunitID: " + adUnitId);
            
            onAppLovinRevenueThunkCpp(revenue, networkName, adUnitId, placement, countryCode);
        }
    }
}