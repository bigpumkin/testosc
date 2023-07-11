#include "misc.hpp"

class Oscillator
{
 
  public:
	//Oscillator();
	
	float note_freq;
	
	vector<float> phase;
	float last_phase;
	
	void process(float sample_rate);
	
};

void Oscillator::process(float sample_rate) 
{
    this->phase = get_phasor(440, 0, 44100, 50000);
    this->last_phase = this->phase[phase.size()];   
           
        for(size_t i=0; i<this->phase.size(); i++)
        {
            this->phase[i] *= 2;
            this->phase[i] *= M_PI;
        }
}
