#include "Functions/WebUIUnloadModel.h"

#include "WebUIParser.h"
#include "Http.h"
#include "WebUIUtils.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

UIWebUIUnloadModel::UIWebUIUnloadModel()
{
}

UIWebUIUnloadModel::~UIWebUIUnloadModel()
{
}

UIWebUIUnloadModel* UIWebUIUnloadModel::WebUI_UnloadModel(FString Address)
{
	UIWebUIUnloadModel* BPNode = NewObject<UIWebUIUnloadModel>();
	BPNode->Address = Address;
	return BPNode;
}

TSharedPtr<FJsonObject> UIWebUIUnloadModel::BuildPayload() const
{
	//build payload
	TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());

	return _payloadObject;
}

void UIWebUIUnloadModel::CommitRequest(const FString& Verb, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& HttpRequest, const FString& _payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Payload to send: %s"), *_payload);
	
	// commit request
	HttpRequest->SetVerb(Verb);
	HttpRequest->SetContentAsString(_payload);
	

	if (HttpRequest->ProcessRequest())
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UIWebUIUnloadModel::OnResponse);
	}
	else
	{
		Finished.Broadcast(false, ("Error sending request"),{});
	}
}

bool UIWebUIUnloadModel::CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const
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

void UIWebUIUnloadModel::Activate()
{
	// NOTE: ApiKey was deleted because it was not really necessary to have it to connect to Oobabooga's WebUI. 

	// creating the http request
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	
	// set headers
	FString url = FString::Printf(TEXT("%s/v1/internal/model/unload"), *Address);
	HttpRequest->SetURL(url);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	auto _payloadObject = BuildPayload();
		

	// convert payload to string
	FString _payload;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
	FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

	CommitRequest("POST", HttpRequest,_payload);
}

void UIWebUIUnloadModel::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const
{
	if (!CheckResponse(Response, WasSuccessful)) return;

	TSharedPtr<FJsonObject> responseObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	
	//Special method in Parses was created
	FString _out = (Response->GetContentAsString());

	if (_out.IsEmpty())
	{
		Finished.Broadcast(false, TEXT("Response text is empty."), _out);
	} else
	{
		Finished.Broadcast(true, "", _out);	
	}
}


