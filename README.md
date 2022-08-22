# Unreal AppLovin SDK plugin
Unofficial Applovin SDK integration for Unreal Engine. Plugin also includes several networks integrations.

![Applovin Unreal Engine](/Resources/icon128.png)

## Integration

### Platforms

* Android
* IOS

### Integrated types of ads

* Rewarded ads
* Interstitial

### Integrated networks

* Applovin Network
* Adcolony
* Admob
* Fyber
* InMoby
* Ironsource
* Meta (Facebook)
* Mintegral
* Pangle (Bytedance)
* Smaato
* TapJoy
* Vungle
* UnityAds

## How to use

### Install

1. Clone repository or download zip archive. *Please note, that repository uses Git LFS for iOS libraries and uassets.*
2. Create `AppLovin` folder in `Plugins` folder of your project and place everything there. Path should look like this: `Project/Plugins/AppLovin/AppLovin.uplugin`.
3. Regenerate project's files and compile it.
4. Plugin should enable automatically. But if don't, open editor, and enable it via Plugins manager window.
5. Fill your networks id's in UPL files.

![Setup AppLovin keys for Android](/Docs/Seup_Keys_Android.jpg)

![Setup AppLovin keys for IOS](/Docs/Seup_Keys_IOS.jpg)

### Usage

Plugin initializes automatically. Get AppLovin object to get access to ads. You should be able to get this object from any place. 

*Note, that in order to get AppLovin object from UObjects, they must have access to a World (GetWorld)*


Use `Load` function to load ad, and when they are loaded, use `Show` function. You must also pass ad placement UnitID you get from Applovin console.
Use delegate events to call your logic after something happend in a plugin. For example ad was loaded of rewarded.

#### Interstitial
![Use Applovin in Blueprints](/Docs/BP_Interstitial.jpg)

```c++
UAppLovinProxy::GetApplovin()->LoadInterstitial("UnitID_HERE");
UAppLovinProxy::GetApplovin()->ShowInterstitial("UnitID_HERE");

UAppLovinProxy::GetApplovin()->OnInterstitialEvent.AddDynamic(this, &UMySomeObject::OnInterstitialEvent);
UAppLovinProxy::GetApplovin()->OnInterstitialErrorEvent.AddDynamic(this, &UMySomeObject::OnInterstitialErrorEvent);
```

#### Rewarded video

![Use Applovin in Blueprints](/Docs/BP_Rewarded.jpg)

```c++
UAppLovinProxy::GetApplovin()->LoadRewardedVideo("UnitID_HERE");
UAppLovinProxy::GetApplovin()->ShowRewardedVideo("UnitID_HERE");

UAppLovinProxy::GetApplovin()->OnRewardedVideoEvent.AddDynamic(this, &UMySomeObject::OnRewardedVideoEvent);
UAppLovinProxy::GetApplovin()->OnRewardedVideoErrorEvent.AddDynamic(this, &UMySomeObject::OnRewardedVideoErrorEvent);
```

#### Debuger

Use debugger to check integration and applovin information in development builds.

![Use Applovin in Blueprints](/Docs/BP_Debugger.jpg)

```c++
UAppLovinProxy::GetApplovin()->ShowDebugger();
```

#### Test widget

By default, test widget gets shown in development builds and editor, so you do not see ads when testing your game.

You can enable showing ads in development buils by enabling `Use library in dev builds` in `Project Settins -> Plugins -> AppLovin`.
