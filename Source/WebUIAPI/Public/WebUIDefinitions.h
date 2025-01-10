#pragma once

#include "CoreMinimal.h"
#include "WebUIDefinitions.generated.h"

// COMPLETION ------------------------------------------------------------------------------------------------------------------------------------------------------------

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

// CHAT ---------------------------------------------------------------------------------------------------------------------------------------------------------------

// One separate message
USTRUCT(BlueprintType)
struct FChatMessage
{
	GENERATED_USTRUCT_BODY()

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

// JSON PARAMETERS -----------------------------------------------------------------------------------------------------------------------------------------------


/**
 * Basic structure for all JSON parameters.
 * Cast to bool - return if this parameter is enabled.
 * Cast to FString - return associated JSON name of this parameter.
 */
USTRUCT(BlueprintType)
struct FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSetting() = default;
	FBasicJSONSetting(const bool& isEnabled, const FString& JSONName) : IsEnabled(isEnabled), JSONParameterName(JSONName) {}

	//Should this parameter be included in JSON?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	bool IsEnabled = true;

	//The associated name in JSON format for this parameter.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString JSONParameterName = TEXT("");

	//Auto-conversion to bool for fast checking if this parameter enabled.
	explicit operator bool() const
	{
		return IsEnabled;
	}

	//Auto-conversion to FString to retrieve parameter name.
	explicit operator FString() const
	{
		return JSONParameterName;
	}
};

// Boolean JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingBool : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingBool() = default;
	FBasicJSONSettingBool(const bool& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	bool Value = false;
};

//Integer JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingInteger : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingInteger() = default;
	FBasicJSONSettingInteger(const int32& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	int32 Value = 0;
};

//String JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingString : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingString() = default;
	FBasicJSONSettingString(const FString& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString Value = TEXT("");
};

//Number JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingFloat : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingFloat() = default;
	FBasicJSONSettingFloat(const float& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	float Value = 0.0;
};

//Strings array of JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingStringArray : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingStringArray() = default;
	FBasicJSONSettingStringArray(const TArray<FString>& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FString> Value = {};
};

// JSON CUSTOM PARAMETERS -----------------------------------------------------------------------------------------------------------------------------------------------

// Type of JSON setting parameter
UENUM()
enum class JSONTypeParameter
{
	Number,
	Integer,
	String
};

// Custom JSON parameters to include
USTRUCT(BlueprintType)
struct FCustomJSONParameter
{
	GENERATED_USTRUCT_BODY()

	//Type of the JSON parameter (Only Number, Integer and String are supported)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	JSONTypeParameter Type = JSONTypeParameter::Number;

	// JSON name of the parameter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString JsonName;

	// Value of the parameter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FString JsonValue;
	
};


// GENERATION JSON SETTINGS ------------------------------------------------------------------------------------------------------------------------------------------------------


//Basic generation parameters (obtained from text-generator-webui in FastAPI (http://127.0.0.1:5000/docs#/))
USTRUCT(BlueprintType)
struct FBasicGenerationSettings
{
	GENERATED_USTRUCT_BODY()
	
	//Definitions from https://github.com/oobabooga/text-generation-webui/wiki/03-%E2%80%90-Parameters-Tab

	/**
	 * Maximum number of tokens to generate.
	 * Don't set it higher than necessary: it is used in the truncation calculation through the formula (prompt_length) = min(truncation_length - max_new_tokens, prompt_length),
	 * so your prompt will get truncated if you set it too high.
	 */

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger MaxTokens = FBasicJSONSettingInteger(200, true, TEXT("max_tokens"));
	
