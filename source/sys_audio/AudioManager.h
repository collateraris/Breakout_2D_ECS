#pragma once

#include <SoundAssetId.h>
#include <MusicAssetId.h>

namespace irrklang
{
	class ISoundEngine;
}

namespace breakout
{
	class AudioManager
	{
	public:

		static AudioManager& Get();

		void PlaySound(ESoundAssetId soundId);
		void PlayMusic(EMusicAssetId musicId);

	private:

		AudioManager();
		~AudioManager();
		AudioManager(AudioManager&) = delete;
		AudioManager(AudioManager&&) = delete;
		void operator=(AudioManager&) = delete;
		void operator=(AudioManager&&) = delete;

		irrklang::ISoundEngine* m_soundEngine = nullptr;
	};
}