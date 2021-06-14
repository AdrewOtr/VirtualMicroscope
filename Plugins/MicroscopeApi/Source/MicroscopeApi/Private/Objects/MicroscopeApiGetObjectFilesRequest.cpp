#include "Objects/MicroscopeApiGetObjectFilesRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UMicroscopeGetObjectFilesRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetObjectFilesUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeGetObjectFilesRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
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
    const TArray<TSharedPtr<FJsonValue>> JsonValues = JsonPayload->GetArrayField(Api::Fields::Files);
    
    // Parse JSON objects into Artheon object entities.
    for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonValues); It; ++It) {
        TSharedPtr<FJsonObject> JsonObject = (*It)->AsObject();
    
        if (JsonObject.IsValid()) {
            FMicroscopeFile Object;
            Object.ParseJson(JsonObject);
            Files.Add(Object);
        }
    }

    TriggerDelegates(true);
}
