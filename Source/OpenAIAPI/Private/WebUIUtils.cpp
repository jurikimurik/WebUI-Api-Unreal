#include "WebUIUtils.h"


void UWebUIUtils::IncludeBasicGenerationSettings(TSharedPtr<FJsonObject> Shared, const FBasicGenerationSettings& Basics)
{
	//Array<String>
		// Optional Arguments
		if (!Basics.Stop.IsEmpty())
		{
			TArray <TSharedPtr<FJsonValue>> StopStrings;
			for (const FString& stopString : Basics.Stop)
			{
				TSharedPtr<FJsonValueString> stopStr = MakeShareable(new FJsonValueString(stopString));
				StopStrings.Add(stopStr);
			}
			Shared->SetArrayField("stop", StopStrings);
		}
		if (!Basics.SamplerPriority.IsEmpty())
		{
			TArray <TSharedPtr<FJsonValue>> Samplers;
			for (const FString& samplerStr : Basics.SamplerPriority)
			{
				TSharedPtr<FJsonValueString> sampler = MakeShareable(new FJsonValueString(samplerStr));
				Samplers.Add(sampler);
			}
			Shared->SetArrayField("sampler_priority", Samplers);
		}

	//Booleans
	Shared->SetBoolField(TEXT("add_bos_token"), Basics.AddBosToken);
	Shared->SetBoolField(TEXT("auto_max_new_tokens"), Basics.AutoMaxNewTokens);
	Shared->SetBoolField(TEXT("ban_eos_token"), Basics.BanEosToken);
	Shared->SetBoolField(TEXT("do_sample"), Basics.DoSample);
	Shared->SetBoolField(TEXT("dynamic_temperature"), Basics.DynamicTemperature);
	Shared->SetBoolField(TEXT("skip_special_tokens"), Basics.SkipSpecialTokens);
	Shared->SetBoolField(TEXT("temperature_last"), Basics.TemperatureLast);
		//Optional Arguments
		if (Basics.Stream)
			Shared->SetBoolField("stream", Basics.Stream);


	//Integers
	Shared->SetNumberField(TEXT("max_tokens_second"), Basics.MaxTokensSecond);
	Shared->SetNumberField(TEXT("mirostat_mode"), Basics.MirostatMode);
	Shared->SetNumberField(TEXT("no_repeat_ngram_size"), Basics.NoRepeatNgramSize);
	Shared->SetNumberField(TEXT("prompt_lookup_num_tokens"), Basics.PromptLookupNumTokens);
	Shared->SetNumberField(TEXT("repetition_penalty_range"), Basics.RepetitionPenaltyRange);
	Shared->SetNumberField(TEXT("seed"), Basics.Seed);
	Shared->SetNumberField(TEXT("top_k"), Basics.TopK);
	Shared->SetNumberField(TEXT("truncation_length"), Basics.TruncationLength);
		//Optionals
		if (!Basics.MaxTokens)
			Shared->SetNumberField(TEXT("max_tokens"), Basics.MaxTokens);
		if (!Basics.N)
			Shared->SetNumberField(TEXT("n"), Basics.N);

	//Numbers
	Shared->SetNumberField(TEXT("dynatemp_exponent"), Basics.DynaTempExponent);
	Shared->SetNumberField(TEXT("dynatemp_high"), Basics.DynaTempHigh);
	Shared->SetNumberField(TEXT("dynatemp_low"), Basics.DynaTempLow);
	Shared->SetNumberField(TEXT("encoder_repetition_penalty"), Basics.EncoderRepetitionPenalty);
	Shared->SetNumberField(TEXT("epsilon_cutoff"), Basics.EpsilonCutoff);
	Shared->SetNumberField(TEXT("eta_cutoff"), Basics.EtaCutoff);
	Shared->SetNumberField(TEXT("guidance_scale"), Basics.GuidanceScale);
	Shared->SetNumberField(TEXT("min_p"), Basics.MinP);
	Shared->SetNumberField(TEXT("mirostat_eta"), Basics.MirostatEta);
	Shared->SetNumberField(TEXT("mirostat_tau"), Basics.MirostatTau);
	Shared->SetNumberField(TEXT("penalty_alpha"), Basics.PenaltyAlpha);
	Shared->SetNumberField(TEXT("repetition_penalty"), Basics.RepetitionPenalty);
	Shared->SetNumberField(TEXT("smoothing_curve"), Basics.SmoothingCurve);
	Shared->SetNumberField(TEXT("smoothing_factor"), Basics.SmoothingFactor);
	Shared->SetNumberField(TEXT("tfs"), Basics.Tfs);
	Shared->SetNumberField(TEXT("top_a"), Basics.TopA);
	Shared->SetNumberField(TEXT("typical_p"), Basics.TypicalP);
		//Optional
		if (!Basics.FrequencyPenalty)
			Shared->SetNumberField(TEXT("frequency_penalty"), Basics.FrequencyPenalty);
		if (!Basics.PresencePenalty)
			Shared->SetNumberField(TEXT("presence_penalty"), Basics.PresencePenalty);
		if (!Basics.Temperature)
			Shared->SetNumberField(TEXT("temperature"), Basics.Temperature);
		if (!Basics.TopP)
			Shared->SetNumberField(TEXT("top_p"), Basics.TopP);

	//Strings
	Shared->SetStringField(TEXT("custom_token_bans"), Basics.CustomTokenBans);
	Shared->SetStringField(TEXT("grammar_string"), Basics.GrammarString);
	Shared->SetStringField(TEXT("negative_prompt"), Basics.NegativePrompt);
		//Optionals
		if (!Basics.Model.IsEmpty())
			Shared->SetStringField(TEXT("model"), Basics.Model);
		if (!Basics.Preset.IsEmpty())
			Shared->SetStringField(TEXT("present"), Basics.Preset);
		if (!Basics.User.IsEmpty())
			Shared->SetStringField(TEXT("user"), Basics.User);


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
	IncludeBasicGenerationSettings(Shared, CompletionSettings.Basics);


	//Booleans + Optional
	if (CompletionSettings.Echo)
		Shared->SetBoolField(TEXT("echo"), CompletionSettings.Echo);
	
	
	//Integers + Optionals
	if (CompletionSettings.BestOf)
		Shared->SetNumberField(TEXT("best_of"), CompletionSettings.BestOf);
	if (CompletionSettings.LogProbs)
		Shared->SetNumberField(TEXT("log_prob"), CompletionSettings.LogProbs);
	
	//Strings
	Shared->SetStringField("prompt", CompletionSettings.prompt);
		//Optionals
		if (!CompletionSettings.Suffix.IsEmpty())
			Shared->SetStringField(TEXT("suffix"), CompletionSettings.Suffix);
}

