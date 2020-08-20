#include <AudioManager.h>

#include <AssetsManager.h>

#include <irrKlang.h>

using namespace breakout;

AudioManager::AudioManager()
{
	m_soundEngine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{

}

AudioManager& AudioManager::Get()
{
	static AudioManager audioManager;
	return audioManager;
}

void AudioManager::PlaySound(ESoundAssetId soundId)
{
	auto& assetManager = AssetManager::Get();
	m_soundEngine->play2D(assetManager.GetPath(soundId).c_str(), false);
}

void AudioManager::PlayMusic(EMusicAssetId musicId)
{
	auto& assetManager = AssetManager::Get();
	m_soundEngine->play2D(assetManager.GetPath(musicId).c_str(), true);
}