#include "Departments/MicroscopeApiGetDepartmentsRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"

void UMicroscopeGetDepartmentsRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetDepartmentsUrl());

    Super::ProcessRequest();
}

void UMicroscopeGetDepartmentsRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    TSharedPtr<FJsonObject> JsonPayload;
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseStr);
    
    if (!FJsonSerializer::Deserialize(JsonReader, JsonPayload) || !JsonPayload.IsValid()) {
        return TriggerDelegates(false);
    }
    
    // Get array of JSON objects.
    const TArray<TSharedPtr<FJsonValue>> JsonValues = JsonPayload->GetArrayField(Api::Fields::Departments);
    
    // Parse JSON objects into Artheon object entities.
    for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonValues); It; ++It) {
        TSharedPtr<FJsonObject> JsonObject = (*It)->AsObject();
    
        if (JsonObject.IsValid()) {
            FMicroscopeDepartment Object;
            Object.ParseJson(JsonObject);
            Departments.Add(Object);
        }
    }

    TriggerDelegates(true);
}
