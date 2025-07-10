/*
  ==============================================================================

    Synth.h
    Created: 25 Mar 2025 9:40:02pm
    Author:  Teen Kar Seng

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "FlexibleOscillator.h"
#include "PlayOscillator.h"
#include "WhiteNoise.h"
#include "Kick.h"
#include "SFXSampler.h"
#include "Delay.h"

class SynthSound : public juce::SynthesiserSound
{
    public:
    /** Returns true if this sound should be played when a given midi note is pressed.

        The Synthesiser will use this information when deciding which sounds to trigger
        for a given note.
    */
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }

    /** Returns true if the sound should be triggered by midi events on a given channel.

        The Synthesiser will use this information when deciding which sounds to trigger
        for a given note.
    */
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }

};

/// Redefining synthesiser voice for our own sound making code.
class SynthVoice : public juce::SynthesiserVoice
{
    public:
    
    /// connect synthesiser voice parameters to the audio processor value tree state
        void connectParameters (juce::AudioProcessorValueTreeState& apvts)
    {
            //Oscillator 1 parameters
            oscOnOffParam = apvts.getRawParameterValue ("oscOnOff");
            oscTypeParam = apvts.getRawParameterValue ("oscType");
            oscGainParam = apvts.getRawParameterValue ("oscGain");
            
            //Modulating Oscillator 1 parameters
            modOscFreqParam = apvts.getRawParameterValue ("modOscFreq");
            modIndexParam = apvts.getRawParameterValue ("modIndex");

            //Osc 1 Amplitude ADSR parameters
            oscAmpAttackParam = apvts.getRawParameterValue ("oscAmpAttack");
            oscAmpDecayParam = apvts.getRawParameterValue ("oscAmpDecay");
            oscAmpSustainParam = apvts.getRawParameterValue ("oscAmpSustain");
            oscAmpReleaseParam = apvts.getRawParameterValue ("oscAmpRelease");
            
            //Osc 1 Frequency ADSR On/Off parameter
            oscEnvOnOffParam = apvts.getRawParameterValue ("oscEnvOnOff");
            
            //Osc 1 Frequency ADSR parameters
            oscFreqAttackParam = apvts.getRawParameterValue ("oscFreqAttack");
            oscFreqDecayParam = apvts.getRawParameterValue ("oscFreqDecay");
            oscFreqSustainParam = apvts.getRawParameterValue ("oscFreqSustain");
            oscFreqReleaseParam = apvts.getRawParameterValue ("oscFreqRelease");
            
            // Osc 1 Play patterns
            oscPlayTypeParam = apvts.getRawParameterValue ("oscPlayType");
            oscPlayRateParam = apvts.getRawParameterValue ("oscPlayRate");
            oscPlayRangeParam = apvts.getRawParameterValue ("oscPlayRange");
            
//====================================================================================================================================
            
            //Oscillator 2 parameters
            oscOnOffParam2 = apvts.getRawParameterValue ("oscOnOff2");
            oscTypeParam2 = apvts.getRawParameterValue ("oscType2");
            oscGainParam2 = apvts.getRawParameterValue ("oscGain2");
            
            //Modulating Oscillator 2 parameters
            modOscFreqParam2 = apvts.getRawParameterValue ("modOscFreq2");
            modIndexParam2 = apvts.getRawParameterValue ("modIndex2");

            //Osc 2 Amplitude ADSR parameters
            oscAmpAttackParam2 = apvts.getRawParameterValue ("oscAmpAttack2");
            oscAmpDecayParam2 = apvts.getRawParameterValue ("oscAmpDecay2");
            oscAmpSustainParam2 = apvts.getRawParameterValue ("oscAmpSustain2");
            oscAmpReleaseParam2 = apvts.getRawParameterValue ("oscAmpRelease2");
            
            //Osc 2 Frequency ADSR On/Off parameter
            oscEnvOnOffParam2 = apvts.getRawParameterValue ("oscEnvOnOff2");
            
            //Osc 2 Frequency ADSR parameters
            oscFreqAttackParam2 = apvts.getRawParameterValue ("oscFreqAttack2");
            oscFreqDecayParam2 = apvts.getRawParameterValue ("oscFreqDecay2");
            oscFreqSustainParam2 = apvts.getRawParameterValue ("oscFreqSustain2");
            oscFreqReleaseParam2 = apvts.getRawParameterValue ("oscFreqRelease2");
            
            //Osc 2 Play patterns
            oscPlayTypeParam2 = apvts.getRawParameterValue ("oscPlayType2");
            oscPlayRateParam2 = apvts.getRawParameterValue ("oscPlayRate2");
            oscPlayRangeParam2 = apvts.getRawParameterValue ("oscPlayRange2");
            
//====================================================================================================================================
            //Oscillator 3 parameters
            oscOnOffParam3 = apvts.getRawParameterValue ("oscOnOff3");
            oscTypeParam3 = apvts.getRawParameterValue ("oscType3");
            oscGainParam3 = apvts.getRawParameterValue ("oscGain3");
            
            //Modulating Oscillator 3 parameters
            modOscFreqParam3 = apvts.getRawParameterValue ("modOscFreq3");
            modIndexParam3 = apvts.getRawParameterValue ("modIndex3");

            //Osc 3 Amplitude ADSR parameters
            oscAmpAttackParam3 = apvts.getRawParameterValue ("oscAmpAttack3");
            oscAmpDecayParam3 = apvts.getRawParameterValue ("oscAmpDecay3");
            oscAmpSustainParam3 = apvts.getRawParameterValue ("oscAmpSustain3");
            oscAmpReleaseParam3 = apvts.getRawParameterValue ("oscAmpRelease3");
            
            //Osc 3 Frequency ADSR On/Off parameter
            oscEnvOnOffParam3 = apvts.getRawParameterValue ("oscEnvOnOff3");
            
            //Osc 3 Frequency ADSR parameters
            oscFreqAttackParam3 = apvts.getRawParameterValue ("oscFreqAttack3");
            oscFreqDecayParam3 = apvts.getRawParameterValue ("oscFreqDecay3");
            oscFreqSustainParam3 = apvts.getRawParameterValue ("oscFreqSustain3");
            oscFreqReleaseParam3 = apvts.getRawParameterValue ("oscFreqRelease3");
            
            //Osc 3 Play patterns
            oscPlayTypeParam3 = apvts.getRawParameterValue ("oscPlayType3");
            oscPlayRateParam3 = apvts.getRawParameterValue ("oscPlayRate3");
            oscPlayRangeParam3 = apvts.getRawParameterValue ("oscPlayRange3");
            
//====================================================================================================================================
            //White Noise parameters
            noiseOnOffParam = apvts.getRawParameterValue ("noiseOnOff");
            noiseGainParam = apvts.getRawParameterValue ("noiseGain");
            
            //White Noise Amplitude ADSR parameters
            noiseAmpAttackParam = apvts.getRawParameterValue ("noiseAmpAttack");
            noiseAmpDecayParam = apvts.getRawParameterValue ("noiseAmpDecay");
            noiseAmpSustainParam = apvts.getRawParameterValue ("noiseAmpSustain");
            noiseAmpReleaseParam = apvts.getRawParameterValue ("noiseAmpRelease");
            
//====================================================================================================================================
            //Kick parameters
            kickOnOffParam = apvts.getRawParameterValue ("kickOnOff");
            kickGainParam = apvts.getRawParameterValue ("kickGain");
            kickFreqParam = apvts.getRawParameterValue ("kickFreq");
                        
            //Kick Frequency ADSR parameters
            kickFreqDecayParam = apvts.getRawParameterValue ("kickFreqDecay");
            
//====================================================================================================================================
           //Delay parameters
            delayOnOffParam = apvts.getRawParameterValue("delayOnOff");
            
//====================================================================================================================================
            //Amplitude Modulation parameters
            amOscOnOffParam = apvts.getRawParameterValue("amOscOnOff");
            amOscFreqParam = apvts.getRawParameterValue("amOscFreq");
            
//====================================================================================================================================
            //Low pass filter parameters
            lowPassOnOffParam = apvts.getRawParameterValue("lowPassOnOff");
            lowPassCutOffParam = apvts.getRawParameterValue("lowPassCutOff");
            lowPassQParam = apvts.getRawParameterValue("lowPassQ");
            
        }

            
    
