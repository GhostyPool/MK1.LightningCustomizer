// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include "SDK.h"
#include "unreal\UObject.h"
#include "unreal\FName.h"
#include <mutex>

static bool s_bEnabled = false;
static float s_fLightningColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static std::mutex s_mtxLightningColour;

extern "C" PLUGIN_API const char* GetPluginName()
{
    return "Lightning customizer";
}

extern "C" PLUGIN_API const char* GetPluginProject()
{
    return "MK12HOOK";
}

extern "C" PLUGIN_API const char* GetPluginTabName()
{
    return "Lightning customizer";
}

extern "C" PLUGIN_API void OnInitialize()
{
    MK12HOOKSDK::Initialize();
}

struct FLinearColor
{
    float R,
          G,
          B,
          A;
};

struct MKCharacterActor
{
    char pad[0x528];
    FLinearColor SkinFXColorProperties;
};

extern "C" PLUGIN_API void OnBeginPlay(__int64 actorPtr)
{
    static FName raiden(L"BP_Raiden_Char_C", FNAME_Add, 1);

    if (!s_bEnabled)
        return;

    UObject* actor = reinterpret_cast<UObject*>(actorPtr);

    if (actor->Class->SuperStruct->Name == raiden)
    {
        MKCharacterActor* mkActor = reinterpret_cast<MKCharacterActor*>(actor);

        std::lock_guard<std::mutex> lock(s_mtxLightningColour);
        mkActor->SkinFXColorProperties.R = s_fLightningColour[0];
        mkActor->SkinFXColorProperties.G = s_fLightningColour[1];
        mkActor->SkinFXColorProperties.B = s_fLightningColour[2];
        mkActor->SkinFXColorProperties.A = s_fLightningColour[3];
    }
}

extern "C" PLUGIN_API void TabFunction()
{
    if (!MK12HOOKSDK::IsOK())
        return;

    MK12HOOKSDK::ImGui_Checkbox("Enable##lc_enable", &s_bEnabled);

    if (MK12HOOKSDK::ImGui_ColorEdit4("Lightning colour##lc", s_fLightningColour))
        std::lock_guard<std::mutex> lock(s_mtxLightningColour);

    MK12HOOKSDK::ImGui_Text("The colour change takes effect on character reload.");
}

extern "C" PLUGIN_API void OnShutdown()
{
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

