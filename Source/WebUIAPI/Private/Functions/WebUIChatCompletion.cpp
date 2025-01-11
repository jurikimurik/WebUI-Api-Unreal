// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/WebUIChatCompletion.h"
#include "WebUIDefinitions.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "WebUIParser.h"
#include "WebUIUtils.h"


UWebUIChatCompletion::UWebUIChatCompletion()
{
}

UWebUIChatCompletion::~UWebUIChatCompletion()
{
}

UWebUIChatCompletion* UWebUIChatCompletion::WebUI_ChatCompletion(FChatCompletionGenerationSettings ChatSettingsInput, FString Address)
{
	UWebUIChatCompletion* BPNode = NewObject<UWebUIChatCompletion>();
	BPNode->ChatCompletionSettings = ChatSettingsInput;
	BPNode->Address = Address;
	return BPNode;
}

TSharedPtr<FJsonObject> UWebUIChatCompletion::BuildPayload()
{
	//build payload
	TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());

	//Creating and loading messages array
	UWebUIUtils::IncludeChatGenerationSettings(_payloadObject, ChatCompletionSettings);

	return _payloadObject;
}

void UWebUIChatCompletion::CommitRequest(FString Verb, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, FString _payload)
{
	// commit request
	HttpRequest->SetVerb(Verb);
	HttpRequest->SetContentAsString(_payload);

	if (HttpRequest->ProcessRequest())
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UWebUIChatCompletion::OnResponse);
	}
	else
	{
		Finished.Broadcast(false, ("Error sending request"),{});
	}
}

void UWebUIChatCompletion::Activate()
{
	// NOTE: ApiKey was deleted because it was not really necessary to have it to connect to Oobabooga's WebUI.
	
	// creating the http request
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	
	// Set URL and Headers
	FString url = FString::Printf(TEXT("%s/v1/chat/completions"), *Address);
	HttpRequest->SetURL(url);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	auto _payloadObject = BuildPayload();

	// Convert payload to String
	FString _payload;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
	FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

	CommitRequest("POST", HttpRequest,_payload);
}

bool UWebUIChatCompletion::CheckResponse(FHttpResponsePtr Response, bool WasSuccessful) const
{
	if (!WasSuccessful)
	{
		if (!Response)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error processing request. No response."));
			Finished.Broadcast(false,  ("Error processing request. No response."), {});
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Error processing request. \n%s \n%s"), *Response->GetContentAsString(), *Response->GetURL());
			if (Finished.IsBound())
			{
				Finished.Broadcast(false, *Response->GetContentAsString(), {});
			}
		}
		return false;
	}
	return true;
}

void UWebUIChatCompletion::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const
{
	if (!CheckResponse(Response, WasSuccessful)) return;

	TSharedPtr<FJsonObject> responseObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(reader, responseObject))
	{
		bool err = responseObject->HasField(FString("error"));

		if (err)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished.Broadcast(false, TEXT("Api error"), {});
			return;
		}

		
		WebUIParser parser(*responseObject);
			//Special method in Parses was created
		TArray<FChatCompletionWebUI> _out = parser.ParseWebUIChatCompletionResponse();

		if (_out.IsEmpty())
		{
			Finished.Broadcast(false, TEXT("Response text is empty."), TArray<FChatCompletionWebUI>());
		} else
		{
			Finished.Broadcast(true, "", _out);	
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot deserialize object"));
		Finished.Broadcast(false, TEXT("Cannot deserialize object"), {});
	}
}

