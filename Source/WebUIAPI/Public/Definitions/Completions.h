#pragma once

#include "Completions.generated.h"

// COMPLETIONS ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Basic completion
USTRUCT(BlueprintType)
struct FCompletion
{
	GENERATED_USTRUCT_BODY()

	// Similar to WebUI's response.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString Text = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	int32 Index = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString FinishReason = "";
};

// Basic settings of one simple completion that is used for WebUI
USTRUCT(BlueprintType)
struct FCompletionWebUiSettings
{
	GENERATED_USTRUCT_BODY()

	// Text that should be applied before prompt
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString StartSequence = "";

	// Prompt that is used for generation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString Prompt = "";

	// Text that should be applied after the prompt
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString EndSequence = "";
	
	/** The maximum number of tokens to generate. Requests can use up to 2048 tokens shared between prompt and completion. (One token is roughly 4 characters for normal English text) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	int32 MaxTokens = 250;

	/** What sampling temperature to use. Higher values means the model will take more risks. Try 0.9 for more creative applications, and 0 (argmax sampling) for ones with a well-defined answer. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	float Temperature = 0.7f;

	/** An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	float TopP = 1.0f;

	/** Random seed that is used for random answer generation. Same seed each time will generate the same response.**/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	float Seed = 0;
};
