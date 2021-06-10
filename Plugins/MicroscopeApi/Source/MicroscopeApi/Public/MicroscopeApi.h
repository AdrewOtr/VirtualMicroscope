// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

MICROSCOPEAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogMicroscopeApi, All, All);

class FMicroscopeApiModule : public IModuleInterface {
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

namespace Api {

#pragma region
    static const FString _ = TEXT("/");

    static const FString Objects = TEXT("objects");
#pragma endregion

    const FString RootUrl = TEXT("http://127.0.0.1:8000"); // Local debug API.

#pragma region Objects
    const FString ObjectsUrl = RootUrl + _ + Objects;

    inline FString MakeObjectsIndexUrl(const int32 Offset = 0, const int32 Limit = 10, const FString& Query = "") {
        return ObjectsUrl + FString::Printf(TEXT("?offset=%d&limit=%d&query=%s"), Offset, Limit, *Query);
    }

    inline FString MakeObjectUrl(const FString Id) {
        return ObjectsUrl + _ + Id;
    }
#pragma endregion

    namespace HttpMethods {
        const auto Get = TEXT("GET");
        const auto Post = TEXT("POST");
        const auto Put = TEXT("PUT");
        const auto Patch = TEXT("PATCH");
        const auto Delete = TEXT("DELETE");
    }

    namespace Headers {
        const auto RequestId = TEXT("id");
        const auto Referer = TEXT("referer");
        const auto Key = TEXT("key");
        const auto ContentType = TEXT("Content-Type");
        const auto Accept = TEXT("Accept");
    }

    namespace ContentTypes {
        const auto ApplicationJson = TEXT("application/json");
        const FString MultipartFormData = TEXT("multipart/form-data");
    }

    namespace Types {
        const auto Object = TEXT("object");
    }

    namespace Fields {
        const auto Payload = TEXT("data");
        const auto Id = TEXT("id");
        const auto Type = TEXT("type");
        const auto Url = TEXT("url");
        const auto Date = TEXT("date");
        const auto Title = TEXT("title");
        const auto Description = TEXT("description");
        const auto Name = TEXT("name");
        const auto Object = TEXT("object");
        const auto Files = TEXT("files");
        const auto DepartmentId = TEXT("department_id");
        const auto Zoom = TEXT("Zoom");
    }
}
