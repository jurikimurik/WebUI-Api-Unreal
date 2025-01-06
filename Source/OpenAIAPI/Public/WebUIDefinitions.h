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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	bool IsEnabled = true;

	//The associated name in JSON format for this parameter.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
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
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	bool Value = false;
};

//Integer JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingInteger : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingInteger() = default;
	FBasicJSONSettingInteger(const int32& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	int32 Value = 0;
};

//String JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingString : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingString() = default;
	FBasicJSONSettingString(const FString& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString Value = TEXT("");
};

//Number JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingFloat : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingFloat() = default;
	FBasicJSONSettingFloat(const float& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	float Value = 0.0;
};

//Strings array of JSON parameter.
USTRUCT(BlueprintType)
struct FBasicJSONSettingStringArray : public FBasicJSONSetting
{
	GENERATED_USTRUCT_BODY()
	
	FBasicJSONSettingStringArray() = default;
	FBasicJSONSettingStringArray(const TArray<FString>& value, const bool& isEnabled, const FString& JSONName) : FBasicJSONSetting(isEnabled, JSONName), Value(value) {}
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	JSONTypeParameter Type = JSONTypeParameter::Number;

	// JSON name of the parameter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString JsonName;

	// Value of the parameter
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FString JsonValue;
	
};


// GENERATION JSON SETTINGS ------------------------------------------------------------------------------------------------------------------------------------------------------


//Basic generation parameters (obtained from text-generator-webui in FastAPI (http://127.0.0.1:5000/docs#/))
USTRUCT(BlueprintType)
struct FBasicGenerationSettings
{
	GENERATED_USTRUCT_BODY()
	
	//Definiotns from https://github.com/oobabooga/text-generation-webui/wiki/03-%E2%80%90-Parameters-Tab

	/**
	 * Maximum number of tokens to generate.
	 * Don't set it higher than necessary: it is used in the truncation calculation through the formula (prompt_length) = min(truncation_length - max_new_tokens, prompt_length),
	 * so your prompt will get truncated if you set it too high.
	 */

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger MaxTokens = FBasicJSONSettingInteger(200, true, TEXT("max_tokens"));
	
