#include "Registry.h"
#include "../Components/TransformComp.h"
#include "../Components/AudioComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/RigidBodyComp.h"
#include "../Components/EnemyComp.h"
#include "../Components/AnimatorComp.h"

Registry::Registry()
{
    // Register ALL the functions
    rttiMap.insert({ TransformComp::TypeName, &TransformComp::CreateTransformComponent });
    rttiMap.insert({ AudioComp::TypeName, &AudioComp::CreateAudioComponent });
    rttiMap.insert({ PlayerComp::TypeName, &PlayerComp::CreatePlayerComponent });
    rttiMap.insert({ SpriteComp::TypeName, &SpriteComp::CreateSpriteComponent });
    rttiMap.insert({ RigidbodyComp::TypeName, &RigidbodyComp::CreateRigidBodyComponent });
    rttiMap.insert({ EnemyComp::TypeName, &EnemyComp::CreateEnemyComponent });
    rttiMap.insert({ AnimatorComp::TypeName, &AnimatorComp::CreateAnimatorComponent });
}

BaseRTTI* Registry::FindAndCreate(const std::string& type, GameObject* owner)
{
    BaseRTTI* ptr = nullptr;
    if (rttiMap.find(type) != rttiMap.end())
        ptr = rttiMap[type](owner);
    else
        throw std::invalid_argument("Registry FindAndCreate Invalid typeName " + type);

    return ptr;
}