    /** Called to start a new note.
        This will be called during the rendering callback, so must be fast and thread-safe.
    */
     void startNote (int midiNoteNumber,
                            float velocity,
                            juce::SynthesiserSound* sound,
                            int currentPitchWheelPosition) override
    {
        
//        DBG ("note started! " << "\n" << midiNoteNumber);
        isPlaying = true;
        
//====================================================================================================================================
        //Osc 1
        
        //Set sample rate for oscillator and envelope
        osc1.setSampleRate (getSampleRate());
        
        //Set ADSR for amplitude envelope
        osc1.setAmpAttack (*oscAmpAttackParam);
        osc1.setAmpDecay (*oscAmpDecayParam);
        osc1.setAmpSustain (*oscAmpSustainParam);
        osc1.setAmpRelease (*oscAmpReleaseParam);
        
        //Set ADSR for frequency envelope
        osc1.setFreqAttack (*oscFreqAttackParam);
        osc1.setFreqDecay (*oscFreqDecayParam);
        osc1.setFreqSustain (*oscFreqSustainParam);
        osc1.setFreqRelease (*oscFreqReleaseParam);
        
        //set parameters to the envelope, note on
        osc1.setEnvOn();
        
        
//====================================================================================================================================
        //Osc 2
        
        //Set sample rate for oscillator and envelope
        osc2.setSampleRate(getSampleRate());
        
        //Set ADSR for amplitude envelope
        osc2.setAmpAttack (*oscAmpAttackParam2);
        osc2.setAmpDecay (*oscAmpDecayParam2);
        osc2.setAmpSustain (*oscAmpSustainParam2);
        osc2.setAmpRelease (*oscAmpReleaseParam2);
        
        //Set ADSR for frequency envelope
        osc2.setFreqAttack (*oscFreqAttackParam2);
        osc2.setFreqDecay (*oscFreqDecayParam2);
        osc2.setFreqSustain (*oscFreqSustainParam2);
        osc2.setFreqRelease (*oscFreqReleaseParam2);
        
        //set parameters to the envelope, note on
        osc2.setEnvOn();
//====================================================================================================================================
        //Osc 3
        
        //Set sample rate for oscillator and envelope
        osc3.setSampleRate(getSampleRate());
        
        //Set ADSR for amplitude envelope
        osc3.setAmpAttack (*oscAmpAttackParam3);
        osc3.setAmpDecay (*oscAmpDecayParam3);
        osc3.setAmpSustain (*oscAmpSustainParam3);
        osc3.setAmpRelease (*oscAmpReleaseParam3);
        
        //Set ADSR for frequency envelope
        osc3.setFreqAttack (*oscFreqAttackParam3);
        osc3.setFreqDecay (*oscFreqDecayParam3);
        osc3.setFreqSustain (*oscFreqSustainParam3);
        osc3.setFreqRelease (*oscFreqReleaseParam3);
        
        //set parameters to the envelope, note on
        osc3.setEnvOn();
//====================================================================================================================================
        //Noise/Click
        //Set sample rate for oscillator and envelope
        click.setSampleRate(getSampleRate());
        
        //Set ADSR for amplitude envelope
        click.setAmpAttack (0.1);
        click.setAmpDecay (0.1);
        click.setAmpSustain (*noiseAmpSustainParam);
        click.setAmpRelease (0.1);
        
        //set parameters to the envelope, note on
        click.setEnvOn();
        
//====================================================================================================================================
        //Kick
        //Set sample rate for oscillator and envelope
        kick.setSampleRate(getSampleRate());
        
        //Set ADSR for amplitude envelope
        kick.setAmpParams();
        
        //Set ADSR for frequency envelope
        kick.setFreqAttack();
        kick.setFreqDecay(*kickFreqDecayParam);
        kick.setFreqSustain();
        kick.setFreqRelease();
                
        //set parameters to the envelope, note on
        kick.setEnvOn();
        
//====================================================================================================================================
        //Delay
        
        delay.setSize(getSampleRate());
        delay.setDelayTimeInSamples(getSampleRate() * 0.5);
        lfo.setSampleRate(getSampleRate());
        lfo.setFrequency(0.5);
        
        //Set sample rate for Amplitude ADSR envelope
        delayEnv.setSampleRate(getSampleRate());
        
        //Set parameters for Amplitude ADSR envelope
        juce::ADSR::Parameters delayEnvParams;
        delayEnvParams.attack = 0.1;
        delayEnvParams.decay = 0.0;
        delayEnvParams.sustain = 1.0;
        delayEnvParams.release = 0.1;
        
        delayEnv.setParameters (delayEnvParams);
        delayEnv.noteOn();

//====================================================================================================================================
        //Amplitude Modulation (AM)
        
        //Set up sample rate for AM
        amOsc.setSampleRate(getSampleRate());
        
//====================================================================================================================================
        //Low Pass Filter
        lowPass.setCoefficients (juce::IIRCoefficients::makeLowPass(getSampleRate(), *lowPassCutOffParam, *lowPassQParam));
        
    }

