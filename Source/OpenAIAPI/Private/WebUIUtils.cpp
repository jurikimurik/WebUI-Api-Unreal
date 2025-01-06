#include "WebUIUtils.h"

namespace JSONUtils
{
	//Template method for checking and setting JSON parameter. Using "SetNumberField" by default.
	template <class T> void CheckAndSet(TSharedPtr<FJsonObject> Shared, const T& Value)
	{
		if (Value)
		{
			Shared->SetNumberField(Value.JSONParameterName, Value.Value);
		}
	}

	template<>
	void CheckAndSet(TSharedPtr<FJsonObject> Shared, const FBasicJSONSettingBool& boolValue)
	{
		if (boolValue)
		{
			Shared->SetBoolField(boolValue.JSONParameterName, boolValue.Value);
		}
	}

	template<>
	void CheckAndSet(TSharedPtr<FJsonObject> Shared, const FBasicJSONSettingString& stringValue)
	{
		if (stringValue)
		{
			Shared->SetStringField(stringValue.JSONParameterName, stringValue.Value);
		}
	}

	template<>
	void CheckAndSet(TSharedPtr<FJsonObject> Shared, const FBasicJSONSettingStringArray& stringArrayValue)
	{
		if (stringArrayValue)
		{
			TArray <TSharedPtr<FJsonValue>> strings;
			for (const FString& valueStr : stringArrayValue.Value)
			{
				TSharedPtr<FJsonValueString> jsonStr = MakeShareable(new FJsonValueString(valueStr));
				strings.Add(jsonStr);
			}
			Shared->SetArrayField(stringArrayValue.JSONParameterName, strings);
		}
	}
}


void UWebUIUtils::IncludeBasicGenerationSettings(TSharedPtr<FJsonObject> Shared, const FBasicGenerationSettings& Basics)
{
	using namespace JSONUtils;
	
	//Array<String>
		// Optional Arguments
		CheckAndSet(Shared, Basics.Stop);
		CheckAndSet(Shared, Basics.SamplerPriority);

	//Booleans
	CheckAndSet(Shared, Basics.AddBosToken);
	CheckAndSet(Shared, Basics.AutoMaxNewTokens);
	CheckAndSet(Shared, Basics.BanEosToken);
	CheckAndSet(Shared, Basics.DoSample);
	CheckAndSet(Shared, Basics.DynamicTemperature);
	CheckAndSet(Shared, Basics.SkipSpecialTokens);
	CheckAndSet(Shared, Basics.TemperatureLast);
		//Optional Arguments
		CheckAndSet(Shared, Basics.Stream);

	//Integers
	CheckAndSet(Shared, Basics.MaxTokensSecond);
	CheckAndSet(Shared, Basics.MirostatMode);
	CheckAndSet(Shared, Basics.NoRepeatNgramSize);
	CheckAndSet(Shared, Basics.PromptLookupNumTokens);
	CheckAndSet(Shared, Basics.RepetitionPenaltyRange);
	CheckAndSet(Shared, Basics.Seed);
	CheckAndSet(Shared, Basics.TopK);
	CheckAndSet(Shared, Basics.TruncationLength);
		//Optionals
		CheckAndSet(Shared, Basics.MaxTokens);
		CheckAndSet(Shared, Basics.N);
		
	//Numbers
	CheckAndSet(Shared, Basics.DynaTempExponent);
	CheckAndSet(Shared, Basics.DynaTempHigh);
	CheckAndSet(Shared, Basics.DynaTempLow);
	CheckAndSet(Shared, Basics.EncoderRepetitionPenalty);
	CheckAndSet(Shared, Basics.EpsilonCutoff);
	CheckAndSet(Shared, Basics.EtaCutoff);
	CheckAndSet(Shared, Basics.GuidanceScale);
	CheckAndSet(Shared, Basics.MinP);
	CheckAndSet(Shared, Basics.MirostatEta);
	CheckAndSet(Shared, Basics.MirostatTau);
	CheckAndSet(Shared, Basics.PenaltyAlpha);
	CheckAndSet(Shared, Basics.RepetitionPenalty);
	CheckAndSet(Shared, Basics.SmoothingCurve);
	CheckAndSet(Shared, Basics.SmoothingFactor);
	CheckAndSet(Shared, Basics.Tfs);
	CheckAndSet(Shared, Basics.TopA);
	CheckAndSet(Shared, Basics.TypicalP);
	
		//Optional
		CheckAndSet(Shared, Basics.FrequencyPenalty);
		CheckAndSet(Shared, Basics.PresencePenalty);
		CheckAndSet(Shared, Basics.Temperature);
		CheckAndSet(Shared, Basics.TopP);
		
	//Strings
	CheckAndSet(Shared, Basics.CustomTokenBans);
	CheckAndSet(Shared, Basics.GrammarString);
	CheckAndSet(Shared, Basics.NegativePrompt);
		//Optionals
		CheckAndSet(Shared, Basics.Model);
		CheckAndSet(Shared, Basics.Preset);
		CheckAndSet(Shared, Basics.User);
		

	//Custom JSON Parameters
	for (const FCustomJSONParameter& param : Basics.CustomJSONParameters)
	{
		//Write to JSON will depend on type of the parameter.
		switch (param.Type)
		{
		case JSONTypeParameter::Number:
			
			if (param.JsonValue.IsNumeric())
			{
				Shared->SetNumberField(param.JsonName, FCString::Atof(*param.JsonValue));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Trying to pass not-numeric value as numeric in JSON request: %s"), *param.JsonValue);
			}
			break;
			
		case JSONTypeParameter::Integer:
			
			if (param.JsonValue.IsNumeric())
			{
				Shared->SetNumberField(param.JsonName, FCString::Atoi(*param.JsonValue));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Trying to pass not-numeric value as numeric in JSON request: %s"), *param.JsonValue);
			}
			break;
			
		case JSONTypeParameter::String:
			Shared->SetStringField(param.JsonName, param.JsonValue);
			break;
		}
	}

	//Objects + Optional
	// TODO: LogitBias
}

