/*
  ==============================================================================

    Kick.h
    Created: 11 Apr 2025 10:23:01am
    Author:  Teen Kar Seng

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "FlexibleOscillator.h"

class Kick
{
    public:
    
    // set in Start Note
    void setSampleRate (float newSampleRate)
    {
        //Main Oscillator
        osc.setSampleRate (newSampleRate);
        
        //Amplitude ADSR Envelope
        oscAmpEnv.setSampleRate(newSampleRate);
        
        //Frequency ADSR Envelope
        oscFreqEnv.setSampleRate(newSampleRate);
    }
    
    //Set frequency inside DSP Loop
    void setFrequency (float _frequency)
    {
        freq = _frequency;
        osc.setFrequency (freq);
    }

    
    //Sets ALL Amplitude ADSR parameters. Set in Start Note
    void setAmpParams ()
    {
        setAmpAttack();
        setAmpDecay();
        setAmpSustain();
        setAmpRelease();
    }
    
    //Amplitude ADSR parameters. Set in Start Note
    void setAmpAttack ()
    {
        oscAmpEnvParams.attack = 0.1;
    }
    
    void setAmpDecay ()
    {
        oscAmpEnvParams.decay = 0.1;
    }
    
    void setAmpSustain ()
    {
        oscAmpEnvParams.sustain = 1.0;
    }
    
    void setAmpRelease ()
    {
        oscAmpEnvParams.release = 0.1;
    }
    
    
    //Frequency ADSR parameters. Set in Start Note
    void setFreqAttack ()
    {
        oscFreqEnvParams.attack = 0.01;
    }
    
    void setFreqDecay (float _FreqDcy)
    {
        oscFreqEnvParams.decay = _FreqDcy;
    }
    
    void setFreqSustain ()
    {
        oscFreqEnvParams.sustain = 0.0f;
    }
    
    void setFreqRelease ()
    {
        oscFreqEnvParams.release = 0.01;
    }
    
    
    //Set up Envelopes for use. Set in Start Note
    void setEnvOn ()
    {
        //Amplitude ADSR envelope setup
        oscAmpEnv.setParameters (oscAmpEnvParams);
        oscAmpEnv.noteOn();
        
        //Frequency ADSR envelope setup
        oscFreqEnv.setParameters (oscFreqEnvParams);
        oscFreqEnv.noteOn();
    }
    
    //Set in Stop Note
    void noteOff ()
    {
        oscAmpEnv.noteOff();
        oscFreqEnv.noteOff();
    }
    
    //Set in DSP Loop
    void setOscOnOff (int oscOnOffParam)
    {
        oscOnOff = oscOnOffParam;
    }
    
    //Set in DSP Loop
    void setGain (float gainParam)
    {
        gain = gainParam;
    }
    
    float process()
    {
        //Envelopes get next sample
        float oscAmpEnvVal = oscAmpEnv.getNextSample();
        float oscFreqEnvVal = oscFreqEnv.getNextSample();

        float oscFreq = freq * oscFreqEnvVal;
        osc.setFrequency (oscFreq);
        
        float oscOutput;
        
        //When Osc 1 is Off
        if (oscOnOff == 1)
        {
            oscOutput = 0.0;
        }
        
        //When Osc1 is On
        if (oscOnOff == 0)
        {
            oscOutput = osc.process(1) * gain * oscAmpEnvVal;
        }
        
        return oscOutput;

    }
    
    //called at end of DSP Loop within if statement for isPlaying before clearCurrentNote
      bool isActive ()
      {
         return oscAmpEnv.isActive();
     }
    
    private:
    FlexOsc osc;
    
    //Osc Amp Envelope
    
    juce::ADSR oscAmpEnv;
    juce::ADSR::Parameters oscAmpEnvParams;
    
    //Osc Freq Envelope
    
    juce::ADSR oscFreqEnv;
    juce::ADSR::Parameters oscFreqEnvParams;
    
    int oscOnOff;
    float gain;
    float freq;
};