    /** Called to stop a note.

        This will be called during the rendering callback, so must be fast and thread-safe.

        The velocity indicates how quickly the note was released - 0 is slowly, 1 is quickly.

        If allowTailOff is false or the voice doesn't want to tail-off, then it must stop all
        sound immediately, and must call clearCurrentNote() to reset the state of this voice
        and allow the synth to reassign it another sound.

        If allowTailOff is true and the voice decides to do a tail-off, then it's allowed to
        begin fading out its sound, and it can stop playing until it's finished. As soon as it
        finishes playing (during the rendering callback), it must make sure that it calls
        clearCurrentNote().
    */
    void stopNote (float velocity, bool allowTailOff) override
    {
        //When envelope release has stopped, note is stopped
        osc1.noteOff();
        osc2.noteOff();
        osc3.noteOff();
        click.noteOff();
        kick.noteOff();
        delayEnv.noteOff();
    }
    
    
    
    /** Renders the next block of data for this voice.

        The output audio data must be added to the current contents of the buffer provided.
        Only the region of the buffer between startSample and (startSample + numSamples)
        should be altered by this method.

        If the voice is currently silent, it should just return without doing anything.

        If the sound that the voice is playing finishes during the course of this rendered
        block, it must call clearCurrentNote(), to tell the synthesiser that it has finished.

        The size of the blocks that are rendered can change each time it is called, and may
        involve rendering as little as 1 sample at a time. In between rendering callbacks,
        the voice's methods will be called to tell it about note and controller events.
    */
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                                  int startSample,
                                  int numSamples) override
    {
       if (isPlaying)
       {

           //DSP Loop
           for (int i = startSample; i < startSample + numSamples; i++)
           {
               
        //============================================================================================
               //Osc 1 setup
               
               ///connect parameters within DSP Loop and process
               int osc1OnOff = int (*oscOnOffParam);
               osc1.setOscOnOff(osc1OnOff);
               
               int osc1Type = int (*oscTypeParam);
               osc1.setOscType(osc1Type);
               
               float osc1Gain = *oscGainParam;
               osc1.setGain (osc1Gain);
               
               float osc1ModFreq = *modOscFreqParam;
               osc1.setModFreq(osc1ModFreq);
               
               float osc1modIndex = *modIndexParam;
               osc1.setModIndex(osc1modIndex);
               
               int osc1PlayType = *oscPlayTypeParam;
               osc1.setPlayType(osc1PlayType);
               
               float osc1PlayRate = *oscPlayRateParam;
               osc1.setPlayRate (osc1PlayRate);
               
               int osc1PlayRange = *oscPlayRangeParam;
               osc1.setPlayRange(osc1PlayRange);
               
               int osc1FreqEnvOnOff = *oscEnvOnOffParam;
               osc1.setFreqEnvOnOff (osc1FreqEnvOnOff);
               
               int currentNote = getCurrentlyPlayingNote();
               osc1.setCurrentNote(currentNote);
               
               float osc1Output = osc1.process();
               
               
        //============================================================================================
               //Osc 2 setup
               
               ///connect parameters within DSP Loop and process
               int osc2OnOff = int (*oscOnOffParam2);
               osc2.setOscOnOff (osc2OnOff);
               
               int osc2Type = int (*oscTypeParam2);
               osc2.setOscType (osc2Type);
               
               float osc2Gain = *oscGainParam2;
               osc2.setGain (osc2Gain);
               
               float osc2ModFreq = *modOscFreqParam2;
               osc2.setModFreq (osc2ModFreq);
               
               float osc2modIndex = *modIndexParam2;
               osc2.setModIndex(osc2modIndex);
               
               int osc2PlayType = *oscPlayTypeParam2;
               osc2.setPlayType (osc2PlayType);
               
               float osc2PlayRate = *oscPlayRateParam2;
               osc2.setPlayRate (osc2PlayRate);
               
               int osc2PlayRange = *oscPlayRangeParam2;
               osc2.setPlayRange(osc2PlayRange);
               
               int osc2FreqEnvOnOff = *oscEnvOnOffParam2;
               osc2.setFreqEnvOnOff (osc2FreqEnvOnOff);
               
               osc2.setCurrentNote(currentNote);
               
               float osc2Output = osc2.process();
    //============================================================================================
               //Osc 3 setup
               
               ///connect parameters within DSP Loop and process
               int osc3OnOff = int (*oscOnOffParam3);
               osc3.setOscOnOff (osc3OnOff);
               
               int osc3Type = int (*oscTypeParam3);
               osc3.setOscType (osc3Type);
               
               float osc3Gain = *oscGainParam3;
               osc3.setGain (osc3Gain);
               
               float osc3ModFreq = *modOscFreqParam3;
               osc3.setModFreq (osc3ModFreq);
               
               float osc3modIndex = *modIndexParam3;
               osc3.setModIndex(osc3modIndex);
               
               int osc3PlayType = *oscPlayTypeParam3;
               osc3.setPlayType (osc3PlayType);
               
               float osc3PlayRate = *oscPlayRateParam3;
               osc3.setPlayRate (osc3PlayRate);
               
               int osc3PlayRange = *oscPlayRangeParam3;
               osc3.setPlayRange(osc3PlayRange);
               
               int osc3FreqEnvOnOff = *oscEnvOnOffParam3;
               osc3.setFreqEnvOnOff (osc3FreqEnvOnOff);
               
               osc3.setCurrentNote(currentNote);
               
               float osc3Output = osc3.process();
               
    //============================================================================================
               //Click setup
               
               ///connect parameters within DSP Loop and process
               int clickOnOff = int (*noiseOnOffParam);
               click.setOscOnOff(clickOnOff);
               
               float clickGain = *noiseGainParam;
               click.setGain (clickGain);
               
               float clickOutput = click.process();
               
    //============================================================================================
                //Kick setup
                   
               ///connect parameters within DSP Loop and process
               int kickOnOff = int (*kickOnOffParam);
               kick.setOscOnOff(kickOnOff);
                          
               float kickGain = *kickGainParam;
               kick.setGain (kickGain);
               
               float kickFreq = *kickFreqParam;
               kick.setFrequency(kickFreq);
                          
               float kickOutput = kick.process();
                          
               
    //============================================================================================
               //Delay setup
               float delayEnvVal = delayEnv.getNextSample();
//               float lfoVal = lfo.process(); //+- 1
//               float delayTimeInSamples = (lfoVal * 500) + 600;
//               delay.setDelayTimeInSamples(delayTimeInSamples);
    //============================================================================================
               //Amplitude Modulation (AM) setup
               
               ///connect parameters within DSP Loop
               float amOscFreq = *amOscFreqParam;
               amOsc.setFrequency (amOscFreq);
               
    //============================================================================================
               //Preparing output sample to be played
               
               //additive synthesis of all output
               float allOutput = (osc1Output + osc2Output + osc3Output + clickOutput + kickOutput) / 5;
               
              //if AM is on, AM is applied onto the sample to play
               int amOscOnOff = int (*amOscOnOffParam);
               
               if (amOscOnOff == 0)
               {
                   allOutput = allOutput * amOsc.process();
               }
               
               //if delay is on, delay is applied onto the sample to play
               float delaySample = delay.process(allOutput) * delayEnvVal;
               int delayOnOff = int (*delayOnOffParam);
            
               if (delayOnOff == 0)
               {
                   allOutput = delaySample;
               }
               
               
               //if LPF is on, LPF is applied to sample to play
               int lowPassOnOff = int (*lowPassOnOffParam);
               
               if (lowPassOnOff == 0)
               {
                   allOutput = lowPass.processSingleSampleRaw(allOutput);
               }
               
               float sampleToPlay = allOutput;
        
               //work through each channel (c for channel)
               for (int c = 0; c <outputBuffer.getNumChannels(); c++)
               {
                   outputBuffer.addSample (c, i, sampleToPlay);
               }
               
               
               
               // has the envelope finished?
               // if so, turn off DSP and clear voice
               
               if (! osc1.isActive() && ! osc2.isActive() && ! osc3.isActive() && ! click.isActive() && ! kick.isActive() && ! delayEnv.isActive())
               {
                   isPlaying = false;
                   clearCurrentNote();
               }
               
               if (isPlaying == false)
               {
                   
                   osc1.resetPhase();
                   
                   osc2.resetPhase();
                   
                   osc3.resetPhase();
                   
               }

               osc1.clearNotes();
               osc2.clearNotes();
               osc3.clearNotes();
            
               
           }
           
       }
        
    }
    
    
    
   
    /** Must return true if this voice object is capable of playing the given sound.

        If there are different classes of sound, and different classes of voice, a voice can
        choose which ones it wants to take on.

        A typical implementation of this method may just return true if there's only one type
        of voice and sound, or it might check the type of the sound object passed-in and
        see if it's one that it understands.
    */
     bool canPlaySound (juce::SynthesiserSound*) override
    {
        return true;
    }
    
    /** Called to let the voice know that the pitch wheel has been moved.
        This will be called during the rendering callback, so must be fast and thread-safe.
    */
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        
    }

    /** Called to let the voice know that a midi controller has been moved.
        This will be called during the rendering callback, so must be fast and thread-safe.
    */
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    
    private:
        
    bool isPlaying = false;
    
