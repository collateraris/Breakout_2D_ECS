#pragma once

#include <Component.h>

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

		using ColorsData = std::array<float, 3>;
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

		void RespawnParticle(entityId id);

		void SetNumber(int size);
		void SetTexture(oglml::Texture2D& texture);
		void SetShader(oglml::Shader& shader);

	protected:

		oglml::Particles& Particles();

		void Resize();

	private:

		int m_particlesNumber = 0;

		oglml::Particles m_particles;

		std::vector<ColorsData> m_colors = {};
		std::vector<OffsetsData> m_offsets = {};
		std::vector<VelocityData> m_velocities = {};
		std::vector<LifeData> m_life = {};
	};
}