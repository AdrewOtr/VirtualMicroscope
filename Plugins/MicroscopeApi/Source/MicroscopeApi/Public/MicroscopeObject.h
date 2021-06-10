#pragma once
#include "MicroscopeFile.h"

#include "MicroscopeObject.generated.h"

USTRUCT(BlueprintType)
struct MICROSCOPEAPI_API FMicroscopeObject  {
    GENERATED_BODY()

	FMicroscopeObject(){
    }

	virtual ~FMicroscopeObject() = default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Date;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString DepartmentId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
	TArray<FMicroscopeFile> Files;

    virtual void ParseJson(const TSharedPtr<FJsonObject> JsonObject);
	virtual TSharedPtr<FJsonObject> ToJson();
};