//====================================================================================================================================
    
    //Osc 1
    PlayOsc osc1;
    
    //Osc 1 PM params
    std::atomic<float>* modOscFreqParam;
    std::atomic<float>* modIndexParam;
    
    //Osc 1 On/Off param
    std::atomic<float>* oscOnOffParam;
    
    //Osc 1 Wave Type Param
    std::atomic<float>* oscTypeParam;
    
    //Osc 1 Gain Param
    std::atomic<float>* oscGainParam;
    
    //Osc 1 Amplitude Envelope param
    std::atomic<float>* oscAmpAttackParam;
    std::atomic<float>* oscAmpDecayParam;
    std::atomic<float>* oscAmpSustainParam;
    std::atomic<float>* oscAmpReleaseParam;
    
    //Osc 1 Frequency ADSR Envelope On/Off param
    std::atomic<float>* oscEnvOnOffParam;
    
    //Osc 1 Frequency Envelope param
    std::atomic<float>* oscFreqAttackParam;
    std::atomic<float>* oscFreqDecayParam;
    std::atomic<float>* oscFreqSustainParam;
    std::atomic<float>* oscFreqReleaseParam;
    
    //Osc 1 Play Pattern Options
    std::atomic <float>* oscPlayTypeParam;
    std::atomic <float>* oscPlayRateParam;
    std::atomic <float>* oscPlayRangeParam;
