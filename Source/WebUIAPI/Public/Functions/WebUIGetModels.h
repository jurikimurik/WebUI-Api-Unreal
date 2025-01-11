#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "./WebUIDefinitions.h"
#include "HttpModule.h"

#include "WebUIGetModels.generated.h"



/**
 * Make an HTTP request to WebUI for retrieving all models that can be loaded.
 */
UCLASS()
class WEBUIAPI_API UWebUIGetModels : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UWebUIGetModels();
	virtual ~UWebUIGetModels();

	//IP address with port number, where HTTP Request will be sent
	FString Address = "https://127.0.0.1:5000";

	UPROPERTY(BlueprintAssignable, Category="WebUI")
	FOnWebUiArraySimpleResponsePin Finished;
	
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "WebUI")
	static UWebUIGetModels* WebUI_GetModels(FString Address);
	
	TSharedPtr<FJsonObject> BuildPayload() const;
	void CommitRequest(const ::FString&, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&, const FString& _payload);
	bool CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
	
};