	/**
	 * Primary factor to control the randomness of outputs. 0 = deterministic (only the most likely token is used). Higher value = more randomness.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat Temperature = FBasicJSONSettingFloat(0.7, true, TEXT("temperature"));

	/**
	 * If not set to 1, select tokens with probabilities adding up to less than this number. Higher value = higher range of possible random results.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat TopP = FBasicJSONSettingFloat(0.9, true, TEXT("top_p"));

	/**
	 * Tokens with probability smaller than (min_p) * (probability of the most likely token) are discarded.
	 * This is the same as top_a but without squaring the probability.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat MinP = FBasicJSONSettingFloat(0, true, TEXT("min_p"));

	/**
	 * Similar to top_p, but select instead only the top_k most likely tokens. Higher value = higher range of possible random results.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger TopK = FBasicJSONSettingInteger(20, true, TEXT("top_k"));
	
	/**
	 * Similar to repetition_penalty, but with an additive offset on the raw token scores instead of a multiplicative factor.
	 * It may generate better results. 0 means no penalty, higher value = less repetition, lower value = more repetition.
	 * Previously called "additive_repetition_penalty".
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat PresencePenalty = FBasicJSONSettingFloat(0, true, TEXT("presence_penalty"));

	/**
	* Repetition penalty that scales based on how many times the token has appeared in the context.
	 * Be careful with this; there's no limit to how much a token can be penalized.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat FrequencyPenalty = FBasicJSONSettingFloat(0, true, TEXT("frequency_penalty"));

	/**
	 * The number of most recent tokens to consider for repetition penalty. 0 makes all tokens be used.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger RepetitionPenaltyRange = FBasicJSONSettingInteger(1024, true, TEXT("repetition_penalty_range"));

	/**
	 * If not set to 1, select only tokens that are at least this much more likely to appear than random tokens, given the prior text.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat TypicalP = FBasicJSONSettingFloat(1, true, TEXT("typical_p"));

	/**
	 * Tries to detect a tail of low-probability tokens in the distribution and removes those tokens.
	 * See https://www.trentonbricken.com/Tail-Free-Sampling/ for details.
	 * The closer to 0, the more discarded tokens.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat Tfs = FBasicJSONSettingFloat(1, true, TEXT("tfs"));

	/**
	 * Tokens with probability smaller than (top_a) * (probability of the most likely token)^2 are discarded.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat TopA = FBasicJSONSettingFloat(0, true, TEXT("top_a"));

	/**
	 * In units of 1e-4; a reasonable value is 3. This sets a probability floor below which tokens are excluded from being sampled.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat EpsilonCutoff = FBasicJSONSettingFloat(0, true , TEXT("epsilon_cutoff"));

	/**
	 * The main parameter for Classifier-Free Guidance (CFG). https://arxiv.org/pdf/2306.17806.pdf suggests that 1.5 is a good value.
	 * It can be used in conjunction with a negative prompt or not.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat GuidanceScale = FBasicJSONSettingFloat(1, true, TEXT("guidance_scale"));

	/**
	 * Only used when guidance_scale != 1. It is most useful for instruct models and custom system messages.
	 * You place your full prompt in this field with the system message replaced with the default one for the model
	 * (like "You are Llama, a helpful assistant...") to make the model pay more attention to your custom system message.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString NegativePrompt = FBasicJSONSettingString(TEXT(""), false, TEXT("negative_prompt"));
	
	/**
	 * Contrastive Search is enabled by setting this to greater than zero and unchecking "do_sample".
	 * It should be used with a low value of top_k, for instance, top_k = 4.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat PenaltyAlpha = FBasicJSONSettingFloat(0, true, TEXT("penalty_alpha"));

	/**
	 * Activates the Mirostat sampling technique. It aims to control perplexity during sampling.
	 * See https://arxiv.org/abs/2007.14966
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger MirostatMode = FBasicJSONSettingInteger(0, true, TEXT("mirostat_mode"));

	/**
	 * No idea, see the paper for details. According to the Preset Arena, 8 is a good value.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat MirostatTau = FBasicJSONSettingFloat(5, true, TEXT("mirostat_tau"));

	/**
	 * No idea, see the paper for details. According to the Preset Arena, 0.1 is a good value.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat MirostatEta = FBasicJSONSettingFloat(0.1, true, TEXT("mirostat_eta"));

	/**
	* Activates Dynamic Temperature. This modifies temperature to range between "dynatemp_low" (minimum) and "dynatemp_high" (maximum), with an entropy-based scaling.
	* The steepness of the curve is controlled by "dynatemp_exponent".
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool DynamicTemperature = FBasicJSONSettingBool(false, true, TEXT("dynamic_temperature"));


	/**
	 * Activates Quadratic Sampling. When 0 < smoothing_factor < 1, the logits distribution becomes flatter. When smoothing_factor > 1, it becomes more peaked.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat SmoothingFactor = FBasicJSONSettingFloat(0, true, TEXT("smoothing_factor"));

	/**
	 * Makes temperature the last sampler instead of the first.
	 * With this, you can remove low probability tokens with a sampler like min_p and then use a high temperature to make the model creative without losing coherency.
	 * Note: this parameter takes precedence over "Sampler priority".
	 * That means that temperature/dynamic_temperature/quadratic_sampling will be removed from wherever they are and moved to the end of the stack.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool TemperatureLast = FBasicJSONSettingBool(false, true, TEXT("temperature_last"));

	/**
	 * When unchecked, sampling is entirely disabled, and greedy decoding is used instead (the most likely token is always picked).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool DoSample = FBasicJSONSettingBool(true, true, TEXT("do_sample"));

	/**
	 * Set the Pytorch seed to this number. Note that some loaders do not use Pytorch (notably llama.cpp), and others are not deterministic (ExLlamaV2).
	 * For these loaders, the seed has no effect.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger Seed = FBasicJSONSettingInteger(-1, true, TEXT("seed"));

	/**
	 * Also known as the "Hallucinations filter". Used to penalize tokens that are not in the prior text.
	 * Higher value = more likely to stay in context, lower value = more likely to diverge.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat EncoderRepetitionPenalty = FBasicJSONSettingFloat(1, true, TEXT("encoder_repetition_penalty"));

	/**
	 *  If not set to 0, specifies the length of token sets that are completely blocked from repeating at all.
	 *  Higher values = blocks larger phrases, lower values = blocks words or letters from repeating.
	 *  Only 0 or high values are a good idea in most cases.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger NoRepeatNgramSize = FBasicJSONSettingInteger(0, true, TEXT("no_repeat_ngram_size"));

	
	/**
	 * Used to prevent the prompt from getting bigger than the model's context length.
	 * In the case of the transformers loader, which allocates memory dynamically, this parameter can also be used to set a VRAM ceiling and prevent out-of-memory errors.
	 * This parameter is automatically updated with the model's context length (from "n_ctx" or "max_seq_len" for loaders that use these parameters,
	 * and from the model metadata directly for loaders that do not) when you load a model.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger TruncationLength =FBasicJSONSettingInteger(8192, true, TEXT("truncation_length"));

	/**
	 * To make text readable in real-time in case the model is generating too fast. Good if you want to flex and tell everyone how good your GPU is.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger MaxTokensSecond = FBasicJSONSettingInteger(0, true, TEXT("max_tokens_second"));
	
	/**
	 * The model stops generating as soon as any of the strings set in this field is generated.
	 * Note that when generating text in the Chat tab, some default stopping strings are set regardless of this parameter, like "\nYour Name:" and "\nBot name:" for chat mode.
	 * That's why this parameter has a "Custom" in its name.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingStringArray Stop = FBasicJSONSettingStringArray({}, false, TEXT("stop"));

	/**
	 * Allows you to ban the model from generating certain tokens altogether.
	 * You need to find the token IDs under "Default" > "Tokens" or "Notebook" > "Tokens", or by looking at the tokenizer.json for the model directly.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString CustomTokenBans = FBasicJSONSettingString(TEXT(""), false, TEXT("custom_token_bans"));

	/**
	 * When checked, the max_new_tokens parameter is expanded in the backend to the available context length.
	 * The maximum length is given by the "truncation_length" parameter.
	 * This is useful for getting long replies in the Chat tab without having to click on "Continue" many times.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool AutoMaxNewTokens = FBasicJSONSettingBool(false, true, TEXT("auto_max_new_tokens"));

	/**
	*  One of the possible tokens that a model can generate is the EOS (End of Sequence) token.
	*  When it is generated, the generation stops prematurely.
	*  When this parameter is checked, that token is banned from being generated, and the generation will always generate "max_new_tokens" tokens.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool BanEosToken = FBasicJSONSettingBool(false, true, TEXT("ban_eos_token"));

	/**
	 * By default, the tokenizer will add a BOS (Beginning of Sequence) token to your prompt.
	 * During training, BOS tokens are used to separate different documents.
	 * If unchecked, no BOS token will be added, and the model will interpret your prompt as being in the middle of a document instead of at the start of one.
	 * This significantly changes the output and can make it more creative.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool AddBosToken = FBasicJSONSettingBool(true, true, TEXT("add_bos_token"));
	
	/**
	 * When decoding the generated tokens, skip special tokens from being converted to their text representation. Otherwise, BOS appears as <s>, EOS as </s>, etc.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool SkipSpecialTokens = FBasicJSONSettingBool(true, true, TEXT("skip_special_tokens"));

	/**
	 * When unchecked, the full response is outputted at once, without streaming the words one at a time.
	 * I recommend unchecking this parameter on high latency networks like running the webui on Google Colab or using --share.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool Stream = FBasicJSONSettingBool(false, false, TEXT("stream"));
	
	/**
	 * Allows you to customize the order in which the different samplers are applied.
	 * The first sampler on the list gets applied first.
	 * With this, custom orders like top_p -> temperature -> top_k can be defined.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingStringArray SamplerPriority = FBasicJSONSettingStringArray({	"temperature", "dynamic_temperature", "quadric_sampling", "top_k",
										"top_p", "typical_p", "epsilon_cutoff", "eta_cutoff", "tfs",
										"top_a", "min_p", "mirostat"}, true, TEXT("sampler_priority"));

	/**
	 * Allows you to constrain the model output to a particular format.
	 * For instance, you can make the model generate lists, JSON, specific words, etc.
	 * Grammar is extremely powerful and I highly recommend it.
	 * The syntax looks a bit daunting at first sight, but it gets very easy once you understand it.
	 * See https://github.com/ggerganov/llama.cpp/blob/master/grammars/README.md for details.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString GrammarString = FBasicJSONSettingString(TEXT(""), false, TEXT("grammar_string"));

	/**
	 * The steepness of the dynamic temperature curve is controlled by this.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat DynaTempExponent = FBasicJSONSettingFloat(0, false, TEXT("dynatemp_exponent"));

	/**
	 * Connected with Dynamic Temperature.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat DynaTempHigh = FBasicJSONSettingFloat(0, false, TEXT("dynatemp_high"));

	/**
	 * Connected woth Dynamic Temperature.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat DynaTempLow = FBasicJSONSettingFloat(0, false, TEXT("dynatemp_low"));
	

	/**
	 * In units of 1e-4; a reasonable value is 3. The main parameter of the special Eta Sampling technique. See https://arxiv.org/pdf/2210.15191.pdf for a description.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat EtaCutoff = FBasicJSONSettingFloat(0, true, TEXT("eta_cutoff"));

	/**
	 * The name of the model (?)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Model = FBasicJSONSettingString(TEXT(""), false, TEXT("model"));

	/**
	 * Can be used to save and load combinations of parameters for reuse.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Preset = FBasicJSONSettingString(TEXT("simple-1"), false, TEXT("preset"));

	/**
	 * Penalty factor for repeating prior tokens. 1 means no penalty, higher value = less repetition, lower value = more repetition.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat RepetitionPenalty = FBasicJSONSettingFloat(1.15, true, TEXT("repetition_penalty"));

	/**
	 * Connected with smoothing factor.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat SmoothingCurve = FBasicJSONSettingFloat(1, true , TEXT("smoothing_curve"));
	
	/**
	 * A unique identifier representing your end-user.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString User = FBasicJSONSettingString("User", false, TEXT("user"));
	
	/**
	* (https://platform.WebUI.com/docs/api-reference/completions/create)
	* Modify the likelihood of specified tokens appearing in the completion.
	* 
	* Accepts a JSON object that maps tokens (specified by their token ID in the GPT tokenizer) to an associated bias value from -100 to 100.
	* You can use this tokenizer tool to convert text to token IDs.
	* Mathematically, the bias is added to the logits generated by the model prior to sampling.
	* The exact effect will vary per model, but values between -1 and 1 should decrease or increase likelihood of selection;
	* values like -100 or 100 should result in a ban or exclusive selection of the relevant token.
	*
	* As an example, you can pass {"50256": -100} to prevent the <|endoftext|> token from being generated.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString LogitBias = FBasicJSONSettingString(TEXT(""), false, TEXT("logit_bias"));

	/**
	 * How many completions to generate for each prompt.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger N = FBasicJSONSettingInteger(1, true, TEXT("n"));

	/**
	 * Unfortunately, no idea.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger PromptLookupNumTokens = FBasicJSONSettingInteger(0, true, TEXT("prompt_lookup_num_tokens"));

	
	/**
	 * Custom JSON parameter that should be included.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FCustomJSONParameter> CustomJSONParameters;
	
};

//Generation parameters for basic completion. (Retrieved from FastAPI on http://127.0.0.1:5000/docs#/)
USTRUCT(BlueprintType)
struct FCompletionGenerationSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicGenerationSettings Basics;

	/**
	* (https://platform.WebUI.com/docs/api-reference/completions)
	* Generates best_of completions server-side and returns the "best" (the one with the highest log probability per token). Results cannot be streamed.
	* When used with n, best_of controls the number of candidate completions and n specifies how many to return – best_of must be greater than n.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger BestOf = FBasicJSONSettingInteger(0, false, TEXT("best_of"));

	/**
	 * (https://platform.WebUI.com/docs/api-reference/completions)
	 * Echo back the prompt in addition to the completion.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool Echo = FBasicJSONSettingBool(false, false, TEXT("echo"));

	/**
	* (https://platform.WebUI.com/docs/api-reference/completions)
	* Include the log probabilities on the logprobs most likely output tokens, as well the chosen tokens.
	* For example, if logprobs is 5, the API will return a list of the 5 most likely tokens.
	* The API will always return the logprob of the sampled token, so there may be up to logprobs+1 elements in the response.
	* The maximum value for logprobs is 5.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger LogProbs = FBasicJSONSettingInteger(0, false, TEXT("logprobs"));

	/**
	* (https://platform.WebUI.com/docs/api-reference/completions)
	* The prompt(s) to generate completions for, encoded as a string.
	* Note that <|endoftext|> is the document separator that the model sees during training,
	* so if a prompt is not specified the model will generate as if from the beginning of a new document.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString prompt = FBasicJSONSettingString(TEXT(""), true, TEXT("prompt"));

	/**
	 * The suffix that comes after a completion of inserted text.
	 * This parameter is only supported for gpt-3.5-turbo-instruct.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Suffix = FBasicJSONSettingString(TEXT(""), false, TEXT("suffix"));
	
};

//Generation parameters for chat completions. (Retrieved from FastAPI on http://127.0.0.1:5000/docs#/)
USTRUCT(BlueprintType)
struct FChatCompletionGenerationSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicGenerationSettings Basics;
	
	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Character = FBasicJSONSettingString(TEXT(""), false, TEXT("character"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString ChatInstructCommand = FBasicJSONSettingString(TEXT(""), false, TEXT("chat_instruct_command"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString ChatTemplateStr = FBasicJSONSettingString(TEXT(""), false, TEXT("chat_template_str"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Context = FBasicJSONSettingString(TEXT(""), false, TEXT("context"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool Continue_ = FBasicJSONSettingBool(false, true, TEXT("continue_"));
	
	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString FunctionCall = FBasicJSONSettingString(TEXT(""), false, TEXT("function_call"));

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	//TArray<FString> Functions;

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Greeting = FBasicJSONSettingString(TEXT(""), false, TEXT("greeting"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString InstructionTemplate = FBasicJSONSettingString(TEXT(""), false, TEXT("instruction_template"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString InstructionTemplateStr = FBasicJSONSettingString(TEXT(""), false, TEXT("instruction_template_str"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FChatMessage> Messages;

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Mode = FBasicJSONSettingString(TEXT(""), true, TEXT("mode"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Name1 = FBasicJSONSettingString(TEXT(""), false, TEXT("name1"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString Name2 = FBasicJSONSettingString(TEXT(""), false, TEXT("name2"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString UserBio = FBasicJSONSettingString(TEXT(""), false, TEXT("user_bio"));
	
};

// MODELS -------------------------------------------------------------------------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct FModelSettings
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FBasicModelSettings
{
	GENERATED_USTRUCT_BODY()

	// Name of the model to load.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString ModelName = FBasicJSONSettingString(TEXT(""), true, TEXT("model_name"));

	// TODO: Can also contain "Settings" in JSON POST request.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FModelSettings Settings;

	// Additional JSON parameters that should be included.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FCustomJSONParameter> CustomJSONParameters;
};

USTRUCT(BlueprintType)
struct FTransformerSettings
{
	GENERATED_USTRUCT_BODY()

	/**
	 * Basic settings for model.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicModelSettings Basics;
	
	//I don't know why, but CpuMemory needs to be string in JSON POST request to work with Oobagooba's WebUI.

	
	/**
	 * Similarly to the parameter above, you can also set a limit on the amount of CPU memory used.
	 * Whatever doesn't fit either in the GPU or the CPU will go to a disk cache, so to use this option you should also check the "disk" checkbox.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString CpuMemory = FBasicJSONSettingString(TEXT("1"), true, TEXT("cpu_memory"));

	/**
	 * When set to greater than 0, activates CPU offloading using the accelerate library, where part of the layers go to the CPU.
	 * The performance is very bad. Note that accelerate doesn't treat this parameter very literally, so if you want the VRAM usage to be at most 10 GiB,
	 * you may need to set this parameter to 9 GiB or 8 GiB. It can be used in conjunction with "load_in_8bit" but not with "load-in-4bit" as far as I'm aware.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger GpuMemory0 = FBasicJSONSettingInteger(1000, true , TEXT("gpu_memory_0"));

	//TODO: Implement compute_dtype and quant_type to inclide into JSON POST request, because they are types for now.

	
	/**
	 * Used when "load-in-4bit" is checked. I recommend leaving the default value.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString ComputeDType = FBasicJSONSettingString(TEXT("float16"), false, TEXT("compute_dtype"));

	
	/**
	 *  Used when "load-in-4bit" is checked. I recommend leaving the default value.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingString QuantType = FBasicJSONSettingString(TEXT("nf4"), false, TEXT("quant_type"));

	
	/**
	 * Used to extend the context length of a model with a minor loss in quality. I have measured 1.75 to be optimal for 1.5x context, and 2.5 for 2x context.
	 * That is, with alpha = 2.5 you can make a model with 4096 context length go to 8192 context length.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingFloat AlphaValue = FBasicJSONSettingFloat(1.0, true, TEXT("alpha_value"));

	
	/**
	 * Originally another way to write "alpha_value", it ended up becoming a necessary parameter for some models like CodeLlama,
	 * which was fine-tuned with this set to 1000000 and hence needs to be loaded with it set to 1000000 as well.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger RopeFreqBase = FBasicJSONSettingInteger(702000, true, TEXT("rope_freq_base"));

	
	/**
	 * The first and original context-length extension method, discovered by kaiokendev. When set to 2, the context length is doubled,
	 * 3, and it's tripled, etc. It should only be used for models that have been fine-tuned with this parameter set to different from 1.
	 * For models that have not been tuned to have greater context length, alpha_value will lead to a smaller accuracy loss
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingInteger CompressPosEmb = FBasicJSONSettingInteger(1, true, TEXT("compress_pos_emb"));

	
	/**
	 * Loads the model in CPU mode using Pytorch. The model will be loaded in 32-bit precision, so a lot of RAM will be used.
	 * CPU inference with transformers is older than llama.cpp, and it works, but it's a lot slower.
	 * Note: this parameter has a different interpretation in the llama.cpp loader (see below).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool Cpu = FBasicJSONSettingBool(false, true, TEXT("cpu"));

	
	/**
	 * Load the model in 8-bit precision using bitsandbytes.
	 * The 8-bit kernel in that library has been optimized for training and not inference, so load-in-8bit is slower than load-in-4bit (but more accurate).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool LoadIn8bit = FBasicJSONSettingBool(false, true, TEXT("load_in_8bit"));

	
	/**
	 * Use bfloat16 precision instead of float16 (the default). Only applies when quantization is not used.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool Bf16 = FBasicJSONSettingBool(false, true, TEXT("bf16"));

	
	/**
	 * When checked, the backend will try to guess a reasonable value for "gpu-memory" to allow you to load a model with CPU offloading.
	 * I recommend just setting "gpu-memory" manually instead. This parameter is also needed for loading GPTQ models, in which case it needs to be checked before loading the model.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool AutoDevices = FBasicJSONSettingBool(true, true, TEXT("auto_devices"));

	
	/**
	 * Enable disk offloading for layers that don't fit into the GPU and CPU combined.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool Disk = FBasicJSONSettingBool(false, true, TEXT("disk"));

	
	/**
	 * Load the model in 4-bit precision using bitsandbytes.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool LoadIn4bit = FBasicJSONSettingBool(false, true, TEXT("load_in_4bit"));

	
	/**
	 * Some models use custom Python code to load the model or the tokenizer. For such models, this option needs to be set.
	 * It doesn't download any remote content: all it does is execute the .py files that get downloaded with the model.
	 * Those files can potentially include malicious code; I have never seen it happen, but it is in principle possible.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool TrustRemoteCode = FBasicJSONSettingBool(false, true, TEXT("trust_remote_code"));

	
	/**
	 * Do not use the "fast" version of the tokenizer. Can usually be ignored; only check this if you can't load the tokenizer for your model otherwise.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool NoUseFast = FBasicJSONSettingBool(false, true, TEXT("no_use_fast"));


	/**
	 * Set use_flash_attention_2=True while loading the model. Possibly useful for training.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool UseFlashAttention2 = FBasicJSONSettingBool(false, true, TEXT("use_flash_attention_2"));

	
	/**
	 * Only applies when you are loading a GPTQ model through the transformers loader. It needs to be checked if you intend to train LoRAs with the model.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool DisableExllama = FBasicJSONSettingBool(false, true, TEXT("disable_exllama"));

	
	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	FBasicJSONSettingBool DisableExllamav2 = FBasicJSONSettingBool(false, true, TEXT("disable_exllamav2"));

	
	/**
	 * Additional JSON parameters that should be included in "args" field.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebUI")
	TArray<FCustomJSONParameter> ArgsCustomParameters;
};

// DELEGATES -------------------------------------------------------------------------------------------------------------------------------------------------------------------

// To retrieve FString
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiSimpleResponsePin, bool, Success, const FString&, errorMessage, const FString, message);

// To retrieve TArray<FString> 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiArraySimpleResponsePin, bool, Success, const FString&, errorMessage, const TArray<FString>&, message);

// To retrieve FChatCompletionWebUI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiChatCompletionResponseRecievedPin, bool, Success, const FString&, errorMessage, const TArray<FChatCompletionWebUI>&, messages);

// To retrieve FCompletion
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebUiCompletionResponseRecievedPin, bool, Success, const FString&, errorMessage, const FCompletion, message);







