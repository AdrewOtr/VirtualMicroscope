#pragma once
#include "MicroscopeFile.generated.h"

USTRUCT(BlueprintType)
struct MICROSCOPEAPI_API FMicroscopeFile {    
    GENERATED_BODY()
    
    FMicroscopeFile(){
    }

    virtual ~FMicroscopeFile() = default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    FString Url;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Artheon")
    int32 Zoom = 0;


    virtual void ParseJson(const TSharedPtr<FJsonObject> JsonObject);
    virtual TSharedPtr<FJsonObject> ToJson();
};
