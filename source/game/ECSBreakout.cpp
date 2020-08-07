#include <ECSBreakout.h>

#include <gameContext.h>
#include <Component.h>
#include <ComponentManager.h>
#include <EntityComponentSystem.h>
#include <gameWindow.h>

#include <StringConstants.h>

#include <ConfigManager.h>
#include <AssetsManager.h>
#include <ResourcesManager.h>
#include <TexturesManager.h>
#include <ShadersManager.h>

#include <OGLML/Sprite.h>
#include <OGLML/Shader.h>
#include <OGLML/Texture2D.h>

#include <SpriteComponent.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>
#include <PlayerComponent.h>
#include <PlayerBallComponent.h>
#include <ColliderComponent.h>

#include <LogManager.h>

#include <InputManager.h>
#include <GameMaps.h>

#include <EventsStorage.h>

#include <cassert>
#include <array>
#include <algorithm>

using namespace breakout;

int CreateAwersomeEntity();

int CreateBackground();

int CreateSolidBlock();

int CreateBlock();

int CreatePlayerPaddle();

int CreatePlayerBall();

void ECSBreakout::Init()
{
	InitComponentsPools();

	CreateWorld();
}

int ECSBreakout::CreateComponent(EEntityType type)
{
	switch (type)
	{
	case EEntityType::Awersome:
		return CreateAwersomeEntity();
		break;
	case EEntityType::Background:
		return CreateBackground();
		break;
	case EEntityType::SolidBlock:
		return CreateSolidBlock();
		break;
	case EEntityType::Block:
		return CreateBlock();
		break;
	case EEntityType::PlayerPaddle:
		return CreatePlayerPaddle();
		break;
	case EEntityType::PlayerBall:
		return CreatePlayerBall();
		break;
	default:
		assert(false, entityNotInitStr);
		break;
	}
}

int CreateAwersomeEntity()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::Awersome));

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	transformComponent.SetPosition({ 200.0f, 200.0f });
	transformComponent.SetScale({ 300.0f, 400.0f });
	transformComponent.SetRotation(45.f);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);
	sprite.SetColor({ 0.0f, 1.0f, 0.0f });

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Awersome));
	sprite.SetTexture(texture);

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	return entityId;
}

int CreateBackground()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::Background));

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	transformComponent.SetPosition({ 0.0f, 0.0f });
	transformComponent.SetRotation(0.f);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Background));
	sprite.SetTexture(texture);

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);
	transformComponent.SetScale({ screenWidth, screenHeight });

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	return entityId;
}

int CreateSolidBlock()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::SolidBlock));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square);

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::SolidBlock));
	sprite.SetTexture(texture);

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);

	return entityId;
}

int CreateBlock()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::Block));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square);

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Block));
	sprite.SetTexture(texture);

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);

	return entityId;
}

int CreatePlayerPaddle()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::Block));

	ecs.AddComponentByEntityId<PlayerComponent>(entityId);

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::PlayerPaddle));
	sprite.SetTexture(texture);

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);

	const std::array<float, 2> playerSize = { 100.0f, 20.0f };
	transformComponent.SetPosition({ screenWidth * 0.5f - playerSize[0] * 0.5f, 
		screenHeight - playerSize[1]});
	transformComponent.SetScale(playerSize);

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square).SetSize(playerSize[0], playerSize[1]);

	auto& movementComponent = ecs.AddComponentByEntityId<MovementComponent>(entityId);
	movementComponent.SetVelocity({2000.f, 0.f});

	InputManager::Get().OnKeyPress().BindLambda([&](oglml::EKeyButtonCode key, oglml::EKeyModeCode mode)
	{
		if (key == oglml::EKeyButtonCode::KEY_A)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_MOVE_LEFT));
			LOG(playerMoveLeftPushEvent.c_str());
		}
		else if (key == oglml::EKeyButtonCode::KEY_D)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_MOVE_RIGHT));
			LOG(playerMoveRightPushEvent.c_str());
		}
		else if (key == oglml::EKeyButtonCode::KEY_SPACE)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_SPACE_CLICK));
			LOG(playerSpaceClickPushEventRight.c_str());
		}
	});

	return entityId;
}

int CreatePlayerBall()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::PlayerBall));

	ecs.AddComponentByEntityId<PlayerBallComponent>(entityId);

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	transformComponent.SetScale({ 25.5f, 25.5f });

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Circle).SetSize(25.5f, 25.5f);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Awersome));
	sprite.SetTexture(texture);

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	auto& movementComponent = ecs.AddComponentByEntityId<MovementComponent>(entityId);
	movementComponent.SetVelocity({ 100.0f, -350.0f });

	return entityId;
}

void ECSBreakout::InitComponentsPools()
{
	auto components = GameContext::Get().GetConfigManager().GetRoot().GetPath(componentsStr).GetChildren();

	for (auto& component : components)
	{
		EComponentType id = static_cast<EComponentType>(component.GetAttribute<int>(idStr));
		int poolSize = component.GetAttribute<int>(poolSizeStr);
		
		switch (id)
		{
		case breakout::EComponentType::Sprite:
			ComponentManager::Get().CreateComponentPool<SpriteComponent>(poolSize);
			break;
		case breakout::EComponentType::Transform:
			ComponentManager::Get().CreateComponentPool<TransformComponent>(poolSize);
			break;
		case breakout::EComponentType::Movement:
			ComponentManager::Get().CreateComponentPool<MovementComponent>(poolSize);
			break;
		case breakout::EComponentType::Player:
			ComponentManager::Get().CreateComponentPool<PlayerComponent>(poolSize);
			break;
		case breakout::EComponentType::PlayerBall:
			ComponentManager::Get().CreateComponentPool<PlayerBallComponent>(poolSize);
			break;
		case breakout::EComponentType::Collider:
			ComponentManager::Get().CreateComponentPool<ColliderComponent>(poolSize);
			break;
		default:
			break;
		}
	}
}

void ECSBreakout::CreateWorld()
{
	ECSBreakout::CreateComponent(EEntityType::Background);

	GameMaps::Get().LoadMap(EGameMapLevels::Space_invader);

	ECSBreakout::CreateComponent(EEntityType::PlayerPaddle);
	ECSBreakout::CreateComponent(EEntityType::PlayerBall);
}