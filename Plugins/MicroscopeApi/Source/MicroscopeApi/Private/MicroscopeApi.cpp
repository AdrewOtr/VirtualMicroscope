// Copyright Epic Games, Inc. All Rights Reserved.

#include "MicroscopeApi.h"

DEFINE_LOG_CATEGORY(LogMicroscopeApi);

#define LOCTEXT_NAMESPACE "FMicroscopeApiModule"

void FMicroscopeApiModule::StartupModule()
{
	UE_LOG(LogMicroscopeApi, Log, TEXT("ArtheonShared module started."));
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMicroscopeApiModule::ShutdownModule()
{
	UE_LOG(LogMicroscopeApi, Log, TEXT("ArtheonShared module shut down."));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMicroscopeApiModule, MicroscopeApi)