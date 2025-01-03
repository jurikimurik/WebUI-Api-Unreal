#pragma once

#include "CoreMinimal.h"
#include "WebUIDefinitions.generated.h"


// Basic settings of one simple completion that is used for WebUI
USTRUCT(BlueprintType)
struct FCompletionWebUiSettings
{
	GENERATED_USTRUCT_BODY()

	// Text that should be applied before prompt
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString startSequence = "";

	// Prompt that is used for generation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString prompt = "";

	// Text that should be applied after the prompt
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString endSequence = "";
	
	/** The maximum number of tokens to generate. Requests can use up to 2048 tokens shared between prompt and completion. (One token is roughly 4 characters for normal English text) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	int32 maxTokens = 250;

	/** What sampling temperature to use. Higher values means the model will take more risks. Try 0.9 for more creative applications, and 0 (argmax sampling) for ones with a well-defined answer. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	float temperature = 0.7f;

	/** An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	float topP = 1.0f;

	/** Random seed that is used for random answer generation. Same seed each time will generate the same response.**/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	float seed = 0;
};



USTRUCT(BlueprintType)
struct FChatMessage
{
	GENERATED_USTRUCT_BODY()

	//Role of this message
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString role;

	//Content of this message
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString content;
};

USTRUCT(BlueprintType)
struct FChatCompletionWebUI
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	int32 index = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString finishReason = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	TArray<FChatMessage> messages;
};

// Basic settings of one simple chat completion that is used for WebUI
USTRUCT(BlueprintType)
struct FChatCompletionWebUiSettings
{
	GENERATED_USTRUCT_BODY()

	// <Role -> Content>
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	TArray<FChatMessage> messages;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString mode = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString instructionTemplate = "";
};