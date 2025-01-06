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
	WebUIParser();
	WebUIParser(const FCompletionWebUiSettings&);
	WebUIParser(const FChatCompletionWebUiSettings&);

	WebUIParser(const FCompletionGenerationSettings&);
	WebUIParser(const FChatCompletionGenerationSettings&);
	
	~WebUIParser();


	FCompletionWebUiSettings webUiSettings;
	FChatCompletionWebUiSettings chatWebUiSettings;

	FCompletionGenerationSettings CompletionGenerationSettings;
	FChatCompletionGenerationSettings ChatCompletionGenerationSettings;
	


	FCompletion ParseCompletionsResponse(const FJsonObject&) const;

	FCompletion ParseWebIUResponse(const FJsonObject&);
	TArray<FChatCompletionWebUI> ParseChatWebUIResponse(const FJsonObject&);

	FString ParseTranscriptionCompletion(const FJsonObject&);
	FString ParseGeneratedImage(FJsonObject&);
};
