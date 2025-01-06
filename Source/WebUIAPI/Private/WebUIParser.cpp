#include "WebUIParser.h"
#include "Dom/JsonObject.h"


// Constructor
WebUIParser::WebUIParser(const FCompletionWebUiSettings& settings)
: webUiSettings(settings)
{
}

WebUIParser::WebUIParser(const FChatCompletionWebUiSettings& settings)
	: chatWebUiSettings(settings)
{
}

WebUIParser::WebUIParser(const FCompletionGenerationSettings& settings)
	: CompletionGenerationSettings(settings)
{
}

WebUIParser::WebUIParser(const FChatCompletionGenerationSettings& settings)
	: ChatCompletionGenerationSettings(settings)
{
}

//De-constructor
WebUIParser::~WebUIParser()
{
}

// parses a single Completion.

FCompletion WebUIParser::ParseWebIUResponse(const FJsonObject& json)
{
	FCompletion res = {};

	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField(FString("choices"));
	if (choices.IsEmpty())
	{
		res.text = TEXT("WebUI RESPONSE CHOICES ARE EMPTY");
		res.index = -1;
		return res;
	}
	
	TSharedPtr<FJsonValue> choice = choices[0];
	res.text = choice->AsObject()->GetStringField(TEXT("text"));
	res.index = choice->AsObject()->GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	
	return res;
}

TArray<FChatCompletionWebUI> WebUIParser::ParseChatWebUIResponse(const FJsonObject& json)
{
	//Should be similar to type in TArray
	typedef FChatCompletionWebUI ChatCompletion;
	
	TArray<ChatCompletion> res = {};

	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField(FString("choices"));
	if (choices.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("WebUI: Choices are empty!"))
		ChatCompletion response;
		response.finishReason = TEXT("WebUI RESPONSE CHOICES ARE EMPTY");
		response.index = -1;
		res.Add(response);
		return res;
	}

	for (TSharedPtr<FJsonValue> choice : choices)
	{
		ChatCompletion response;
		response.index = choice->AsObject()->GetIntegerField(TEXT("index"));
		response.finishReason = choice->AsObject()->GetStringField(TEXT("finish_reason"));
		auto messageObject = choice->AsObject()->GetField(TEXT("message"), EJson::Object);
		
		FChatMessage message;
		message.role = messageObject->AsObject()->GetStringField(TEXT("role"));
		message.content = messageObject->AsObject()->GetStringField(TEXT("content"));
		response.messages.Add(message);

		res.Add(response);
	}
	
	return res;
}

FString WebUIParser::ParseTranscriptionCompletion(const FJsonObject& json)
{
	return json.GetStringField(FString("text"));
}

// parses a single Generated Image.
FString WebUIParser::ParseGeneratedImage(FJsonObject& json)
{
	FString res = "";
	res = json.GetStringField(TEXT("url"));

	return res;
}