//====================================================================================================================================
    
    // Osc 2
    PlayOsc osc2;
    
    //Osc 2 PM params
    std::atomic<float>* modOscFreqParam2;
    std::atomic<float>* modIndexParam2;
    
    //Osc 2 On/Off
    std::atomic<float>* oscOnOffParam2;
    
    //Osc 2 Wave Type Params
    std::atomic<float>* oscTypeParam2;
    
    //Osc 2 Gain param
    std::atomic<float>* oscGainParam2;
    
    //Osc 2 Amplitude Envelope
    std::atomic<float>* oscAmpAttackParam2;
    std::atomic<float>* oscAmpDecayParam2;
    std::atomic<float>* oscAmpSustainParam2;
    std::atomic<float>* oscAmpReleaseParam2;
    
    //Osc 2 Frequency ADSR Envelope On/Off param
    std::atomic<float>* oscEnvOnOffParam2;
    
    //Osc 2 Frequency Envelope
    std::atomic<float>* oscFreqAttackParam2;
    std::atomic<float>* oscFreqDecayParam2;
    std::atomic<float>* oscFreqSustainParam2;
    std::atomic<float>* oscFreqReleaseParam2;
    
    //Osc 2 Play Pattern Options
    std::atomic <float>* oscPlayTypeParam2;
    std::atomic <float>* oscPlayRateParam2;
    std::atomic <float>* oscPlayRangeParam2;
    
