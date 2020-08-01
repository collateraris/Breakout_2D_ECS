#include <ECSBreakout.h>

#include <gameContext.h>
#include <EntityComponentSystem.h>
#include <gameWindow.h>

#include <AssetsManager.h>
#include <ResourcesManager.h>
#include <TexturesManager.h>
#include <ShadersManager.h>

#include <OGLML/Sprite.h>
#include <OGLML/Shader.h>
#include <OGLML/Texture2D.h>

#include <SpriteComponent.h>
#include <components/TransformComponent.h>

using namespace breakout;

void CreateAwersomeEntity();

void ECSBreakout::CreateComponent(EEntityType type)
{
	switch (type)
	{
	case EEntityType::Awersome:
		CreateAwersomeEntity();
		break;
	default:
		break;
	}
}

void CreateAwersomeEntity()
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

}