void UWebUIUtils::IncludeCompletionGenerationSettings(TSharedPtr<FJsonObject> Shared,
	const FCompletionGenerationSettings& CompletionSettings)
{
	using namespace JSONUtils;
	IncludeBasicGenerationSettings(Shared, CompletionSettings.Basics);

	

	//Booleans + Optional
	CheckAndSet(Shared, CompletionSettings.Echo);
	
	//Integers + Optionals
	CheckAndSet(Shared, CompletionSettings.BestOf);
	CheckAndSet(Shared, CompletionSettings.LogProbs);
	
	//Strings
	CheckAndSet(Shared, CompletionSettings.prompt);
		//Optionals
		CheckAndSet(Shared, CompletionSettings.Suffix);
}

void UWebUIUtils::IncludeChatGenerationSettings(TSharedPtr<FJsonObject> Shared,
	const FChatCompletionGenerationSettings& ChatSettings)
{
	using namespace JSONUtils;
	IncludeBasicGenerationSettings(Shared, ChatSettings.Basics);
	
	
	//Array<Object>
	TArray <TSharedPtr<FJsonValue>> Messages;
	{
		for (auto message : ChatSettings.Messages)
		{
			TSharedPtr<FJsonObject> messageObject = MakeShareable(new FJsonObject());
			messageObject->SetStringField("role", message.role);
			messageObject->SetStringField("content", message.content);
			TSharedRef<FJsonValueObject> StringValue = MakeShareable(new FJsonValueObject(messageObject));
			Messages.Add(StringValue);
		}
	}
	Shared->SetArrayField(TEXT("messages"), Messages);

	//TODO: Create and implement payload for ChatSettings.Functions

	
	
	//Booleans
	CheckAndSet(Shared, ChatSettings.Continue_);
	
	//Strings
	CheckAndSet(Shared, ChatSettings.Mode);
	CheckAndSet(Shared, ChatSettings.FunctionCall);
	CheckAndSet(Shared, ChatSettings.Character);
	CheckAndSet(Shared, ChatSettings.ChatInstructCommand);
	CheckAndSet(Shared, ChatSettings.ChatTemplateStr);
	CheckAndSet(Shared, ChatSettings.Context);
	CheckAndSet(Shared, ChatSettings.Greeting);
	CheckAndSet(Shared, ChatSettings.InstructionTemplate);
	CheckAndSet(Shared, ChatSettings.InstructionTemplateStr);
	CheckAndSet(Shared, ChatSettings.Name1);
	CheckAndSet(Shared, ChatSettings.Name2);
	CheckAndSet(Shared, ChatSettings.UserBio);
	
}