//====================================================================================================================================
    // Osc 3
    PlayOsc osc3;
    
    //Osc 3 params
    std::atomic<float>* modOscFreqParam3;
    std::atomic<float>* modIndexParam3;
    
    //Osc 3 On/Off
    std::atomic<float>* oscOnOffParam3;
    
    //Osc 3 Wave Type Params
    std::atomic<float>* oscTypeParam3;
    
    //Osc 3 Gain param
    std::atomic<float>* oscGainParam3;
    
    //Osc 3 Amplitude Envelope
    std::atomic<float>* oscAmpAttackParam3;
    std::atomic<float>* oscAmpDecayParam3;
    std::atomic<float>* oscAmpSustainParam3;
    std::atomic<float>* oscAmpReleaseParam3;
    
    //Osc 3 Frequency ADSR Envelope On/Off param
    std::atomic<float>* oscEnvOnOffParam3;
    
    //Osc 3 Frequency Envelope
    std::atomic<float>* oscFreqAttackParam3;
    std::atomic<float>* oscFreqDecayParam3;
    std::atomic<float>* oscFreqSustainParam3;
    std::atomic<float>* oscFreqReleaseParam3;
    
    //Osc 3 Play Pattern Options
    std::atomic <float>* oscPlayTypeParam3;
    std::atomic <float>* oscPlayRateParam3;
    std::atomic <float>* oscPlayRangeParam3;
    
    
