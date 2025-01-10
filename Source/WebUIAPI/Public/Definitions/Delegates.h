#pragma once

#include "Chat.h"
#include "Completions.h"

#include "Delegates.generated.h"

// DELEGATES -------------------------------------------------------------------------------------------------------------------------------------------------------------------

// To retrieve FString
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiSimpleResponsePin, bool, Success, const FString&, errorMessage, const FString, message);

// To retrieve TArray<FString>
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiArraySimpleResponsePin, bool, Success, const FString&, errorMessage, const TArray<FString>&, message);

// To retrieve FChatCompletionWebUI
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiChatCompletionResponseRecievedPin, bool, Success, const FString&, errorMessage, const TArray<FChatCompletionWebUI>&, messages);

// To retrieve FCompletion
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiCompletionResponseRecievedPin, bool, Success, const FString&, errorMessage, const FCompletion, message);