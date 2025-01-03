// Fill out your copyright notice in the Description page of Project Settings.


#include "WebUIChatCompletions.h"
#include "WebUIDefinitions.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "WebUIParser.h"


UWebUIChatCompletions::UWebUIChatCompletions()
{
}

UWebUIChatCompletions::~UWebUIChatCompletions()
{
}

UWebUIChatCompletions* UWebUIChatCompletions::OpenWebUIChatCompletions(FChatCompletionWebUiSettings ChatSettingsInput, FString Address)
{
	UWebUIChatCompletions* BPNode = NewObject<UWebUIChatCompletions>();
	BPNode->ChatSettings = ChatSettingsInput;
	BPNode->Address = Address;
	return BPNode;
}

void UWebUIChatCompletions::Activate()
{
	// NOTE: ApiKey was deleted because it was not really necessary to have it to connect to Oobabooga's WebUI. 
	// creating the http request
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	
	// set headers
	FString url = FString::Printf(TEXT("%s/v1/chat/completions"), *Address);
	HttpRequest->SetURL(url);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	//build payload
	TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());

	//Creating and loading messages array
	TArray <TSharedPtr<FJsonValue>> Messages;
	{
		for (auto message : ChatSettings.messages)
		{
			TSharedPtr<FJsonObject> messageObject = MakeShareable(new FJsonObject());
			messageObject->SetStringField("role", message.role);
			messageObject->SetStringField("content", message.content);
			TSharedRef<FJsonValueObject> StringValue = MakeShareable(new FJsonValueObject(messageObject));
			Messages.Add(StringValue);
		}
		
	}
	_payloadObject->SetArrayField("messages", Messages);
	
	
	_payloadObject->SetStringField(TEXT("mode"), ChatSettings.mode);
	_payloadObject->SetStringField(TEXT("instruction_template"), ChatSettings.instructionTemplate);
		

	// convert payload to string
	FString _payload;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
	FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

	// commit request
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(_payload);

	if (HttpRequest->ProcessRequest())
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UWebUIChatCompletions::OnResponse);
	}
	else
	{
		Finished2.Broadcast(false, ("Error sending request"),{});
	}
}

void UWebUIChatCompletions::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	// print response as debug message
	if (!WasSuccessful)
	{
		if (!Response)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error processing request. No response."));
			Finished2.Broadcast(false,  ("Error processing request. No response."), {});
			return;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Error processing request. \n%s \n%s"), *Response->GetContentAsString(), *Response->GetURL());
		if (Finished2.IsBound())
		{
			Finished2.Broadcast(false, *Response->GetContentAsString(), {});
		}

		return;
	}

	TSharedPtr<FJsonObject> responseObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(reader, responseObject))
	{
		bool err = responseObject->HasField(FString("error"));

		if (err)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished2.Broadcast(false, TEXT("Api error"), {});
			return;
		}

		
		WebUIParser parser(ChatSettings);
			//Special method in Parses was created
		TArray<FChatCompletionWebUI> _out = parser.ParseChatWebUIResponse(*responseObject);

		if (_out.IsEmpty())
		{
			Finished2.Broadcast(false, TEXT("Response text is empty."), TArray<FChatCompletionWebUI>());
		} else
		{
			Finished2.Broadcast(true, "", _out);	
		}
	}
}

