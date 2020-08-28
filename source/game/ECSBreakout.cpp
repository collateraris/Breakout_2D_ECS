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
#include <AudioManager.h>

#include <OGLML/Sprite.h>
#include <OGLML/Shader.h>
#include <OGLML/Texture2D.h>

#include <SpriteComponent.h>
#include <SpriteColorComponent.h>
#include <components/TransformComponent.h>
#include <MovementComponent.h>
#include <PlayerComponent.h>
#include <PlayerBallComponent.h>
#include <ParticlesComponent.h>
#include <ColliderComponent.h>
#include <PowerUpComponent.h>

#include <LogManager.h>

#include <InputManager.h>
#include <GameMaps.h>

#include <EventsStorage.h>

#include <cassert>
#include <array>
#include <algorithm>

using namespace breakout;

BreakoutInitGameData g_initData;

int CreateAwersomeEntity();

int CreateBackground();

int CreateSolidBlock();

int CreateBlock();

int CreatePlayerPaddle();

int CreatePlayerBall();

int CreateSpeedPowerUp();
int CreateStickyPowerUp();
int CreatePassThroughPowerUp();
int CreatePadSizeIncreasePowerUp();
int CreateConfusePowerUp();
int CreateChaosPowerUp();

void ECSBreakout::Init()
{
	AudioManager::Get().PlayMusic(EMusicAssetId::BreakoutMain);

	LoadInitDataFromConfig();

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
	case EEntityType::SpeedPowerUp:
		return CreateSpeedPowerUp();
		break;
	case EEntityType::StickyPowerUp:
		return CreateStickyPowerUp();
		break;
	case EEntityType::PassThroughPowerUp:
		return CreatePassThroughPowerUp();
		break;
	case EEntityType::PadSizeIncreasePowerUp:
		return CreatePadSizeIncreasePowerUp();
		break;
	case EEntityType::ConfusePowerUp:
		return CreateConfusePowerUp();
		break;
	case EEntityType::ChaosPowerUp:
		return CreateChaosPowerUp();
		break;
	default:
		assert(false, entityNotInitStr);
		return -1;
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
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Saved);

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::SolidBlock), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::SolidBlock));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreateBlock()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::Block));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Destroyable);

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);

	ecs.AddComponentByEntityId<SpriteColorComponent>(entityId);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::Block), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Block));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreatePlayerPaddle()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::PlayerPaddle));

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

	const std::array<float, 2>& playerSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerPaddleSize)];
	const std::array<float, 2> playerSizePos = { screenWidth * 0.5f - playerSize[0] * 0.5f,
		screenHeight - playerSize[1] };
	transformComponent.SetPosition(playerSizePos);
	transformComponent.SetScale(playerSize);

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Saved)
		.SetSize(playerSize[0], playerSize[1])
		.SetPosition(playerSizePos);

	auto& movementComponent = ecs.AddComponentByEntityId<MovementComponent>(entityId);
	const std::array<float, 2>& playerVelocity = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerPaddleVelocity)];
	movementComponent.SetVelocity(playerVelocity);

	InputManager::Get().OnKeyPressed().BindLambda([&](oglml::EKeyButtonCode key, oglml::EKeyModeCode mode)
	{
		if (key == oglml::EKeyButtonCode::KEY_A)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_MOVE_LEFT));
		}
		else if (key == oglml::EKeyButtonCode::KEY_D)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_MOVE_RIGHT));
		}
		else if (key == oglml::EKeyButtonCode::KEY_SPACE)
		{
			EventsStorage::Get().Put(BaseEvent(EEventType::PLAYER_ACTION_SPACE_CLICK));
		}
	});

	return entityId;
}

int CreatePlayerBall()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::PlayerBall));

	ecs.AddComponentByEntityId<PlayerBallComponent>(entityId);

	const std::array<float, 2>& ballSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerBallSize)];
	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	transformComponent.SetScale(ballSize);

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Circle)
		.SetDamagableType(EDamagableType::Saved)
		.SetSize(ballSize[0], ballSize[1]);

	auto& spriteComponent = ecs.AddComponentByEntityId<SpriteComponent>(entityId);
	auto& sprite = spriteComponent.Sprite();

	auto window = GameContext::Get().GetMainWindow();

	float screenWidth = window->GetWidth();
	float screenHeight = window->GetHeight();
	sprite.SetScreenSize(screenWidth, screenHeight);
	transformComponent.SetPosition({0., screenHeight});
	colliderComponent.SetPosition({ 0., screenHeight });

	auto& particlesTexture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Particle));
	auto& particlesShader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Particle));
	auto& particlesComponent = ecs.AddComponentByEntityId<ParticlesComponent>(entityId);
	particlesComponent.SetOrthoParams(screenWidth, screenHeight);
	particlesComponent.SetTexture(particlesTexture);
	particlesComponent.SetShader(particlesShader);

	auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::Awersome));
	sprite.SetTexture(texture);

	auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
	sprite.SetShader(shader);

	auto& movementComponent = ecs.AddComponentByEntityId<MovementComponent>(entityId);
	const std::array<float, 2>& ballVelocity  = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::playerBallVelocity)];
	movementComponent.SetVelocity(ballVelocity);

	return entityId;
}

