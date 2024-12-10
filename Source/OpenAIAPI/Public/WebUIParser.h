#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "OpenAIDefinitions.h"
#include "WebUIDefinitions.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

/**
 * 
 */
class OPENAIAPI_API WebUIParser
{
public:
	WebUIParser();
	WebUIParser(const FCompletionSettings&);
	WebUIParser(const FCompletionWebUiSettings&);
	WebUIParser(const FChatSettings&);
	WebUIParser(const FSpeechSettings&);
	~WebUIParser();

	FCompletionSettings completionSettings;
	FCompletionWebUiSettings webUiSettings;
	
	FChatSettings chatSettings;
	FSpeechSettings speechSettings;

	FCompletion ParseCompletionsResponse(const FJsonObject&) const;
	FCompletionInfo ParseGPTCompletionInfo(const FJsonObject&);
	FChatCompletion ParseChatCompletion(const FJsonObject&);
	FCompletion ParseWebIUResponse(const FJsonObject&);
	FSpeechCompletion ParseSpeechCompletion (const FJsonObject&);
	FString ParseTranscriptionCompletion(const FJsonObject&);
	FString ParseGeneratedImage(FJsonObject&);
};
