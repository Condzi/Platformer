#include "Animator.hpp"


void Animator::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_frames[m_currentFramePlayingID], states);
}

Animator::Animator()
{
	m_clock = nullptr;
}


Animator::~Animator()
{
	if (m_clock != nullptr)
		delete m_clock;
}

bool Animator::Start()
{
	if (m_frames.size() == 0)
		return false;

	if (m_clock != nullptr)
		delete m_clock;

	m_clock = new sf::Clock;
	m_playing = true;

	m_clock->restart();
	return true;
}

bool Animator::Update()
{
	if (!m_playing)
		return false;
		//This may cause the last frame didn't show
	if (m_currentFramePlayingID >= m_frames.size() - 1)
	{
		Stop();
		return true;
	}

	float eleapsedFramesTime = 0.f;
		
	for (uint16_t i = 0; i < m_currentFramePlayingID; ++i)
	{
		eleapsedFramesTime += m_frames[i].duration;
	}
	
	if (m_clock->getElapsedTime().asSeconds() > eleapsedFramesTime + m_frames[m_currentFramePlayingID].duration)
	{
		m_currentFramePlayingID++;
	}

	return true;
}

void Animator::Stop()
{
	delete m_clock;
	m_clock = nullptr;

	m_currentFramePlayingID = 0;

	m_playing = false;
}

bool Animator::AddFrame(const Frame & frame)
{
	if (m_frames.size() > std::numeric_limits<uint8_t>::max())
		return false;

	m_frames.push_back(frame);

	return true;
}

bool Animator::DelFrame(const uint8_t & id)
{
	if (id > m_frames.size() || id < 0)
		return false;

	m_frames.erase(m_frames.begin(), m_frames.begin() + id);
	
	return true;
}

bool Animator::DelCurrentFrame()
{
	if (!m_playing)
		return false;

	m_frames.erase(m_frames.begin(), m_frames.begin() + m_currentFramePlayingID);

	return true;
}

Frame Animator::GetFrame(const uint8_t & id)
{
	if (id > m_frames.size() || id < 0)
		return Frame();

	return m_frames[id];
}

Frame Animator::GetCurrentFrame()
{
	return m_frames[m_currentFramePlayingID];
}

float Animator::GetAnimationLength()
{
	float final = 0.f;

	for (Frame var : m_frames)
	{
		final += var.duration;
	}

	return final;
}

uint8_t Animator::GetCurrentFramePlayingID()
{
	return m_currentFramePlayingID;
}

bool Animator::IsPlaying()
{
	return m_playing;
}
