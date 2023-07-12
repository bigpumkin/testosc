#include <SFML/Audio.hpp>
#include <vector>

#include "osc.hpp"
#include "misc.hpp"

using namespace std;

// custom audio stream that plays a loaded buffer


class MyStream : public sf::SoundStream
{

    public:
    MyStream() {
        initialize(1, 44100);
    }
    
private:
    
    vector<sf::Int16> fl_m_samples;
    
    Oscillator osc;
    virtual bool onGetData(Chunk& data)
    {
        // number of samples to stream every time the function is called;
        // in a more robust implementation, it should be a fixed
        // amount of time rather than an arbitrary number of samples
        osc.process(44100);      
        const int samplesToStream = 50000;
        
        data.sampleCount = samplesToStream;
        
        // set the pointer to the next audio samples to be played
        m_samples.clear();
        
        for(size_t i=0; i<=samplesToStream; i++)
        {
            m_samples.push_back(sin(osc.phase[i]));
        }        
        
        fl_m_samples = float_to_int16(m_samples);
        
        data.samples = fl_m_samples.data();

           return true;
    }

    virtual void onSeek(sf::Time timeOffset)
    {
        // compute the corresponding sample index according to the sample rate and channel count
        m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
    }

    std::vector<float> m_samples;
    std::size_t m_currentSample;
    
};

int main()
{
    // load an audio buffer from a sound file
    sf::SoundBuffer buffer;
    
    // initialize and play our custom stream
    MyStream stream;
   
    stream.play();

    // let it play until it is finished
    while (stream.getStatus() == MyStream::Playing)
        sf::sleep(sf::seconds(0.1f));

    return 0;
}
