#pragma once

#include "JSONParameters.h"

#include "Models.generated.h"

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
