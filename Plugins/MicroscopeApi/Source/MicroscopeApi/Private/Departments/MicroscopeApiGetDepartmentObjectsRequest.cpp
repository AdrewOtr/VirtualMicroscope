#include "Departments/MicroscopeApiGetDepartmentObjectsRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"

void UMicroscopeGetDepartmentObjectsRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetDepartmentObjectsUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeGetDepartmentObjectsRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
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
    const TArray<TSharedPtr<FJsonValue>> JsonValues = JsonPayload->GetArrayField(Api::Fields::Objects);
    
    // Parse JSON objects into Artheon object entities.
    for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonValues); It; ++It) {
        TSharedPtr<FJsonObject> JsonObject = (*It)->AsObject();
    
        if (JsonObject.IsValid()) {
            FMicroscopeObject Object;
            Object.ParseJson(JsonObject);
            Objects.Add(Object);
        }
    }

    TriggerDelegates(true);
}
