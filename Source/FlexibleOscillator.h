/*
  ==============================================================================

    FlexibleOscillator.h
    Created: 27 Mar 2025 5:03:13pm
    Author:  Teen Kar Seng

  ==============================================================================
*/

#pragma once
#include <vector>               //for std::vector<float> of samples
#include <cmath>                //for sin() and M_Pi

/**
 flexible oscillator class that allows for an oscillator to change its waveform outputs flexibly
 Call setSampleRate() then setFrequency() before using process every sample
 */

class FlexOsc
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
    
    ///set the Phase Delta manually
    void setPhaseDelta ()
    {
        phaseDelta = frequency / sampleRate;
    }
    
    ///set the mod phase
    void setModPhase (float _modPhase)
    {
        modPhase = _modPhase;
    }
    
    
    ///process - update the phase, wrap the phase and output the sine value of the oscillator
    float process (int waveType)
    {
        //get output of the waveform
        float outputValue = waveformFunction(waveType, phase);
        
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
    virtual float waveformFunction (int waveType, float p)
    {
        if (waveType == 0) //Phasor
        {
            return p;
        }
        
        if (waveType == 1) //Sin
        {
            return sin (modPhase + p * 2 * M_PI);
        }
        
        if (waveType == 2) //Tri
        {
            return (fabs(p - 0.5) - 0.25) * 4.0;
        }
        
        if (waveType == 3) //Square
        {
            if (p > 0.5)
            {
                return - 0.5f;
            }
            else return 0.5f;
        }
    }

    
///setting private variables
private:
    float frequency;
    float sampleRate;
    float phaseDelta;
    float phase = 0.0;
    float modPhase = 0.0;
};


