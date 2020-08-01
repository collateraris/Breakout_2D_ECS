#include <SpriteRenderSystem.h>

#include <gameContext.h>
#include <EntityComponentSystem.h>
#include <SpriteComponent.h>
#include <components/TransformComponent.h>
#include <FreeListPoolElement.h>

#include <OGLML/Sprite.h>

#include <vector>

using namespace breakout;

void SpriteRenderSystem::Init()
{

}

void SpriteRenderSystem::Update(float dtMilliseconds)
{

}

void SpriteRenderSystem::Render()
{
	auto& ecs = GameContext::Get().GetECS();
	const auto& spriteComponents = ecs.GetAllComponentsByType<SpriteComponent>();

	for (auto& component : spriteComponents)
	{
		if (!component.IsActive())
			break;

		auto& spriteComponent = static_cast<FreeListPoolElement<SpriteComponent>>(component).GetContainer();
		int entityId = spriteComponent.m_entityId;
		auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(entityId);

		auto& sprite = spriteComponent.Sprite();
		sprite.SetPosition(transformComponent.GetPosition());
		sprite.SetSize(transformComponent.GetScale());
		sprite.SetRotateAngle(transformComponent.GetRotation());

		sprite.Draw();
	}
}