/*
  ==============================================================================

    WhiteNoise.h
    Created: 9 Apr 2025 11:52:54pm
    Author:  Teen Kar Seng

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"

class WhiteNoise
{
    public:
    
    // set in Start Note
    void setSampleRate (float newSampleRate)
    {
        
        //Amplitude ADSR Envelope
        oscAmpEnv.setSampleRate(newSampleRate);

    }
    
    
    //Amplitude ADSR parameters. Set in Start Note
    void setAmpAttack (float _AmpAtk)
    {
        oscAmpEnvParams.attack = _AmpAtk;
    }
    
    void setAmpDecay (float _AmpDcy)
    {
        oscAmpEnvParams.decay = _AmpDcy;
    }
    
    void setAmpSustain (float _AmpSus)
    {
        oscAmpEnvParams.sustain = _AmpSus;
    }
    
    void setAmpRelease (float _AmpRel)
    {
        oscAmpEnvParams.release = _AmpRel;
    }
    
    
    //Set up Envelopes for use. Set in Start Note
    void setEnvOn ()
    {
        //Amplitude ADSR envelope setup
        oscAmpEnv.setParameters (oscAmpEnvParams);
        oscAmpEnv.noteOn();
        
    }
    
    //Set in Stop Note
    void noteOff ()
    {
        oscAmpEnv.noteOff();
    }
    
    //Set in DSP Loop
    void setOscOnOff (int oscOnOffParam)
    {
        oscOnOff = oscOnOffParam;
    }
    
    void setGain(float gainParam)
    {
        gain = gainParam;
    }
                   
    
    float process()
    {
        //Envelopes get next sample
        float oscAmpEnvVal = oscAmpEnv.getNextSample();
        float output;
        
        //When Noise is Off
        if (oscOnOff == 1)
        {
            output = 0.0;
        }
        
        //When Noise is On
        if (oscOnOff == 0)
        {
            output = (rand() / float (RAND_MAX) - 0.5) * oscAmpEnvVal * gain;
        }
        
        return output;
        }
    
    
    //called at end of DSP Loop within if statement for isPlaying before clearCurrentNote
      bool isActive ()
      {
         return oscAmpEnv.isActive();
     }
    
    
    
    
    
    private:
    SinOsc oscNoise;
    juce::ADSR oscAmpEnv;
    juce::ADSR::Parameters oscAmpEnvParams;
    
    float gain;
    int oscOnOff;
};

