#pragma once

#include "JSONParameters.generated.h"

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
