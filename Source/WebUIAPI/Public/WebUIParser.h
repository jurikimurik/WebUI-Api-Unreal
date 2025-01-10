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
protected:
	//Internal, temporal JSON object
	FJsonObject JsonObject;

	
public:
	WebUIParser() = default;
	WebUIParser(const FJsonObject& Json) : JsonObject(Json) {}
	virtual ~WebUIParser() = default;

	//Getters and setters --------------------------------------------------------------------------------
	FJsonObject GetJsonObject() const;
	void SetJsonObject(const FJsonObject& JSONObject);

	//Check, update JSON and return updated JSON
	FJsonObject CheckSetAndGet(const FJsonObject& JSONToCheck);

	//Only check and return JSONToParse or iternal JSON
	FJsonObject CheckAndGet(const FJsonObject& JSONToParse) const;

	// Web UI Parsing Methods ---------------------------------------------------------------------------

	//Parsing JSON to Completion
	FCompletion ParseWebUICompletionResponse(const FJsonObject& JSONToParse = FJsonObject());

	//Parsing JSON to ChatCompletion
	TArray<FChatCompletionWebUI> ParseWebUIChatCompletionResponse(const FJsonObject& = FJsonObject());

	//Parsing JSON to Model List
	TArray<FString> ParseWebUIModelList(const FJsonObject& = FJsonObject());

	// Open AI Parsing Methods --------------------------------------------------------------------------
	
	FString ParseTranscriptionCompletion(const FJsonObject& = FJsonObject());
	
	FString ParseGeneratedImage(const FJsonObject& = FJsonObject());
	
};
