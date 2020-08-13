#pragma once

#include <Component.h>

#include <RingListObjectPool.h>
#include <OGLML/Particles.h>

#include <vector>
#include <array>

namespace oglml
{
	class Particles;
	class Texture2D;
	class Shader;
}

namespace breakout
{

	class ParticlesComponent : public BaseComponent
	{
		using ColorsData = std::array<float, 4>;
		using OffsetsData = std::array<float, 2>;
		using VelocityData = std::array<float, 2>;
		using LifeData = float;

		using entityId = int;

	public:

		static EComponentType GetType()
		{
			return EComponentType::Particles;
		};

		ParticlesComponent();
		~ParticlesComponent();

		void RespawnParticle(unsigned int number, const OffsetsData& offset);

		void SetTexture(oglml::Texture2D& texture);
		void SetShader(oglml::Shader& shader);
		void SetOrthoParams(float width, float height);

		void Draw();

		void Update(float dtMilliseconds);

	protected:

		void Resize();

	private:

		static const unsigned int m_particlesNumber = 500;

		oglml::Particles m_particles;

		std::vector<ColorsData> m_colors = {};
		std::vector<OffsetsData> m_positions = {};
		std::vector<VelocityData> m_velocities = {};
		RingListObjectPool<LifeData, m_particlesNumber> m_lifes;
	};
}