/*
  ==============================================================================

    PlayOscillator.h
    Created: 9 Apr 2025 11:49:26pm
    Author:  Teen Kar Seng

  ==============================================================================
*/

#pragma once

#ifndef PlayOsc_h
#define PlayOsc_h

#include "Oscillator.h"
#include "FlexibleOscillator.h"

/*
 A class to instantiate the main oscillator of the synth. All functions and parameters MUST be set and connected in their respective areas before synth is usable
 **/
class PlayOsc
{
public:
    
    //Set sample rate. Set in Start Note
    void setSampleRate (float newSampleRate)
    {
        //Main Oscillator
        osc.setSampleRate (newSampleRate);
        
        //Mod Oscillator
        modOsc.setSampleRate (newSampleRate);
        
        //Amplitude ADSR Envelope
        oscAmpEnv.setSampleRate(newSampleRate);
        
        //Frequency ADSR Envelope 
        oscFreqEnv.setSampleRate(newSampleRate);
        
        //Ramp oscillator (Phasor)
        ramp.setSampleRate(newSampleRate);
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
    
    
    //Frequency ADSR parameters. Set in Start Note
    void setFreqAttack (float _FreqAtk)
    {
        oscFreqEnvParams.attack = _FreqAtk;
    }
    
    void setFreqDecay (float _FreqDcy)
    {
        oscFreqEnvParams.decay = _FreqDcy;
    }
    
    void setFreqSustain (float _FreqSus)
    {
        oscFreqEnvParams.sustain = _FreqSus;
    }
    
    void setFreqRelease (float _FreqRel)
    {
        oscFreqEnvParams.release = _FreqRel;
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
    
    //Set to On/Off Oscillator. Set in DSP Loop
    void setOscOnOff (int oscOnOffParam)
    {
        oscOnOff = oscOnOffParam;
    }
    
    //Set to change Osc type. Set in DSP Loop
    void setOscType (int oscTypeParam)
    {
        oscType = oscTypeParam;
    }
    
    //Set to change Gain with slider. Set in DSP Loop
    void setGain (float gainParam)
    {
        gain = gainParam;
    }
    
    //Set frequency of Modulating Oscillator for PM. Set in DSP Loop
    void setModFreq (float modFreqParam)
    {
        modFreq = modFreqParam;
    }
    
    //Set to change Mod Index. Set in DSP Loop
    void setModIndex (float modIndexParam)
    {
        modIndex = modIndexParam;
    }

    //Set the play type of the synth. Set in DSP Loop
    void setPlayType (int playTypeParam)
    {
        playType = playTypeParam;
    }
    
    //Set the play rate. Set in DSP Loop
    void setPlayRate (float playRateParam)
    {
        playRate = playRateParam;
    }
    
    //Set the play range. Set in DSP Loop
    void setPlayRange (int playRangeParam)
    {
        playRange = playRangeParam;
    }
    
    //Set to On/Off Frequency Envelope
    void setFreqEnvOnOff (int freqEnvOnOffParam)
    {
        oscFreqEnvOnOff = freqEnvOnOffParam;
    }
    
    //Set in DSP Loop using the getCurrentlyPlayingNote() function
    void setCurrentNote (int _currentNote)
    {
        currentNote = _currentNote;
    }
    
    //process
    float process()
    {
        //Envelopes get next sample
        float oscAmpEnvVal = oscAmpEnv.getNextSample();
        float oscFreqEnvVal = oscFreqEnv.getNextSample();
        
    //============================================================================================
        //Phase Modulation
        float modProcess = modOsc.process(1); //-1, 1
        float modOut = modProcess * modFreq; //-value, value
        modOut = modOut + 250;
        modOsc.setFrequency (modOut);
               
        float modPhase = modOut * modIndex;
        osc.setModPhase(modPhase);
        
    //============================================================================================
        ramp.setFrequency(playRate);
        
        //Single Note
        if (playType == 0)
         {
             notes.push_back (currentNote);
             }
        // Ascending Chromatic (Rise)
        else if (playType == 1)
         {
             if (playRange + currentNote >= 127)
             {
                 playRange = 127 - currentNote;
             }
             
             for (int i = 0; i < playRange; i++)
             {
             notes.push_back (currentNote + i);
                 }
             }
        
         // Descending Chromatic (Dip)
         else if (playType == 2)
         {
             for (int i = 0; i < playRange; i++)
             {
             notes.push_back (currentNote - i);
                 }
             }
        
         //Ascending Minor Triad
         else if (playType == 3)
         {
             notes.push_back (currentNote);
             notes.push_back (currentNote + 3);
             notes.push_back (currentNote + 7);
             }
        
        //Ascending Major Triad
        else if (playType == 4)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 4);
            notes.push_back (currentNote + 7);
            }
        
        //Ascending Minor 2nd
        else if (playType == 5)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 1);
            }
        
        //Ascending Major 2nd
        else if (playType == 6)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 2);
            }
        
        //Ascending Minor 3rd
        else if (playType == 7)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 3);
            }
        
        //Ascending Major 3rd
        else if (playType == 8)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 4);
            }
        
        //Ascending Perfect 5th
        else if (playType == 9)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 7);
            }
        
        //Descending Perfect 5th
        else if (playType == 10)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote - 7);
            }
        
        //Ascending Octave
        else if (playType == 11)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote + 12);
            }
        
        //Descending Octave
        else if (playType == 12)
        {
            notes.push_back (currentNote);
            notes.push_back (currentNote - 12);
            }
        
        //Ascending Maj Arpeggio
        else if (playType == 13)
        {
            if (playRange + currentNote >= 127)
            {
            playRange = 127 - currentNote;
            }
            
            for (int i = 0; i < playRange; i++)
            {
            notes.push_back (currentNote + (i * 12));
            notes.push_back ((currentNote + 4) + (i * 12));
            notes.push_back ((currentNote + 7) + (i * 12));
                
            if ((currentNote + (i * 12)) >=127)
            {
                i = playRange;
                }
              }
            }
        
        //Descending Maj Arpeggio
        else if (playType == 14)
        {
            for (int i = 0; i < playRange; i++)
            {
            notes.push_back (currentNote - (i * 12));
            notes.push_back ((currentNote - 5) - (i * 12));
            notes.push_back ((currentNote - 8) - (i * 12));
            
            if ((currentNote - (i * 12)) <=0)
                {
                    i = playRange;
                    }
                }
            }
        
        //Ascending Min Arpeggio
        else if (playType == 15)
        {
            for (int i = 0; i < playRange; i++)
            {
            notes.push_back (currentNote + (i * 12));
            notes.push_back ((currentNote + 3) + (i * 12));
            notes.push_back ((currentNote + 7) + (i * 12));
                
            if ((currentNote + (i * 12)) >=127)
                {
                    i = playRange;
                    }
                }
            }
        
        //Descending Min Arpeggio
        else if (playType == 16)
        {
            for (int i = 0; i < playRange; i++)
            {
            notes.push_back (currentNote - (i * 12));
            notes.push_back ((currentNote - 5) - (i * 12));
            notes.push_back ((currentNote - 9) - (i * 12));
            
            if ((currentNote - (i * 12)) <=0)
                {
                    i = playRange;
                    }
                }
            }
 //============================================================================================
        // get phasor output and scale it by the number of notes
         float indexFloat = ramp.process() * notes.size();
        
         // force it to be an integer (stepped)
         int indexInt = floor(indexFloat);
        
         // get the midi note at that index and convert it to frequency in Hz
         int note = notes[indexInt];
         
        float patternFreq = juce::MidiMessage::getMidiNoteInHertz (note);
        if (oscFreqEnvOnOff == 1)
        {
            osc.setFrequency(patternFreq);
        }
        
        
        //apply the frequency to the ADSR envelope
        float oscFreq = patternFreq * oscFreqEnvVal;
        float modFreqEnv = modOut * oscFreqEnvVal;
        if (oscFreqEnvOnOff == 0)
        {
            modOsc.setFrequency (modFreqEnv);
            osc.setFrequency(oscFreq);
        }
        
        float oscOutput;
        
        //When Osc 1 is Off
        if (oscOnOff == 1)
        {
            oscOutput = 0.0;
        }
        
        //When Osc1 is On
        if (oscOnOff == 0)
        {
            oscOutput = osc.process(oscType) * gain * oscAmpEnvVal;
        }
        
        return oscOutput;
    }
    
    
  //called at end of DSP Loop within if statement for isPlaying before clearCurrentNote
    bool isActive ()
    {
       return oscAmpEnv.isActive();
   }
    
    //called at end of DSP Loop when isPlaying == false
    void resetPhase ()
    {
        ramp.resetPhase();
    }
    
    //Called at the end of the DSP Loop to clear notes in the vector
    void clearNotes ()
    {
        notes.clear();
    }
    

private:
    FlexOsc osc;
    FlexOsc modOsc;
    Phasor ramp;
    
    //Osc Amp Envelope
    
    juce::ADSR oscAmpEnv;
    juce::ADSR::Parameters oscAmpEnvParams;
    
    //Osc Freq Envelope
    
    juce::ADSR oscFreqEnv;
    juce::ADSR::Parameters oscFreqEnvParams;
    
    int oscOnOff;
    int oscType;
    float gain;
    
    float modFreq;
    float modIndex;
    
    std::vector<int> notes;     //initialising a vector of notes to be used for patterns
    
    
    int playType;
    float playRate;
    int playRange;
    
    int oscFreqEnvOnOff;
    
    int currentNote;
};


#endif 
