#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "WebUIDefinitions.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

/**
 * 
 */
class WEBUIAPI_API WebUIParser
{
public:
	WebUIParser() = default;
	WebUIParser(const FCompletionWebUiSettings&);
	WebUIParser(const FChatCompletionWebUiSettings&);

	WebUIParser(const FCompletionGenerationSettings&);
	WebUIParser(const FChatCompletionGenerationSettings&);
	
	~WebUIParser();


	FCompletionWebUiSettings webUiSettings;
	FChatCompletionWebUiSettings chatWebUiSettings;

	FCompletionGenerationSettings CompletionGenerationSettings;
	FChatCompletionGenerationSettings ChatCompletionGenerationSettings;

	static FCompletion ParseWebIUResponse(const FJsonObject&);
	static TArray<FChatCompletionWebUI> ParseChatWebUIResponse(const FJsonObject&);

	static FString ParseTranscriptionCompletion(const FJsonObject&);
	static FString ParseGeneratedImage(const FJsonObject&);
};