void UWebUIUtils::IncludeChatGenerationSettings(TSharedPtr<FJsonObject> Shared,
	const FChatCompletionGenerationSettings& ChatSettings)
{
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
	Shared->SetBoolField(TEXT("continue_"), ChatSettings.Continue_);
	
	//Strings
	Shared->SetStringField(TEXT("mode"), ChatSettings.Mode);
	if (!ChatSettings.FunctionCall.IsEmpty())
		Shared->SetStringField(TEXT("function_call"), ChatSettings.FunctionCall);
	if (!ChatSettings.Character.IsEmpty())
		Shared->SetStringField(TEXT("character"), ChatSettings.Character);
	if (!ChatSettings.ChatInstructCommand.IsEmpty())
		Shared->SetStringField(TEXT("chat_instruct_command"), ChatSettings.ChatInstructCommand);
	if (!ChatSettings.ChatTemplateStr.IsEmpty())
		Shared->SetStringField(TEXT("chat_template_str"), ChatSettings.ChatTemplateStr);
	if (!ChatSettings.Context.IsEmpty())
		Shared->SetStringField(TEXT("context"), ChatSettings.Context);
	if (!ChatSettings.Greeting.IsEmpty())
		Shared->SetStringField(TEXT("greeting"), ChatSettings.Greeting);
	if (!ChatSettings.InstructionTemplate.IsEmpty())
		Shared->SetStringField(TEXT("instruction_template"), ChatSettings.InstructionTemplate);
	if (!ChatSettings.InstructionTemplateStr.IsEmpty())
		Shared->SetStringField(TEXT("instruction_template_str"), ChatSettings.InstructionTemplate);
	if (!ChatSettings.Name1.IsEmpty())
		Shared->SetStringField(TEXT("name1"), ChatSettings.Name1);
	if (!ChatSettings.Name2.IsEmpty())
		Shared->SetStringField(TEXT("name2"), ChatSettings.Name2);
	if (!ChatSettings.UserBio.IsEmpty())
		Shared->SetStringField(TEXT("user_bio"), ChatSettings.UserBio);
	
}
