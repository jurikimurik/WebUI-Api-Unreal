#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "./WebUIDefinitions.h"
#include "HttpModule.h"

#include "WebUIStopGeneration.generated.h"



// Function sends HTTP packet to WebUI on address to stop generation.
UCLASS()
class WEBUIAPI_API UWebUIStopGeneration : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UWebUIStopGeneration();
	virtual ~UWebUIStopGeneration() override;

	// Special setting that is being used for simple generation
	FCompletionGenerationSettings ChatSettings;

	//IP address with port number, where HTTP Request will be sent
	FString Address = "https://127.0.0.1:5000";

	UPROPERTY(BlueprintAssignable, Category="WebUI")
	FOnWebUiSimpleResponsePin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "WebUI")
	static UWebUIStopGeneration* StopWebUIGeneration(FString Address);
	
	TSharedPtr<FJsonObject> BuildPayload() const;
	void CommitRequest(const ::FString&, const TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&, const FString& _payload);
	bool CheckResponse(const FHttpResponsePtr& Response, const bool& WasSuccessful) const;

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful) const;
};
