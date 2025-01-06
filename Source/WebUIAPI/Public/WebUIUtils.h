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
#include "WebUIDefinitions.h"


#include "WebUIUtils.generated.h"

UCLASS()
class WEBUIAPI_API UWebUIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void IncludeBasicGenerationSettings(TSharedPtr<FJsonObject> Shared, const FBasicGenerationSettings& Basics);
	static void IncludeCompletionGenerationSettings(TSharedPtr<FJsonObject> Shared, const FCompletionGenerationSettings& CompletionSettings);
	static void IncludeChatGenerationSettings(TSharedPtr<FJsonObject> Shared, const FChatCompletionGenerationSettings& ChatSettings);
};
