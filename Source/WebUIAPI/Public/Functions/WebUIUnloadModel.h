﻿#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "./WebUIDefinitions.h"
#include "HttpModule.h"

#include "WebUIUnloadModel.generated.h"



/**
 * Make an HTTP request to WebUI for unloading AI model.
 */
UCLASS()
class WEBUIAPI_API UIWebUIUnloadModel : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UIWebUIUnloadModel();
	virtual ~UIWebUIUnloadModel() override;
	
	//IP address with port number, where HTTP Request will be sent
	FString Address = TEXT("https://127.0.0.1:5000");

	UPROPERTY(BlueprintAssignable, Category="WebUI")
	FOnWebUiSimpleResponsePin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "WebUI")
	static UIWebUIUnloadModel* WebUI_UnloadModel(FString Address);
	
	TSharedPtr<FJsonObject> BuildPayload() const;
	void CommitRequest(const ::FString&, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&, const FString& _payload);
	bool CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
	
};
