#include "MicroscopeFile.h"

#include "MicroscopeApi.h"

void FMicroscopeFile::ParseJson(const TSharedPtr<FJsonObject> JsonObject) {
    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Id)) {
        Id = JsonObject->GetStringField(Api::Fields::Id);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Type)) {
        Type = JsonObject->GetStringField(Api::Fields::Type);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Url)) {
        Url = JsonObject->GetStringField(Api::Fields::Url);
    }

    if (JsonObject->HasTypedField<EJson::Number>(Api::Fields::Zoom)) {
        Zoom = JsonObject->GetNumberField(Api::Fields::Zoom);
    }
}

TSharedPtr<FJsonObject> FMicroscopeFile::ToJson() {
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

    if (!Id.IsEmpty()) {
        JsonObject->SetStringField(Api::Fields::Id, Id);
    }

    if (!Type.IsEmpty()) {
        JsonObject->SetStringField(Api::Fields::Type, Type);
    }

    if (!Url.IsEmpty()) {
        JsonObject->SetStringField(Api::Fields::Url, Url);
    }
    JsonObject->SetNumberField(Api::Fields::Zoom, Zoom);

    return JsonObject;
}