int CreateSpeedPowerUp()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::SpeedPowerUp));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Intacted);

	auto* powerUpComponent = ecs.AddPrefabComponentByEntityId<PowerUpComponent>(static_cast<int>(EEntityType::SpeedPowerUp), entityId);
	if (powerUpComponent)
		powerUpComponent->powerUpType = EPowerUpType::Speed;

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	const auto& powerUpSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpSize)];
	transformComponent.SetScale(powerUpSize);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::SpeedPowerUp), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::SpeedPowerUp));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreateStickyPowerUp()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::StickyPowerUp));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Intacted);

	auto* powerUpComponent = ecs.AddPrefabComponentByEntityId<PowerUpComponent>(static_cast<int>(EEntityType::StickyPowerUp), entityId);
	if (powerUpComponent)
		powerUpComponent->powerUpType = EPowerUpType::Sticky;

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	const auto& powerUpSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpSize)];
	transformComponent.SetScale(powerUpSize);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::StickyPowerUp), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::StickyPowerUp));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreatePassThroughPowerUp()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::PassThroughPowerUp));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Intacted);

	auto* powerUpComponent = ecs.AddPrefabComponentByEntityId<PowerUpComponent>(static_cast<int>(EEntityType::PassThroughPowerUp), entityId);
	if (powerUpComponent)
		powerUpComponent->powerUpType = EPowerUpType::PassThrough;

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	const auto& powerUpSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpSize)];
	transformComponent.SetScale(powerUpSize);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::PassThroughPowerUp), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::PassThroughPowerUp));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreatePadSizeIncreasePowerUp()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::PadSizeIncreasePowerUp));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Intacted);

	auto* powerUpComponent = ecs.AddPrefabComponentByEntityId<PowerUpComponent>(static_cast<int>(EEntityType::PadSizeIncreasePowerUp), entityId);
	if (powerUpComponent)
		powerUpComponent->powerUpType = EPowerUpType::PadSizeIncrease;

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	const auto& powerUpSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpSize)];
	transformComponent.SetScale(powerUpSize);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::PadSizeIncreasePowerUp), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::PadSizeIncreasePowerUp));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreateConfusePowerUp()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::ConfusePowerUp));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Intacted);

	auto* powerUpComponent = ecs.AddPrefabComponentByEntityId<PowerUpComponent>(static_cast<int>(EEntityType::ConfusePowerUp), entityId);
	if (powerUpComponent)
		powerUpComponent->powerUpType = EPowerUpType::Confuse;

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	const auto& powerUpSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpSize)];
	transformComponent.SetScale(powerUpSize);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::ConfusePowerUp), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::ConfusePowerUp));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

	return entityId;
}

int CreateChaosPowerUp()
{
	auto& ecs = GameContext::Get().GetECS();
	int entityId = ecs.CreateEntityByEntityTypeId(static_cast<int>(EEntityType::ChaosPowerUp));

	auto& colliderComponent = ecs.AddComponentByEntityId<ColliderComponent>(entityId);
	colliderComponent.SetColliderType(EColliderType::Square)
		.SetDamagableType(EDamagableType::Intacted);

	auto* powerUpComponent = ecs.AddPrefabComponentByEntityId<PowerUpComponent>(static_cast<int>(EEntityType::ChaosPowerUp), entityId);
	if (powerUpComponent)
		powerUpComponent->powerUpType = EPowerUpType::Chaos;

	auto& transformComponent = ecs.AddComponentByEntityId<TransformComponent>(entityId);
	const auto& powerUpSize = ECSBreakout::GetInitGameData().data[static_cast<int>(EBreakoutInitGameDataId::powerUpSize)];
	transformComponent.SetScale(powerUpSize);

	auto* spriteComponent = ecs.AddPrefabComponentByEntityId<SpriteComponent>(static_cast<int>(EEntityType::ChaosPowerUp), entityId);
	if (spriteComponent)
	{
		auto& sprite = spriteComponent->Sprite();

		auto& texture = TexturesManager::Get().GetResource(static_cast<int>(ETextureAssetId::ChaosPowerUp));
		sprite.SetTexture(texture);

		auto& shader = ShadersManager::Get().GetResource(static_cast<int>(EShaderAssetId::Sprite));
		sprite.SetShader(shader);

		auto window = GameContext::Get().GetMainWindow();

		float screenWidth = window->GetWidth();
		float screenHeight = window->GetHeight();
		sprite.SetScreenSize(screenWidth, screenHeight);
	}

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
		case breakout::EComponentType::Particles:
			ComponentManager::Get().CreateComponentPool<ParticlesComponent>(poolSize);
			break;
		case breakout::EComponentType::SpriteColor:
			ComponentManager::Get().CreateComponentPool<SpriteColorComponent>(poolSize);
			break;
		case breakout::EComponentType::PowerUp:
			ComponentManager::Get().CreateComponentPool<PowerUpComponent>(poolSize);
			break;
		default:
			break;
		}
	}
}

void ECSBreakout::CreateWorld()
{
	ECSBreakout::CreateComponent(EEntityType::Background);

	GameMaps::Get().LoadMap(EGameMapLevels::Bounce_galore);

	ECSBreakout::CreateComponent(EEntityType::PlayerPaddle);
	ECSBreakout::CreateComponent(EEntityType::PlayerBall);
}

void ECSBreakout::LoadInitDataFromConfig()
{
	auto initDatas = GameContext::Get().GetConfigManager().GetRoot().GetPath(initDataStr).GetChildren();
	for (auto& data : initDatas)
	{
		int id = data.GetAttribute<int>(idStr);
		float val1  = data.GetAttribute<float>(val1Str);
		float val2 = data.GetAttribute<float>(val2Str);

		g_initData.data[id] = {val1, val2};
	}
}

const BreakoutInitGameData& ECSBreakout::GetInitGameData()
{
	return g_initData;
}