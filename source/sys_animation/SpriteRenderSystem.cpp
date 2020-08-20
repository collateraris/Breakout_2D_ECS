#include <SpriteRenderSystem.h>

#include <gameContext.h>
#include <EntityComponentSystem.h>
#include <SpriteComponent.h>
#include <SpriteColorComponent.h>
#include <components/TransformComponent.h>
#include <FreeListPoolElement.h>

#include <OGLML/SpriteInstanced.h>
#include <OGLML/Sprite.h>


#include <GameMaps.h>
#include <ECSBreakout.h>

#include <array>

using namespace breakout;

static const size_t MAX_SPRITE_INSTANCE_FOR_DRAW = 150;

oglml::SpriteInstanced<MAX_SPRITE_INSTANCE_FOR_DRAW> g_spriteInstancedRender;

void SpriteRenderSystem::Init()
{
	g_spriteInstancedRender.GenBuffers();
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
			auto entityIdSet = ecs.GetAllEntityIdBoundWithPrefab(spriteComponent.m_componentUniqueId);
			if (!entityIdSet)
				continue;

			g_spriteInstancedRender.ClearSpriteData();
			for (auto& id : *entityIdSet)
			{
				if (g_spriteInstancedRender.IsFull())
				{
					g_spriteInstancedRender.DrawInstanced();
					g_spriteInstancedRender.ClearSpriteData();
				}

				auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(id);

				auto& sprite = spriteComponent.Sprite();
				sprite.SetPosition(transformComponent.GetPosition());
				sprite.SetSize(transformComponent.GetScale());
				sprite.SetRotateAngle(transformComponent.GetRotation());

				if (ecs.IsContainComponentByEntityId<SpriteColorComponent>(id))
				{
					auto& spriteColorComponent = ecs.GetComponentByEntityId<SpriteColorComponent>(id);
					sprite.SetColor(spriteColorComponent.GetColor());
				}

				g_spriteInstancedRender.CollectSpriteData(sprite);			
			}

			g_spriteInstancedRender.DrawInstanced();
			g_spriteInstancedRender.ClearSpriteData();
		}
		else
		{
			auto& transformComponent = ecs.GetComponentByEntityId<TransformComponent>(entityId);

			auto& sprite = spriteComponent.Sprite();
			sprite.SetPosition(transformComponent.GetPosition());
			sprite.SetSize(transformComponent.GetScale());
			sprite.SetRotateAngle(transformComponent.GetRotation());

			if (ecs.IsContainComponentByEntityId<SpriteColorComponent>(entityId))
			{
				auto& spriteColorComponent = ecs.GetComponentByEntityId<SpriteColorComponent>(entityId);
				sprite.SetColor(spriteColorComponent.GetColor());
			}

			g_spriteInstancedRender.ClearSpriteData();
			g_spriteInstancedRender.CollectSpriteData(sprite);
			g_spriteInstancedRender.DrawInstanced();
			g_spriteInstancedRender.ClearSpriteData();
		}
	}
}