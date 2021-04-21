// Fill out your copyright notice in the Description page of Project Settings.
#include "FRGameInstance.h"

#include "Blueprint/UserWidget.h"

#if defined(_MSC_VER)
#pragma comment(lib,"miniupnpc.lib")
#endif

UFRGameInstance::UFRGameInstance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer) {
    OnlineMode = EOnlineMode::Offline; //default to offline
    CurrentState = EFRState::None; //default to none

    //// port opening for multiplayer //// ref:https://dev.to/cryptgar/an-intro-to-miniupnp-35me
    upnp.error = 0;
    upnp.dev = 0;

    //discover UPnP devices on network
    upnp.dev = upnpDiscover(2000, NULL, NULL, 0, 0, 2, &upnp.error);
    if(upnp.error || !upnp.dev) {
        UE_LOG(LogTemp, Error, TEXT("[MiniUPnP] error discovering upnp devices: %s"), strupnperror(upnp.error)); 
        return;
    }

    //retrieve the Internet Gateway Device
    upnp.port = "7777";

    int status = UPNP_GetValidIGD(upnp.dev, &upnp.urls, &upnp.data, upnp.aLanAddr, sizeof(upnp.aLanAddr));
    UE_LOG(LogTemp, Warning, TEXT("[MiniUPnP] status=%d, lan_addr=%s"), status, *FString(upnp.aLanAddr));

    if(status == 1) {
        UE_LOG(LogTemp, Warning, TEXT("[MiniUPnP] found valid IGD: %s"), *FString(upnp.urls.controlURL));
        upnp.error = UPNP_AddPortMapping(upnp.urls.controlURL, upnp.data.first.servicetype,
                                    upnp.port, // external port
                                    upnp.port, // internal port
                                    upnp.aLanAddr, "FreeRunners", "UDP",
                                    0,  // remote host
                                    "0" // lease duration, recommended 0 as some NAT
                                        // implementations may not support another value
                                    );
        if(upnp.error) {
            UE_LOG(LogTemp, Error, TEXT("[MiniUPnP] failed to map port: %s; error: %s"), *FString(upnp.port), *FString(strupnperror(upnp.error)));
        } else {
            UE_LOG(LogTemp, Warning, TEXT("[MiniUPnP] successfully mapped port: %s"), *FString(upnp.port));
        }
    } else {
        UE_LOG(LogTemp, Error, TEXT("[MiniUPnP] no valid IGD found"));
    }
}

void UFRGameInstance::Shutdown() {
    upnp.error = UPNP_DeletePortMapping(upnp.urls.controlURL,
                                 upnp.data.first.servicetype, upnp.port, "UDP", 0);
    if(upnp.error) UE_LOG(LogTemp, Error, TEXT("[MiniUPnP] port map deletion error: %s"), *FString(strupnperror(upnp.error)));
    FreeUPNPUrls(&upnp.urls);
    freeUPNPDevlist(upnp.dev);

    UGameInstance::Shutdown();
}

UUserWidget* UFRGameInstance::TransitionToState(EFRState state) {
    if(state == CurrentState) return nullptr; //early out

    //remove old UI widgets
    FString oldState;
    switch(CurrentState) {
        case(EFRState::None):default:                                       oldState = FString("NONE");        break;
        case(EFRState::Playing):     PlayUIWidget->RemoveFromParent();      oldState = FString("PLAYING");     break;
        case(EFRState::MainMenu):    MainMenuWidget->RemoveFromParent();    oldState = FString("MAINMENU");    break;
        case(EFRState::Loading):     LoadingWidget->RemoveFromParent();     oldState = FString("LOADING");     break;
        case(EFRState::Multiplayer): MultiplayerWidget->RemoveFromParent(); oldState = FString("MULTIPLAYER"); break;
        case(EFRState::LevelSelect): LevelSelectWidget->RemoveFromParent(); oldState = FString("LEVELSELECT"); break;
        case(EFRState::Settings):    SettingsWidget->RemoveFromParent();    oldState = FString("SETTINGS");    break;
    }
    CurrentState = state;

    //add new UI widgets
    FString newState;
    UUserWidget* out = nullptr;
    switch(state) {
        default:                                                         newState = FString("NONE");        out = nullptr;           break;
        case(EFRState::Playing):     PlayUIWidget->AddToViewport();      newState = FString("PLAYING");     out = PlayUIWidget;      break;
        case(EFRState::MainMenu):    MainMenuWidget->AddToViewport();    newState = FString("MAINMENU");    out = MainMenuWidget;    break;
        case(EFRState::Loading):     LoadingWidget->AddToViewport();     newState = FString("LOADING");     out = LoadingWidget;     break;
        case(EFRState::Multiplayer): MultiplayerWidget->AddToViewport(); newState = FString("MULTIPLAYER"); out = MultiplayerWidget; break;
        case(EFRState::LevelSelect): LevelSelectWidget->AddToViewport(); newState = FString("LEVELSELECT"); out = LevelSelectWidget; break;
        case(EFRState::Settings):    SettingsWidget->AddToViewport();    newState = FString("SETTINGS");    out = SettingsWidget;    break;
    }
    UE_LOG(LogTemp, Warning, TEXT("Switching state from %s to %s"), *oldState, *newState);
    return out;
}