#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "./WebUIDefinitions.h"
#include "HttpModule.h"

#include "WebUILoadModel.generated.h"



/**
 * Make an HTTP request to WebUI to load desired model.  
 */
UCLASS()
class WEBUIAPI_API UWebUILoadModel : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UWebUILoadModel();
	virtual ~UWebUILoadModel() override;

	// Special setting that is being used for simple generation
	FTransformerSettings TransformerModelSettings;

	//IP address with port number, where HTTP Request will be sent
	FString Address = TEXT("https://127.0.0.1:5000");

	UPROPERTY(BlueprintAssignable, Category="WebUI")
	FOnWebUiSimpleResponsePin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "WebUI")
	static UWebUILoadModel* WebUI_LoadModel(FTransformerSettings modelSettings, FString Address);
	
	TSharedPtr<FJsonObject> BuildPayload() const;
	void CommitRequest(const ::FString&, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&, const FString& _payload);
	bool CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
	
};
