#include "Functions/WebUIGetModels.h"
#include "WebUIParser.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

UWebUIGetModels::UWebUIGetModels()
{
}

UWebUIGetModels::~UWebUIGetModels()
{
}

UWebUIGetModels* UWebUIGetModels::GetWebUIModels(FString Address)
{
	UWebUIGetModels* BPNode = NewObject<UWebUIGetModels>();
	BPNode->Address = Address;
	return BPNode;
}

TSharedPtr<FJsonObject> UWebUIGetModels::BuildPayload() const
{
	//build payload
	TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());

	return _payloadObject;
}

void UWebUIGetModels::CommitRequest(const FString& Verb, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& HttpRequest, const FString& _payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Payload to send: %s"), *_payload);
	
	// commit request
	HttpRequest->SetVerb(Verb);
	HttpRequest->SetContentAsString(_payload);
	

	if (HttpRequest->ProcessRequest())
	{
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UWebUIGetModels::OnResponse);
	}
	else
	{
		Finished.Broadcast(false, ("Error sending request"),{});
	}
}

bool UWebUIGetModels::CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const
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

void UWebUIGetModels::Activate()
{
	// NOTE: ApiKey was deleted because it was not really necessary to have it to connect to Oobabooga's WebUI. 

	// creating the http request
	auto HttpRequest = FHttpModule::Get().CreateRequest();
	
	// set headers
	FString url = FString::Printf(TEXT("%s/v1/internal/model/list"), *Address);
	HttpRequest->SetURL(url);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	auto _payloadObject = BuildPayload();
		

	// convert payload to string
	FString _payload;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
	FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

	CommitRequest("GET", HttpRequest,TEXT(""));
}

void UWebUIGetModels::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const
{
	if (!CheckResponse(Response, WasSuccessful)) return;

	TSharedPtr<FJsonObject> responseObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	
	if (FJsonSerializer::Deserialize(reader, responseObject))
	{
		if (responseObject->HasField(TEXT("error")))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished.Broadcast(false, TEXT("Api error"), {});
			return;
		}

		
		//Special method in Parses was created
		WebUIParser parser(*responseObject);
		TArray<FString> _out = parser.ParseWebUIModelList();

		if (_out.IsEmpty())
		{
			Finished.Broadcast(false, TEXT("Response texts are empty."), _out);
		} else
		{
			Finished.Broadcast(true, "", _out);	
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot deserialize object"));
	}
}


