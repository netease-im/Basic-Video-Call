// Copyright Epic Games, Inc. All Rights Reserved.

#include "NertcPlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FNertcPluginModule"

void FNertcPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("NertcPlugin")->GetBaseDir();

	NertcDllHandler = nullptr;
#if UE_EDITOR && PLATFORM_WINDOWS
  // Add on the relative location of the third party dll and load it
 // FString LibraryPath;
	//LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/Nertc/Win/x64/Release/nertc-c-sdk.dll"));
 // NertcDllHandler = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
 // if (NertcDllHandler){
 //   // Call the test function in the third party library that opens a message box
 // }else{
 //   FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
 // }
#endif // PLATFORM_WINDOWS	
}

void FNertcPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
#if UE_EDITOR && PLATFORM_WINDOWS
	/*if(NertcDllHandler != nullptr){
		FPlatformProcess::FreeDllHandle(NertcDllHandler);
		NertcDllHandler = nullptr;
	}*/
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNertcPluginModule, NertcPlugin)
