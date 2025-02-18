﻿#include "WebUIUtils.h"

namespace JSONUtils
{
	// If new type that inherits from FBasicJSONSetting was created - create also specialized template for it!
	
	/**
	 * Template method for checking and setting JSON parameter. Using "SetNumberField" by default.
	 * @tparam T Type that inherits from FBasicJSONSetting.
	 * @param Shared JSONObject were Value should be inserted.
	 * @param Value This will be written in Shared if it is enabled.
	 */
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


void UWebUIUtils::IncludeCustomJSONParameters(TSharedPtr<FJsonObject> Shared, const TArray<FCustomJSONParameter>& Parameters)
{
	//Custom JSON Parameters
	for (const FCustomJSONParameter& param : Parameters)
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
		

	IncludeCustomJSONParameters(Shared, Basics.CustomJSONParameters);

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
			messageObject->SetStringField("role", message.Role);
			messageObject->SetStringField("content", message.Content);
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

void UWebUIUtils::IncludeBasicModelSettings(TSharedPtr<FJsonObject> Shared,
                                            const FBasicModelSettings& BasicModelSettings)
{
	using namespace JSONUtils;
	
	//The name of the model
	CheckAndSet(Shared, BasicModelSettings.ModelName);
	//TODO: Include "Settings" also
}

void UWebUIUtils::IncludeTransformerModelSettings(TSharedPtr<FJsonObject> Shared,
                                                  const FTransformerSettings& ModelSettings)
{
	using namespace JSONUtils;

	UWebUIUtils::IncludeBasicModelSettings(Shared, ModelSettings.Basics);

	//Array<Object>
	TSharedPtr<FJsonObject> argsObject = MakeShareable(new FJsonObject());
		
	//Types
	CheckAndSet(argsObject, ModelSettings.ComputeDType);
	CheckAndSet(argsObject, ModelSettings.QuantType);
		
	//Strings
	CheckAndSet(argsObject, ModelSettings.CpuMemory);
		
	//Numbers
	CheckAndSet(argsObject, ModelSettings.AlphaValue);
		
	//Integers
	CheckAndSet(argsObject, ModelSettings.GpuMemory0);
	CheckAndSet(argsObject, ModelSettings.RopeFreqBase);
	CheckAndSet(argsObject, ModelSettings.CompressPosEmb);
		
	//Bools
	CheckAndSet(argsObject, ModelSettings.Cpu);
	CheckAndSet(argsObject, ModelSettings.LoadIn8bit);
	CheckAndSet(argsObject, ModelSettings.Bf16);
	CheckAndSet(argsObject, ModelSettings.AutoDevices);
	CheckAndSet(argsObject, ModelSettings.Disk);
	CheckAndSet(argsObject, ModelSettings.LoadIn4bit);
	CheckAndSet(argsObject, ModelSettings.TrustRemoteCode);
	CheckAndSet(argsObject, ModelSettings.NoUseFast);
	CheckAndSet(argsObject, ModelSettings.UseFlashAttention2);
	CheckAndSet(argsObject, ModelSettings.DisableExllama);
	CheckAndSet(argsObject, ModelSettings.DisableExllamav2);

	//Additional JSON parameters to put in "args" field
	IncludeCustomJSONParameters(argsObject, ModelSettings.ArgsCustomParameters);

	TSharedPtr<FJsonValueObject> argsValueObject = MakeShareable(new FJsonValueObject(argsObject)); 
	Shared->SetField(TEXT("args"), argsValueObject);
	
	//Other additional JSON parameters
	IncludeCustomJSONParameters(Shared, ModelSettings.Basics.CustomJSONParameters);
}
