﻿#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WebUIDefinitions.h"
#include "HttpModule.h"

#include "WebUILoadModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiLoadModelResponseRecievedPin, bool, Success, const FString&, errorMessage, const FString, message);

UCLASS()
class WEBUIAPI_API UWebUILoadModel : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UWebUILoadModel();
	virtual ~UWebUILoadModel() override;

	// Special setting that is being used for simple generation
	FTransformerSettings ModelSettings;

	//IP address with port number, where HTTP Request will be sent
	FString Address = "https://127.0.0.1:5000";

	UPROPERTY(BlueprintAssignable, Category="WebUI")
	FOnWebUiLoadModelResponseRecievedPin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "WebUI")
	static UWebUILoadModel* LoadWebUIModel(FTransformerSettings modelSettings, FString Address);
	
	TSharedPtr<FJsonObject> BuildPayload() const;
	void CommitRequest(const ::FString&, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&, const FString& _payload);
	bool CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
	
};
