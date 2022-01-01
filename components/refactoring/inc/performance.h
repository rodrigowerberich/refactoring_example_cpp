#pragma once

namespace TheaterBilling
{

class Performance{
public:
    Performance(): m_playId{""}, m_audience{-1}{}
    Performance(std::string _playId, int _audience): m_playId{_playId}, m_audience{_audience}{}
    const std::string & playId() const { return m_playId; }
    int audience() const { return m_audience; }

private:
    std::string m_playId;
    int m_audience;
};

} // namespace TheaterBilling