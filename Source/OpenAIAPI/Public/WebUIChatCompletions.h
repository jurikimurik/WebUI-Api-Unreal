// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WebUIDefinitions.h"
#include "OpenAIDefinitions.h"
#include "HttpModule.h"
#include "WebUIChatCompletions.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiChatResponseRecievedPin, bool, Success, const FString&, errorMessage, const TArray<FChatCompletionWebUI>&, messages);

/**
 * 
 */
UCLASS()
class OPENAIAPI_API UWebUIChatCompletions : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UWebUIChatCompletions();
	~UWebUIChatCompletions();

	// Special setting that is being used for simple generation
	FChatCompletionGenerationSettings ChatSettings;

	//IP address with port number, where HTTP Request will be sent
	FString Address = "https://127.0.0.1:5000";

	UPROPERTY(BlueprintAssignable, Category="OpenAI")
	FOnWebUiChatResponseRecievedPin Finished;
	
private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "OpenAI")
	static UWebUIChatCompletions* OpenWebUIChatCompletions(FChatCompletionGenerationSettings chatSettings, FString Address);

	TSharedPtr<FJsonObject> BuildPayload();
	void CommitRequest(::FString, TSharedRef<IHttpRequest, ESPMode::ThreadSafe>, FString _payload);
	bool CheckResponse(FHttpResponsePtr Response, bool WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
	
};
