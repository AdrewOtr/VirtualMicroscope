#pragma once
#include "MicroscopeFile.h"

#include "MicroscopeDepartment.generated.h"

USTRUCT(BlueprintType)
struct MICROSCOPEAPI_API FMicroscopeDepartment  {
    GENERATED_BODY()

	FMicroscopeDepartment(){
    }

	virtual ~FMicroscopeDepartment() = default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Date;

    virtual void ParseJson(const TSharedPtr<FJsonObject> JsonObject);
	virtual TSharedPtr<FJsonObject> ToJson();
};
