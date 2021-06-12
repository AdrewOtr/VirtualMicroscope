#include "MicroscopeObject.h"

#include "MicroscopeApi.h"


void FMicroscopeObject::ParseJson(const TSharedPtr<FJsonObject> JsonObject) {
    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Id)) {
        Id = JsonObject->GetStringField(Api::Fields::Id);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Title)) {
        Title = JsonObject->GetStringField(Api::Fields::Title);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Date)) {
        Date = JsonObject->GetStringField(Api::Fields::Date);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::DepartmentId)) {
        DepartmentId = JsonObject->GetStringField(Api::Fields::DepartmentId);
    }

    if (JsonObject->HasTypedField<EJson::String>(Api::Fields::Description)) {
        Description = JsonObject->GetStringField(Api::Fields::Description);
    }

    if (JsonObject->HasTypedField<EJson::Array>(Api::Fields::Files)) {
        const TArray<TSharedPtr<FJsonValue>> JsonTraitObjects = JsonObject->GetArrayField(Api::Fields::Files);
        for (TArray<TSharedPtr<FJsonValue>>::TConstIterator TraitIt(JsonTraitObjects); TraitIt; ++TraitIt) {
            TSharedPtr<FJsonObject> JsonTraitObject = (*TraitIt)->AsObject();

            if (JsonTraitObject.IsValid()) {
                FMicroscopeFile Trait;
                Trait.ParseJson(JsonTraitObject);
                Files.Add(Trait);
            }
        }
    }
}

TSharedPtr<FJsonObject> FMicroscopeObject::ToJson() {
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

    JsonObject->SetStringField(Api::Fields::Id, Id);
    JsonObject->SetStringField(Api::Fields::Title, Title);
    JsonObject->SetStringField(Api::Fields::Date, Date);
    JsonObject->SetStringField(Api::Fields::DepartmentId, DepartmentId);
    JsonObject->SetStringField(Api::Fields::Description, Description);

    TArray<TSharedPtr<FJsonValue>> JsonFileTraits;
    for (auto Trait : Files) {
        const TSharedPtr<FJsonObject> JsonTraitObject = Trait.ToJson();
        TSharedPtr<FJsonValueObject> ValueObject = MakeShareable(new FJsonValueObject(JsonTraitObject));
        JsonFileTraits.Add(ValueObject);
    }
    JsonObject->SetArrayField(Api::Fields::Files, JsonFileTraits);

    return JsonObject;
}
