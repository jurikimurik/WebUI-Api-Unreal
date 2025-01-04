// Fill out your copyright notice in the Description page of Project Settings.


#include "WebUICallCompletions.h"
#include "OpenAIUtils.h"
#include "WebUIParser.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "OpenAIParser.h"

UWebUICallCompletions::UWebUICallCompletions()
{
}

UWebUICallCompletions::~UWebUICallCompletions()
{
}

UWebUICallCompletions* UWebUICallCompletions::OpenWebUICallCompletions(FCompletionWebUiSettings ChatSettingsInput, FString Address)
{
	UWebUICallCompletions* BPNode = NewObject<UWebUICallCompletions>();
	BPNode->ChatSettings = ChatSettingsInput;
	BPNode->Address = Address;
	return BPNode;
}

TSharedPtr<FJsonObject> UWebUICallCompletions::BuildPayload()
{
	//build payload
	TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());

	// including the final prompt
	FString finalPrompt = FString::Printf(TEXT("%s%s%s"), *ChatSettings.startSequence, *ChatSettings.prompt, *ChatSettings.endSequence);
	_payloadObject->SetStringField(TEXT("prompt"), finalPrompt);

	// including other parameters
	_payloadObject->SetNumberField(TEXT("max_tokens"), ChatSettings.maxTokens);
	_payloadObject->SetNumberField(TEXT("temperature"), ChatSettings.temperature);
	_payloadObject->SetNumberField(TEXT("top_p"), ChatSettings.topP);
	_payloadObject->SetNumberField(TEXT("seed"), ChatSettings.seed);

	return _payloadObject;
}

void UWebUICallCompletions::CommitRequest(FString Verb, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, FString _payload)
{
	// commit request
	HttpRequest->SetVerb(Verb);
	HttpRequest->SetContentAsString(_payload);

	if (HttpRequest->ProcessRequest())
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UWebUICallCompletions::OnResponse);
	}
	else
	{
		Finished.Broadcast(false, ("Error sending request"),{});
	}
}

bool UWebUICallCompletions::CheckResponse(FHttpResponsePtr Response, bool WasSuccessful) const
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

void UWebUICallCompletions::Activate()
{
	// NOTE: ApiKey was deleted because it was not really necessary to have it to connect to Oobabooga's WebUI. 

	// creating the http request
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	
	// set headers
	FString url = FString::Printf(TEXT("%s/v1/completions"), *Address);
	HttpRequest->SetURL(url);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	auto _payloadObject = BuildPayload();
		

	// convert payload to string
	FString _payload;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
	FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

	CommitRequest("POST", HttpRequest,_payload);
}

void UWebUICallCompletions::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	if (!CheckResponse(Response, WasSuccessful)) return;

	TSharedPtr<FJsonObject> responseObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(reader, responseObject))
	{
		bool err = responseObject->HasField("error");

		if (err)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished.Broadcast(false, TEXT("Api error"), {});
			return;
		}

		
		WebUIParser parser(ChatSettings);
			//Special method in Parses was created
		FCompletion _out = parser.ParseWebIUResponse(*responseObject);

		if (_out.text.IsEmpty())
		{
			Finished.Broadcast(false, TEXT("Response text is empty."), _out);
		} else
		{
			Finished.Broadcast(true, "", _out);	
		}
	}
}

