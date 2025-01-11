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
	//Generation ----------------------------------------------------------------------------------------------------------------------------

	// Include all basic settings for generation
	static void IncludeBasicGenerationSettings(TSharedPtr<FJsonObject> Shared, const FBasicGenerationSettings& Basics);
	// Include all necessary settings for basic completion
	static void IncludeCompletionGenerationSettings(TSharedPtr<FJsonObject> Shared, const FCompletionGenerationSettings& CompletionSettings);
	// Include all necessary settings for chat completion
	static void IncludeChatGenerationSettings(TSharedPtr<FJsonObject> Shared, const FChatCompletionGenerationSettings& ChatSettings);

	// Include custom JSON parameters
	static void IncludeCustomJSONParameters(TSharedPtr<FJsonObject> Shared, const TArray<FCustomJSONParameter>& CustomJSONParameters);

	// Include all necessary settings for starting up the model
	static void IncludeBasicModelSettings(TSharedPtr<FJsonObject> Shared, const FBasicModelSettings& BasicModelSettings);
	// Include all necessary settings for transformer type of the model
	static void IncludeTransformerModelSettings(TSharedPtr<FJsonObject> Shared, const FTransformerSettings& ModelSettings);


	// What could be done in future?
	// TODO: ExLlamav2_HF (https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab#exllamav2_hf)
	// TODO: ExLlamav2 (https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab#exllamav2)
	// TODO: AutoGPTQ (https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab#autogptq)
	// TODO: llama.cpp (https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab#llamacpp)
	// TODO: llamacpp_HF (https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab#llamacpp_hf)
	// TODO: AutoAWQ (https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab#autoawq)
};
