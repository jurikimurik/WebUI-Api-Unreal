// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OpenAIDefinitions.h"
#include "HttpModule.h"
#include "WebUICallCompletions.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiResponseRecievedPin, const FCompletion, message, const FString&, errorMessage, bool, Success);

/**
 * 
 */
UCLASS()
class OPENAIAPI_API UWebUICallCompletions : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UWebUICallCompletions();
	~UWebUICallCompletions();

	// Special setting that is being used for simple generation
	FCompletionWebUiSettings ChatSettings;

	//IP address with port number, where HTTP Request will be sent
	FString Address = "https://127.0.0.1:5000";

	UPROPERTY(BlueprintAssignable, Category="OpenAI")
	FOnWebUiResponseRecievedPin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "OpenAI")
	static UWebUICallCompletions* OpenWebUICallCompletions(FCompletionWebUiSettings chatSettings, FString Address);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
	
};
