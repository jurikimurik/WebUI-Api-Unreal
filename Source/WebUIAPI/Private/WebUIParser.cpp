#include "WebUIParser.h"
#include "Dom/JsonObject.h"

FJsonObject WebUIParser::GetJsonObject() const
{
	return JsonObject;
}

void WebUIParser::SetJsonObject(const FJsonObject& JSONObject)
{
	this->JsonObject = JSONObject;
}


FJsonObject WebUIParser::CheckAndGet(const FJsonObject& jsonToCheck) const
{
	//If JSON is empty
	if (jsonToCheck.Values.IsEmpty())
		//Use JSON that is inside of this class instead
		return GetJsonObject();
	else
		//Use this exactly this JSON
		return jsonToCheck;
}

FJsonObject WebUIParser::CheckSetAndGet(const FJsonObject& JSONToCheck)
{
	//If JSON is empty
	if (JSONToCheck.Values.IsEmpty())
		//Use JSON that is inside of this class instead
			return GetJsonObject();
	else
		//Update
			SetJsonObject(JSONToCheck);
		//Use this exactly this JSON
			return GetJsonObject();
}

FCompletion WebUIParser::ParseWebUICompletionResponse(const FJsonObject& JSONToParse)
{
	FJsonObject json = CheckSetAndGet(JSONToParse);

	FCompletion res = {};

	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField(FString("choices"));
	if (choices.IsEmpty())
	{
		res.Text = TEXT("WebUI RESPONSE CHOICES ARE EMPTY");
		res.Index = -1;
		return res;
	}
	
	TSharedPtr<FJsonValue> choice = choices[0];
	res.Text = choice->AsObject()->GetStringField(TEXT("text"));
	res.Index = choice->AsObject()->GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.FinishReason);
	
	return res;
}

TArray<FChatCompletionWebUI> WebUIParser::ParseWebUIChatCompletionResponse(const FJsonObject& jsonToParse)
{
	//Should be similar to type in TArray
	typedef FChatCompletionWebUI ChatCompletion;

	FJsonObject json = CheckSetAndGet(jsonToParse);
	
	TArray<ChatCompletion> res = {};

	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField(FString("choices"));
	if (choices.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("WebUI: Choices are empty!"))
		ChatCompletion response;
		response.FinishReason = TEXT("WebUI RESPONSE CHOICES ARE EMPTY");
		response.Index = -1;
		res.Add(response);
		return res;
	}

	for (TSharedPtr<FJsonValue> choice : choices)
	{
		ChatCompletion response;
		response.Index = choice->AsObject()->GetIntegerField(TEXT("index"));
		response.FinishReason = choice->AsObject()->GetStringField(TEXT("finish_reason"));
		auto messageObject = choice->AsObject()->GetField(TEXT("message"), EJson::Object);
		
		FChatMessage message;
		message.Role = messageObject->AsObject()->GetStringField(TEXT("role"));
		message.Content = messageObject->AsObject()->GetStringField(TEXT("content"));
		response.Messages.Add(message);

		res.Add(response);
	}
	
	return res;
}

FString WebUIParser::ParseTranscriptionCompletion(const FJsonObject& jsonToParse)
{
	return CheckSetAndGet(jsonToParse).GetStringField(FString("text"));
}

FString WebUIParser::ParseGeneratedImage(const FJsonObject& jsonToParse) 
{
	FString res = "";
	res = CheckSetAndGet(jsonToParse).GetStringField(TEXT("url"));

	return res;
}

TArray<FString> WebUIParser::ParseWebUIModelList(const FJsonObject& jsonToParse)
{
	TArray<FString> models;
	auto jsonModels = CheckSetAndGet(jsonToParse).GetArrayField(TEXT("model_names"));
	for (auto jsonModelJson : jsonModels)
	{
		models.Add(jsonModelJson->AsString());
	}
	return models;
}
