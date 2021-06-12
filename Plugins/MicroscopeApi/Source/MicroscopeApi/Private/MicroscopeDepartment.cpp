#include "MicroscopeDepartment.h"

#include "MicroscopeApi.h"


void FMicroscopeDepartment::ParseJson(const TSharedPtr<FJsonObject> JsonObject) {
    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Id)) {
        Id = JsonObject->GetStringField(Api::Fields::Id);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Title)) {
        Title = JsonObject->GetStringField(Api::Fields::Title);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Date)) {
        Date = JsonObject->GetStringField(Api::Fields::Date);
    }
}

TSharedPtr<FJsonObject> FMicroscopeDepartment::ToJson() {
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

    JsonObject->SetStringField(Api::Fields::Id, Id);
    JsonObject->SetStringField(Api::Fields::Title, Title);
    JsonObject->SetStringField(Api::Fields::Date, Date);
    
    return JsonObject;
}