	/**
	 * Primary factor to control the randomness of outputs. 0 = deterministic (only the most likely token is used). Higher value = more randomness.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat Temperature = FBasicJSONSettingFloat(0.7, true, TEXT("temperature"));

	/**
	 * If not set to 1, select tokens with probabilities adding up to less than this number. Higher value = higher range of possible random results.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat TopP = FBasicJSONSettingFloat(0.9, true, TEXT("top_p"));

	/**
	 * Tokens with probability smaller than (min_p) * (probability of the most likely token) are discarded.
	 * This is the same as top_a but without squaring the probability.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat MinP = FBasicJSONSettingFloat(0, true, TEXT("min_p"));

	/**
	 * Similar to top_p, but select instead only the top_k most likely tokens. Higher value = higher range of possible random results.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger TopK = FBasicJSONSettingInteger(20, true, TEXT("top_k"));
	
	/**
	 * Similar to repetition_penalty, but with an additive offset on the raw token scores instead of a multiplicative factor.
	 * It may generate better results. 0 means no penalty, higher value = less repetition, lower value = more repetition.
	 * Previously called "additive_repetition_penalty".
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat PresencePenalty = FBasicJSONSettingFloat(0, true, TEXT("presence_penalty"));

	/**
	* Repetition penalty that scales based on how many times the token has appeared in the context.
	 * Be careful with this; there's no limit to how much a token can be penalized.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat FrequencyPenalty = FBasicJSONSettingFloat(0, true, TEXT("frequency_penalty"));

	/**
	 * The number of most recent tokens to consider for repetition penalty. 0 makes all tokens be used.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger RepetitionPenaltyRange = FBasicJSONSettingInteger(1024, true, TEXT("repetition_penalty_range"));

	/**
	 * If not set to 1, select only tokens that are at least this much more likely to appear than random tokens, given the prior text.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat TypicalP = FBasicJSONSettingFloat(1, true, TEXT("typical_p"));

	/**
	 * Tries to detect a tail of low-probability tokens in the distribution and removes those tokens.
	 * See https://www.trentonbricken.com/Tail-Free-Sampling/ for details.
	 * The closer to 0, the more discarded tokens.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat Tfs = FBasicJSONSettingFloat(1, true, TEXT("tfs"));

	/**
	 * Tokens with probability smaller than (top_a) * (probability of the most likely token)^2 are discarded.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat TopA = FBasicJSONSettingFloat(0, true, TEXT("top_a"));

	/**
	 * In units of 1e-4; a reasonable value is 3. This sets a probability floor below which tokens are excluded from being sampled.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat EpsilonCutoff = FBasicJSONSettingFloat(0, true , TEXT("epsilon_cutoff"));

	/**
	 * The main parameter for Classifier-Free Guidance (CFG). https://arxiv.org/pdf/2306.17806.pdf suggests that 1.5 is a good value.
	 * It can be used in conjunction with a negative prompt or not.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat GuidanceScale = FBasicJSONSettingFloat(1, true, TEXT("guidance_scale"));

	/**
	 * Only used when guidance_scale != 1. It is most useful for instruct models and custom system messages.
	 * You place your full prompt in this field with the system message replaced with the default one for the model
	 * (like "You are Llama, a helpful assistant...") to make the model pay more attention to your custom system message.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString NegativePrompt = FBasicJSONSettingString(TEXT(""), false, TEXT("negative_prompt"));
	
	/**
	 * Contrastive Search is enabled by setting this to greater than zero and unchecking "do_sample".
	 * It should be used with a low value of top_k, for instance, top_k = 4.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat PenaltyAlpha = FBasicJSONSettingFloat(0, true, TEXT("penalty_alpha"));

	/**
	 * Activates the Mirostat sampling technique. It aims to control perplexity during sampling.
	 * See https://arxiv.org/abs/2007.14966
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger MirostatMode = FBasicJSONSettingInteger(0, true, TEXT("mirostat_mode"));

	/**
	 * No idea, see the paper for details. According to the Preset Arena, 8 is a good value.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat MirostatTau = FBasicJSONSettingFloat(5, true, TEXT("mirostat_tau"));

	/**
	 * No idea, see the paper for details. According to the Preset Arena, 0.1 is a good value.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat MirostatEta = FBasicJSONSettingFloat(0.1, true, TEXT("mirostat_eta"));

	/**
	* Activates Dynamic Temperature. This modifies temperature to range between "dynatemp_low" (minimum) and "dynatemp_high" (maximum), with an entropy-based scaling.
	* The steepness of the curve is controlled by "dynatemp_exponent".
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool DynamicTemperature = FBasicJSONSettingBool(false, true, TEXT("dynamic_temperature"));


	/**
	 * Activates Quadratic Sampling. When 0 < smoothing_factor < 1, the logits distribution becomes flatter. When smoothing_factor > 1, it becomes more peaked.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat SmoothingFactor = FBasicJSONSettingFloat(0, true, TEXT("smoothing_factor"));

	/**
	 * Makes temperature the last sampler instead of the first.
	 * With this, you can remove low probability tokens with a sampler like min_p and then use a high temperature to make the model creative without losing coherency.
	 * Note: this parameter takes precedence over "Sampler priority".
	 * That means that temperature/dynamic_temperature/quadratic_sampling will be removed from wherever they are and moved to the end of the stack.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool TemperatureLast = FBasicJSONSettingBool(false, true, TEXT("temperature_last"));

	/**
	 * When unchecked, sampling is entirely disabled, and greedy decoding is used instead (the most likely token is always picked).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool DoSample = FBasicJSONSettingBool(true, true, TEXT("do_sample"));

	/**
	 * Set the Pytorch seed to this number. Note that some loaders do not use Pytorch (notably llama.cpp), and others are not deterministic (ExLlamaV2).
	 * For these loaders, the seed has no effect.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger Seed = FBasicJSONSettingInteger(-1, true, TEXT("seed"));

	/**
	 * Also known as the "Hallucinations filter". Used to penalize tokens that are not in the prior text.
	 * Higher value = more likely to stay in context, lower value = more likely to diverge.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat EncoderRepetitionPenalty = FBasicJSONSettingFloat(1, true, TEXT("encoder_repetition_penalty"));

	/**
	 *  If not set to 0, specifies the length of token sets that are completely blocked from repeating at all.
	 *  Higher values = blocks larger phrases, lower values = blocks words or letters from repeating.
	 *  Only 0 or high values are a good idea in most cases.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger NoRepeatNgramSize = FBasicJSONSettingInteger(0, true, TEXT("no_repeat_ngram_size"));

	
	/**
	 * Used to prevent the prompt from getting bigger than the model's context length.
	 * In the case of the transformers loader, which allocates memory dynamically, this parameter can also be used to set a VRAM ceiling and prevent out-of-memory errors.
	 * This parameter is automatically updated with the model's context length (from "n_ctx" or "max_seq_len" for loaders that use these parameters,
	 * and from the model metadata directly for loaders that do not) when you load a model.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger TruncationLength =FBasicJSONSettingInteger(8192, true, TEXT("truncation_length"));

	/**
	 * To make text readable in real-time in case the model is generating too fast. Good if you want to flex and tell everyone how good your GPU is.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger MaxTokensSecond = FBasicJSONSettingInteger(0, true, TEXT("max_tokens_second"));
	
	/**
	 * The model stops generating as soon as any of the strings set in this field is generated.
	 * Note that when generating text in the Chat tab, some default stopping strings are set regardless of this parameter, like "\nYour Name:" and "\nBot name:" for chat mode.
	 * That's why this parameter has a "Custom" in its name.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingStringArray Stop = FBasicJSONSettingStringArray({}, false, TEXT("stop"));

	/**
	 * Allows you to ban the model from generating certain tokens altogether.
	 * You need to find the token IDs under "Default" > "Tokens" or "Notebook" > "Tokens", or by looking at the tokenizer.json for the model directly.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString CustomTokenBans = FBasicJSONSettingString(TEXT(""), false, TEXT("custom_token_bans"));

	/**
	 * When checked, the max_new_tokens parameter is expanded in the backend to the available context length.
	 * The maximum length is given by the "truncation_length" parameter.
	 * This is useful for getting long replies in the Chat tab without having to click on "Continue" many times.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool AutoMaxNewTokens = FBasicJSONSettingBool(false, true, TEXT("auto_max_new_tokens"));

	/**
	*  One of the possible tokens that a model can generate is the EOS (End of Sequence) token.
	*  When it is generated, the generation stops prematurely.
	*  When this parameter is checked, that token is banned from being generated, and the generation will always generate "max_new_tokens" tokens.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool BanEosToken = FBasicJSONSettingBool(false, true, TEXT("ban_eos_token"));

	/**
	 * By default, the tokenizer will add a BOS (Beginning of Sequence) token to your prompt.
	 * During training, BOS tokens are used to separate different documents.
	 * If unchecked, no BOS token will be added, and the model will interpret your prompt as being in the middle of a document instead of at the start of one.
	 * This significantly changes the output and can make it more creative.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool AddBosToken = FBasicJSONSettingBool(true, true, TEXT("add_bos_token"));
	
	/**
	 * When decoding the generated tokens, skip special tokens from being converted to their text representation. Otherwise, BOS appears as <s>, EOS as </s>, etc.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool SkipSpecialTokens = FBasicJSONSettingBool(true, true, TEXT("skip_special_tokens"));

	/**
	 * When unchecked, the full response is outputted at once, without streaming the words one at a time.
	 * I recommend unchecking this parameter on high latency networks like running the webui on Google Colab or using --share.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool Stream = FBasicJSONSettingBool(false, false, TEXT("stream"));
	
	/**
	 * Allows you to customize the order in which the different samplers are applied.
	 * The first sampler on the list gets applied first.
	 * With this, custom orders like top_p -> temperature -> top_k can be defined.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString GrammarString = FBasicJSONSettingString(TEXT(""), false, TEXT("grammar_string"));

	/**
	 * The steepness of the dynamic temperature curve is controlled by this.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat DynaTempExponent = FBasicJSONSettingFloat(0, false, TEXT("dynatemp_exponent"));

	/**
	 * Connected with Dynamic Temperature.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat DynaTempHigh = FBasicJSONSettingFloat(0, false, TEXT("dynatemp_high"));

	/**
	 * Connected woth Dynamic Temperature.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat DynaTempLow = FBasicJSONSettingFloat(0, false, TEXT("dynatemp_low"));
	

	/**
	 * In units of 1e-4; a reasonable value is 3. The main parameter of the special Eta Sampling technique. See https://arxiv.org/pdf/2210.15191.pdf for a description.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat EtaCutoff = FBasicJSONSettingFloat(0, true, TEXT("eta_cutoff"));

	/**
	 * The name of the model (?)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Model = FBasicJSONSettingString(TEXT(""), false, TEXT("model"));

	/**
	 * Can be used to save and load combinations of parameters for reuse.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Preset = FBasicJSONSettingString(TEXT("simple-1"), false, TEXT("preset"));

	/**
	 * Penalty factor for repeating prior tokens. 1 means no penalty, higher value = less repetition, lower value = more repetition.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat RepetitionPenalty = FBasicJSONSettingFloat(1.15, true, TEXT("repetition_penalty"));

	/**
	 * Connected with smoothing factor.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingFloat SmoothingCurve = FBasicJSONSettingFloat(1, true , TEXT("smoothing_curve"));
	
	/**
	 * A unique identifier representing your end-user.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString User = FBasicJSONSettingString("User", false, TEXT("user"));
	
	/**
	* (https://platform.openai.com/docs/api-reference/completions/create)
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString LogitBias = FBasicJSONSettingString(TEXT(""), false, TEXT("logit_bias"));

	/**
	 * How many completions to generate for each prompt.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger N = FBasicJSONSettingInteger(1, true, TEXT("n"));

	/**
	 * Unfortunately, no idea.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger PromptLookupNumTokens = FBasicJSONSettingInteger(0, true, TEXT("prompt_lookup_num_tokens"));

	
	/**
	 * Custom JSON parameter that should be included.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	TArray<FCustomJSONParameter> CustomJSONParameters;
	
};

//Generation parameters for basic completion. (Retrieved from FastAPI on http://127.0.0.1:5000/docs#/)
USTRUCT(BlueprintType)
struct FCompletionGenerationSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicGenerationSettings Basics;

	/**
	* (https://platform.openai.com/docs/api-reference/completions)
	* Generates best_of completions server-side and returns the "best" (the one with the highest log probability per token). Results cannot be streamed.
	* When used with n, best_of controls the number of candidate completions and n specifies how many to return – best_of must be greater than n.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger BestOf = FBasicJSONSettingInteger(0, false, TEXT("best_of"));

	/**
	 * (https://platform.openai.com/docs/api-reference/completions)
	 * Echo back the prompt in addition to the completion.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool Echo = FBasicJSONSettingBool(false, false, TEXT("echo"));

	/**
	* (https://platform.openai.com/docs/api-reference/completions)
	* Include the log probabilities on the logprobs most likely output tokens, as well the chosen tokens.
	* For example, if logprobs is 5, the API will return a list of the 5 most likely tokens.
	* The API will always return the logprob of the sampled token, so there may be up to logprobs+1 elements in the response.
	* The maximum value for logprobs is 5.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingInteger LogProbs = FBasicJSONSettingInteger(0, false, TEXT("logprobs"));

	/**
	* (https://platform.openai.com/docs/api-reference/completions)
	* The prompt(s) to generate completions for, encoded as a string.
	* Note that <|endoftext|> is the document separator that the model sees during training,
	* so if a prompt is not specified the model will generate as if from the beginning of a new document.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString prompt = FBasicJSONSettingString(TEXT(""), true, TEXT("prompt"));

	/**
	 * The suffix that comes after a completion of inserted text.
	 * This parameter is only supported for gpt-3.5-turbo-instruct.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Suffix = FBasicJSONSettingString(TEXT(""), false, TEXT("suffix"));
	
};

//Generation parameters for chat completions. (Retrieved from FastAPI on http://127.0.0.1:5000/docs#/)
USTRUCT(BlueprintType)
struct FChatCompletionGenerationSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicGenerationSettings Basics;
	
	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Character = FBasicJSONSettingString(TEXT(""), false, TEXT("character"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString ChatInstructCommand = FBasicJSONSettingString(TEXT(""), false, TEXT("chat_instruct_command"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString ChatTemplateStr = FBasicJSONSettingString(TEXT(""), false, TEXT("chat_template_str"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Context = FBasicJSONSettingString(TEXT(""), false, TEXT("context"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingBool Continue_ = FBasicJSONSettingBool(false, true, TEXT("continue_"));
	
	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString FunctionCall = FBasicJSONSettingString(TEXT(""), false, TEXT("function_call"));

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	//TArray<FString> Functions;

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Greeting = FBasicJSONSettingString(TEXT(""), false, TEXT("greeting"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString InstructionTemplate = FBasicJSONSettingString(TEXT(""), false, TEXT("instruction_template"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString InstructionTemplateStr = FBasicJSONSettingString(TEXT(""), false, TEXT("instruction_template_str"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	TArray<FChatMessage> Messages;

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Mode = FBasicJSONSettingString(TEXT(""), true, TEXT("mode"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Name1 = FBasicJSONSettingString(TEXT(""), false, TEXT("name1"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString Name2 = FBasicJSONSettingString(TEXT(""), false, TEXT("name2"));

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OpenAI")
	FBasicJSONSettingString UserBio = FBasicJSONSettingString(TEXT(""), false, TEXT("user_bio"));
	
};
