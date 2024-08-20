#include "GameStateManger.h"
#include "AEEngine.h"
#include "../Level/BaseLevel.h"
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/LogicComponent.h"
#include "../ComponentManager/EngineComponent.h"
#include "../ComponentManager/GraphicComponent.h"
#include "../Components/AudioComp.h"
#include "../EventManager/EventManager.h"
#include "../CollisionManager/CollisionManager.h"

GSM::GameStateManager* GSM::GameStateManager::ptr = nullptr;

GSM::GameStateManager::GameStateManager() : previousLevel(nullptr), currentLevel(nullptr) {}

GSM::GameStateManager::~GameStateManager()
{
    if (previousLevel)
        delete previousLevel;

    if (currentLevel)
        delete currentLevel;
}

GSM::GameStateManager* GSM::GameStateManager::GetPtr()
{
    if (ptr == nullptr)
    {
        ptr = new GameStateManager;
    }

    return ptr;
}

void GSM::GameStateManager::DeletePtr()
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

void GSM::GameStateManager::Init()
{
    if (currentLevel)
    {
        currentLevel->Init();
    }
}

void GSM::GameStateManager::Update()
{
    if (currentLevel)
    {
        ComponentManager<LogicComponent>::GetPtr()->Update();
        ComponentManager<EngineComponent>::GetPtr()->Update();
        ComponentManager<GraphicComponent>::GetPtr()->Update();
        ComponentManager<AudioComp>::GetPtr()->Update();

        EventManager::GetPtr()->DispatchAllEvents();

        CollisionManager::GetPtr()->Update();

        AEGfxSetBackgroundColor(0, 0, 0);

        currentLevel->Update();
    }
}

void GSM::GameStateManager::Exit()
{
    if (currentLevel)
    {
        ComponentManager<LogicComponent>::DeletePtr();
        ComponentManager<EngineComponent>::DeletePtr();
        ComponentManager<GraphicComponent>::DeletePtr();
        ComponentManager<AudioComp>::DeletePtr();

        EventManager::DeletePtr();
        CollisionManager::DeletePtr();

        currentLevel->Exit();
    }
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
    if (previousLevel)
        delete previousLevel;

    previousLevel = currentLevel;

    //Exit the current level
    Exit();

    //Current level is now the "next" level
    currentLevel = newLvl;

    //initialize the level
    Init();
}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
