#include <SpriteRenderSystem.h>

#include <gameContext.h>
#include <EntityComponentSystem.h>
#include <SpriteComponent.h>
#include <components/TransformComponent.h>
#include <FreeListPoolElement.h>

#include <OGLML/Sprite.h>

#include <GameMaps.h>
#include <ECSBreakout.h>

#include <array>

using namespace breakout;

void SpriteRenderSystem::Init()
{

}

void SpriteRenderSystem::Update(float dtMilliseconds)
{
	Render();
}

void SpriteRenderSystem::Render()
{
	auto& ecs = GameContext::Get().GetECS();
	const auto& spriteComponents = ecs.GetAllComponentsByType<SpriteComponent>();

	for (auto& component : spriteComponents)
	{
		auto& spriteComponent = static_cast<FreeListPoolElement<SpriteComponent>*>(component)->GetContainer();
		int entityId = spriteComponent.m_entityId;
		
		if (entityId == static_cast<int>(EEntityIdStatus::PREFABS_CONTAINER))
		{
			auto entityIdSet = ecs.GetAllEntityIdBoundWithPrefab(spriteComponent.m_componentId);
			if (!entityIdSet)
				continue;

			for (auto& id : *entityIdSet)
			{
				auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(id);

				auto& sprite = spriteComponent.Sprite();
				sprite.SetPosition(transformComponent.GetPosition());
				sprite.SetSize(transformComponent.GetScale());
				sprite.SetRotateAngle(transformComponent.GetRotation());

				sprite.Draw();
			}
		}
		else
		{
			auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(entityId);

			auto& sprite = spriteComponent.Sprite();
			sprite.SetPosition(transformComponent.GetPosition());
			sprite.SetSize(transformComponent.GetScale());
			sprite.SetRotateAngle(transformComponent.GetRotation());

			sprite.Draw();
		}
	}
}