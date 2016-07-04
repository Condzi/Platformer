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

	///	Starts animation with speed (0-2)[default 1]
	bool Start();
	bool Update();
	void Stop();

	bool AddFrame(const Frame & frame);
	bool DelFrame(const uint8_t & id);
	bool DelCurrentFrame();

	Frame GetFrame(const uint8_t & id);
	Frame GetCurrentFrame();
	///	Returns animation length in seconds
	float GetAnimationLength();

	uint8_t GetCurrentFramePlayingID();

	bool IsPlaying();

private:
	std::vector<Frame> m_frames;
	sf::Clock * m_clock;
	//max 255 \
		m_currentFramePlaying has nothing to m_lastFrameID (currentFramePlaying it's counter for vector)
	uint8_t m_currentFramePlayingID;
	bool m_playing;
};

