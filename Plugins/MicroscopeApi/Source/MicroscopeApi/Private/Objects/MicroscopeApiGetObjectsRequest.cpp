#include "Objects/MicroscopeApiGetObjectsRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UMicroscopeGetObjectsRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetObjectsUrl());

    Super::ProcessRequest();
}

void UMicroscopeGetObjectsRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    // TSharedPtr<FJsonObject> JsonPayload;
    // const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseStr);
    //
    // if (!FJsonSerializer::Deserialize(JsonReader, JsonPayload) || !JsonPayload.IsValid()) {
    //     return TriggerDelegates(false);
    // }
    //
    // const TSharedPtr<FJsonObject> JsonObjectPayload = JsonPayload->GetObjectField(Api::Fields::Payload);
    //
    // // Get array of JSON objects.
    // const TArray<TSharedPtr<FJsonValue>> JsonValues = JsonObjectPayload->GetArrayField(Api::Fields::Entities);
    //
    // // Parse JSON objects into Artheon object entities.
    // for (TArray<TSharedPtr<FJsonValue>>::TConstIterator It(JsonValues); It; ++It) {
    //     TSharedPtr<FJsonObject> JsonObject = (*It)->AsObject();
    //
    //     if (JsonObject.IsValid()) {
    //         FMicroscopeObject Object;
    //         Object.ParseJson(JsonObject);
    //         Objects.Add(Object);
    //     }
    // }

    TriggerDelegates(true);
}
