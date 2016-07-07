#pragma once
#include <SFML\Graphics.hpp>
#include "..\Frame.hpp"

class Animator :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	Animator();
	~Animator();

	bool Start();
	bool Update();
	void Stop();

	bool AddFrame(const Frame & frame);
	bool DelFrame(const uint8_t & id);
	bool DelCurrentFrame();

	Frame GetFrame(const uint8_t & id);
	Frame GetCurrentFrame();
	std::string GetCurrentFrameTextureTag();
	///	Returns animation length in seconds
	float GetAnimationLength();
	void SetRepeat(const bool & newStatement);

	uint8_t GetCurrentFramePlayingID();

	bool IsPlaying();
	bool IsReapeated();

private:
	std::vector<Frame> m_frames;
	sf::Clock * m_clock;
	uint8_t m_currentFramePlayingID;
	bool m_playing;
	bool m_repeat;
};