//====================================================================================================================================
    
    //White Noise
    WhiteNoise click;
    
    //Noise On/Off
    std::atomic<float>* noiseOnOffParam;
    
    //Noise Gain param
    std::atomic<float>* noiseGainParam;
    
    //Noise Amplitude Envelope
    std::atomic<float>* noiseAmpAttackParam;
    std::atomic<float>* noiseAmpDecayParam;
    std::atomic<float>* noiseAmpSustainParam;
    std::atomic<float>* noiseAmpReleaseParam;
    
//====================================================================================================================================
    
    //Kick
    Kick kick;
    
    //On/Off
    std::atomic<float>* kickOnOffParam;
    
    //Kick Gain param
    std::atomic<float>* kickGainParam;
    
    //Kick Freq param
    std::atomic<float>* kickFreqParam;
    
    //Kick Freq Envelope
    std::atomic<float>* kickFreqDecayParam;
    
//====================================================================================================================================

    //Delay
    Delay delay;
    SinOsc lfo;
    
    //Delay Amplitude Envelope
    std::atomic<float>* delayOnOffParam;
    juce::ADSR delayEnv;

//====================================================================================================================================
    //Amplitude Modulation
    SinOsc amOsc;
    
    //AM On/Off parameter
    std::atomic<float>* amOscOnOffParam;
    
    //AM Frequency parameter
    std::atomic<float>* amOscFreqParam;
    
//====================================================================================================================================
    //Filter
    juce::IIRFilter lowPass;
    std::atomic<float>* lowPassOnOffParam;
    std::atomic<float>* lowPassCutOffParam;
    std::atomic<float>* lowPassQParam;
    
};
