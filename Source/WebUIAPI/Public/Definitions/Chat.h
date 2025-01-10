#pragma once

#include "Chat.generated.h"

// CHAT ---------------------------------------------------------------------------------------------------------------------------------------------------------------

// One separate message
USTRUCT(BlueprintType)
struct FChatMessage
{
	GENERATED_USTRUCT_BODY();

	//Role of this message
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString Role;

	//Content of this message
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString Content;
};

// Structure that have a few of FChatMessage inside of it
USTRUCT(BlueprintType)
struct FChatCompletionWebUI
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	int32 Index = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString FinishReason = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FChatMessage> Messages;
};

// Basic settings of one simple chat completion that is used for WebUI
USTRUCT(BlueprintType)
struct FChatCompletionWebUiSettings
{
	GENERATED_USTRUCT_BODY()

	// <Role -> Content>
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FChatMessage> Messages;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString Mode = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString InstructionTemplate = "";
};
