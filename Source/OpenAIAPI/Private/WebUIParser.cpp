#include "WebUIParser.h"
#include "OpenAIUtils.h"
#include "Dom/JsonObject.h"


// Constructor
WebUIParser::WebUIParser(const FCompletionSettings& settings)
	: completionSettings(settings)
{
}

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

WebUIParser::WebUIParser(const FChatSettings& settings)
	: chatSettings(settings)
{
}

WebUIParser::WebUIParser(const FSpeechSettings& settings)
	: speechSettings(settings)
{
}

//De-constructor
WebUIParser::~WebUIParser()
{
}

// parses a single Completion.
FCompletion WebUIParser::ParseCompletionsResponse(const FJsonObject& json) const
{
	FCompletion res = {};
	
	res.text = json.GetStringField(TEXT("text")) + completionSettings.injectRestartText;
	res.index = json.GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	
	return res;
}

// parses the response info
FCompletionInfo WebUIParser::ParseGPTCompletionInfo(const FJsonObject& json)
{
	FCompletionInfo res = {};

	res.id = json.GetStringField(FString("id"));
	res.object = json.GetStringField(FString("object"));
	res.created = FDateTime::FromUnixTimestamp(json.GetNumberField(FString("created")));
	res.model = json.GetStringField(FString("model"));

	return res;
}

// parses a single Generated messasge.
FChatCompletion WebUIParser::ParseChatCompletion(const FJsonObject& json)
{
	FChatCompletion res = {};

	FChatLog message;
	message.role = EOAChatRole::ASSISTANT;
	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField(FString("choices"));
	TSharedPtr<FJsonValue> choice = choices[0];
	TSharedPtr<FJsonObject> messageObject = choice->AsObject()->GetObjectField(FString("message"));
	message.content = messageObject->GetStringField(FString("content"));
	//res.index = json.GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	res.message = message;
	
	return res;
}

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

FSpeechCompletion WebUIParser::ParseSpeechCompletion(const FJsonObject&)
{
	/*
*Create speech
POST

https://api.openai.com/v1/audio/speech

Generates audio from the input text.

Request body
model
string
Required
One of the available TTS models: tts-1 or tts-1-hd

input
string
Required
The text to generate audio for. The maximum length is 4096 characters.

voice
string
Required
The voice to use when generating the audio. Supported voices are alloy, echo, fable, onyx, nova, and shimmer.

response_format
string
Optional
Defaults to mp3
The format to audio in. Supported formats are mp3, opus, aac, and flac.

speed
number
Optional
Defaults to 1
The speed of the generated audio. Select a value from 0.25 to 4.0. 1.0 is the default.

Returns
The audio file content.
 */

///	FString res = "";

	// Handle the received audio data
	//TArray<uint8> ReceivedData = Response->GetContent();
            
	// For demonstration purposes, write the data to a file on disk
	//FFileHelper::SaveArrayToFile(ReceivedData, *FPaths::ProjectSavedDir() / TEXT("ReceivedAudio.mp3"));

	return {};
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
