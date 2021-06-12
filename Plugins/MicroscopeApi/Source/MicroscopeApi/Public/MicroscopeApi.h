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
    static const FString Departments = TEXT("departments");
#pragma endregion

    const FString RootUrl = TEXT("http://127.0.0.1:8000"); // Local debug API.

#pragma region Objects
    const FString ObjectsUrl = RootUrl + _ + Objects;

    inline FString MakeGetObjectsUrl() {
        return ObjectsUrl;
    }

    inline FString MakeGetObjectUrl(const FString Id) {
        return ObjectsUrl + _ + Id;
    }
#pragma endregion

#pragma region Departments
    const FString DepartmentsUrl = RootUrl + _ + Departments;

    inline FString MakeGetDepartmentsUrl() {
        return DepartmentsUrl;
    }

    inline FString MakeGetDepartmentUrl(const FString Id) {
        return DepartmentsUrl + _ + Id;
    }

    inline FString MakeGetDepartmentObjectsUrl(const FString Id) {
        return DepartmentsUrl + _ + Id + _ + Objects;
    }

    inline FString MakePostDepartmentUrl(const FString Title) {
        return ObjectsUrl + _ + Title;
    }

    inline FString MakePostObjectUrl(const FString DepartmentId) {
        return ObjectsUrl + _ + DepartmentId;
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
