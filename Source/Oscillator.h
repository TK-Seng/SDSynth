//
//  Oscillator.h
//
//
//
//

#ifndef Oscillator_h
#define Oscillator_h

///Libraries to include with Oscillator Header file
//#include <iostream>
#include <vector>               //for std::vector<float> of samples
#include <cmath>                //for sin() and M_Pi
//#include "MattsAudioHeader.h"   //for writeToWav


/**
 phasor class
 ramps from 0-1
 Call setSampleRate() then setFrequency() before using process every sample
 */

class Phasor
{
public:
    ///set frequency in Hz
    void setFrequency(float _frequency)
    {
        frequency = _frequency;
        setPhaseDelta();
    }
    
    ///get frequency value in Hz
    float getFrequency()
    {
        float _frequency = frequency;
        return _frequency;
    }
    
    ///set the sample rate
    void setSampleRate(float _sampleRate)
    {
        sampleRate = _sampleRate;
        setPhaseDelta();
    }
    
    ///get the sample rate
    float getSampleRate()
    {
        return sampleRate;
    }
    
    void resetPhase ()
    {
        phase = 0.0;
    }
    
    ///set the Phase Delta manually
    void setPhaseDelta ()
    {
        phaseDelta = frequency / sampleRate;
    }
    
    ///process - update the phase, wrap the phase and output the sine value of the oscillator
    float process ()
    {
        //get output of the waveform
        float outputValue = waveformFunction(phase);
        
        //increment our phase
        phase += phaseDelta;
        
        //wrap our phase
        if (phase > 1.0)
        {
            phase -= 1.0;
        }
        // output sine
        return outputValue;
        
    }
    
    
    ///gives inherited class flexibility to change the output waveform (i.e. Sine, Triangle, Square etc.)
    virtual float waveformFunction (float p)
    {
        return p;
    }

    
///setting private variables
private:
    float frequency;
    float sampleRate;
    float phaseDelta;
    float phase = 0.0;
    float modPhase = 0.0;
};


///Sine Oscillator class building on top of Phasor base class
class SinOsc : public Phasor
{
public:
    float waveformFunction(float p) override
    {
        return sin (p * 2 * M_PI);  // formula for Sine Oscillator
    }
};


///Triangle Oscillator class building on top of Phasor base class
class TriOsc : public Phasor
{
public:
    float waveformFunction(float p) override
    {
        return (fabs(p - 0.5) - 0.25) * 4.0; // formula for Triangle Oscillator
    }
};


///Square Oscillator class building on top of Phasor base class
class SquareOsc : public Phasor
{
public:
    float waveformFunction(float p) override
    {
        if (p > 0.5)                // formula for Square Oscillator
        {
            return - 0.5f;
        }
        else return 0.5f;
    }
};

///Sine Oscillator class that can use phase modulation, building on top of Phasor class
class SinModOsc : public Phasor
{
public:
    float waveformFunction(float p) override
    {
        return sin (modPhase + p * 2 * M_PI); // formula for Sine Oscillator with modulation
    }
    
    void setModPhase (float _modPhase)
    {
        modPhase = _modPhase;
    }
    
private:
    float modPhase = 0.0;
};


#endif /* Oscillator_h */
