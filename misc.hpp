#pragma once

#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

vector<sf::Int16> float_to_int16(vector<float> num)
{
    vector<sf::Int16> res;
    
    for(size_t i=0; i < num.size(); i++)
    {
        res.push_back(num[i] * 32767);
    }
    return res;
}

vector<float> get_phasor(float freq,  float phase, float sample_rate, size_t samples)
{
    vector<float> out;
    float sample_time = 1.f/sample_rate;
    float phase_increment = freq * sample_time;
    
    for (size_t i = 0; i < samples; i++)
    {
        out.push_back(phase);
        phase = fmod((phase + phase_increment), 1.0);
    }
    
    return out;
    
}
