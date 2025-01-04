#pragma once

#if PLATFORM_WINDOWS
#include "Runtime/Core/Public/Windows/WindowsPlatformMisc.h"
#endif

#if PLATFORM_MAC
#include "Runtime/Core/Public/Apple/ApplePlatformMisc.h"
#endif

#if PLATFORM_LINUX
#include "Runtime/Core/Public/Linux/LinuxPlatformMisc.h"
#endif

#include "WebUIUtils.generated.h"

UCLASS()
class OPENAIAPI_API UWebUIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
};
