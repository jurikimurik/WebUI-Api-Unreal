// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "./WebUIDefinitions.h"
#include "HttpModule.h"
#include "WebUICompletion.generated.h"



/**
 * 
 */
UCLASS()
class WEBUIAPI_API UWebUICompletion : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UWebUICompletion();
	virtual ~UWebUICompletion() override;

	// Special setting that is being used for simple generation
	FCompletionGenerationSettings ChatSettings;

	//IP address with port number, where HTTP Request will be sent
	FString Address = "https://127.0.0.1:5000";

	UPROPERTY(BlueprintAssignable, Category="WebUI")
	FOnWebUiCompletionResponseRecievedPin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "WebUI")
	static UWebUICompletion* WebUI_Completion(FCompletionGenerationSettings chatSettings, FString Address);
	
	TSharedPtr<FJsonObject> BuildPayload() const;
	void CommitRequest(const ::FString&, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&, const FString& _payload);
	bool CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
	
};
