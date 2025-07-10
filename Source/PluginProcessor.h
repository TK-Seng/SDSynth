/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth.h"
#include "FlexibleOscillator.h"
#include "Oscillator.h"
#include "SFXSampler.h"
#include "mySamplerVoice.h"
#include "Delay.h"
//==============================================================================
/**
*/
class AP_3AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AP_3AudioProcessor();
    ~AP_3AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    ///use of shorthand
    using APVTS = juce::AudioProcessorValueTreeState;

    ///initialise apvts
    APVTS apvts;
    
    /// setup our parameters
    APVTS::ParameterLayout createParameterLayout()
    {
        APVTS::ParameterLayout layout;
        
        // id, name, min, max, default
        
//====================================================================================================================================
        //Osc 1 Parameters
        
        //Osc 1 On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscOnOff", 1), "Osc 1", juce::StringArray({"On", "Off" }), 0));
        
        //Osc 1 Wave Type
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscType", 1), "Osc1 Type", juce::StringArray({"Phasor", "Sine", "Triangle", "Square" }), 1));
        
       //Osc 1 Gain
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscGain", 1), "Osc1 Gain", 0.0, 1.0, 0.5));
        

        //Osc 1 Amplitude ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpAttack", 1), "Osc1 Amp Attack", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpDecay", 1), "Osc1 Amp Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpSustain", 1), "Osc1 Amp Sustain", 0.0, 1.0, 0.5));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpRelease", 1), "Osc1 Amp Release", 0.0, 1.0, 0.1));
        
        
        //Osc 1 Frequency ADSR envelope On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscEnvOnOff", 1), "Osc1 Frequency ADSR", juce::StringArray({"On", "Off"}), 1));
        
        //Osc 1 Frequency ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqAttack", 1), "Osc1 Freq Attack", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqDecay", 1), "Osc1 Freq Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqSustain", 1), "Osc1 Freq Sustain", 0.0, 1.0, 0.5));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqRelease", 1), "Osc1 Freq Release", 0.0, 1.0, 0.1));
        
        
        //Osc 1 Play Patterns
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscPlayType", 1), "Osc1 Play Type", juce::StringArray({"Single Note", "Rise", "Dip", "Min Triad", "Maj Triad", "Min 2nd", "Maj 2nd", "Min 3rd", "Maj 3rd", "Perf 5th (Up)", "Perf 5th (Down)", "Octave (Up)","Octave (Down)", "Maj Arp (Up)", "Maj Arp (Down)", "Min Arp (Up)", "Min Arp (Down)" }), 0));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscPlayRate", 1), "Osc1 Play Rate", 0.0, 10.0, 0.25));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscPlayRange", 1), "Osc1 Play Range", 1.0, 100.0, 10));
        
        
        //Osc 1 Modulating Oscillator Parameters
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("modOscFreq", 1), "Osc1 PM Frequency", 1.0, 100, 45));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("modIndex", 1), "Osc1 Mod Index", 0.0, 5.0, 0.0));
        
//====================================================================================================================================
        //Osc 2 Parameters
        
        //Osc 2 On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscOnOff2", 1), "Osc 2", juce::StringArray({"On", "Off" }), 1));
        
        //Osc 2 Wave Type
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscType2", 1), "Osc2 Type", juce::StringArray({"Phasor", "Sine", "Triangle", "Square" }), 1));
        
       //Osc 2 Gain
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscGain2", 1), "Osc2 Gain", 0.0, 1.0, 0.5));
        

        //Osc 2 Amplitude ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpAttack2", 1), "Osc2 Amp Attack", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpDecay2", 1), "Osc2 Amp Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpSustain2", 1), "Osc2 Amp Sustain", 0.0, 1.0, 0.5));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpRelease2", 1), "Osc2 Amp Release", 0.0, 1.0, 0.1));
        
        
        //Osc 2 Frequency ADSR envelope On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscEnvOnOff2", 1), "Osc2 Frequency ADSR", juce::StringArray({"On", "Off"}), 1));
        
        //Osc 2 Frequency ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqAttack2", 1), "Osc2 Freq Attack", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqDecay2", 1), "Osc2 Freq Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqSustain2", 1), "Osc2 Freq Sustain", 0.0, 1.0, 0.5));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqRelease2", 1), "Osc2 Freq Release", 0.0, 1.0, 0.1));
        
        
        //Osc 2 Play Patterns
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscPlayType2", 1), "Osc2 Play Type", juce::StringArray({"Single Note", "Rise", "Dip", "Min Triad", "Maj Triad", "Min 2nd", "Maj 2nd", "Min 3rd", "Maj 3rd", "Perf 5th (Up)", "Perf 5th (Down)", "Octave (Up)","Octave (Down)", "Maj Arp (Up)", "Maj Arp (Down)", "Min Arp (Up)", "Min Arp (Down)" }), 0));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscPlayRate2", 1), "Osc2 Play Rate", 0.0, 10.0, 0.25));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscPlayRange2", 1), "Osc2 Play Range", 1.0, 100.0, 10));
        
        
        //Osc 2 Modulating Oscillator Parameters
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("modOscFreq2", 1), "Osc2 PM Frequency", 1.0, 100, 45));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("modIndex2", 1), "Osc2 Mod Index", 0.0, 5.0, 0.0));
        
//====================================================================================================================================
        //Osc 3 Parameters
        
        //Osc 3 On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscOnOff3", 1), "Osc 3", juce::StringArray({"On", "Off" }), 1));
        
        //Osc 3 Wave Type
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscType3", 1), "Osc3 Type", juce::StringArray({"Phasor", "Sine", "Triangle", "Square" }), 1));
        
       //Osc 3 Gain
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscGain3", 1), "Osc3 Gain", 0.0, 1.0, 0.5));
        

        //Osc 3 Amplitude ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpAttack3", 1), "Osc3 Amp Attack", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpDecay3", 1), "Osc3 Amp Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpSustain3", 1), "Osc3 Amp Sustain", 0.0, 1.0, 0.5));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscAmpRelease3", 1), "Osc3 Amp Release", 0.0, 1.0, 0.1));
        
        
        //Osc 3 Frequency ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscEnvOnOff3", 1), "Osc3 Frequency ADSR", juce::StringArray({"On", "Off"}), 1));
        
        //Osc 3 Frequency ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqAttack3", 1), "Osc3 Freq Attack", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqDecay3", 1), "Osc3 Freq Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqSustain3", 1), "Osc3 Freq Sustain", 0.0, 1.0, 0.5));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscFreqRelease3", 1), "Osc3 Freq Release", 0.0, 1.0, 0.1));
        
        
        //Osc 3 Play Patterns
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("oscPlayType3", 1), "Osc3 Play Type", juce::StringArray({"Single Note", "Rise", "Dip", "Min Triad", "Maj Triad", "Min 2nd", "Maj 2nd", "Min 3rd", "Maj 3rd", "Perf 5th (Up)", "Perf 5th (Down)", "Octave (Up)","Octave (Down)", "Maj Arp (Up)", "Maj Arp (Down)", "Min Arp (Up)", "Min Arp (Down)" }), 0));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscPlayRate3", 1), "Osc3 Play Rate", 0.0, 10.0, 0.25));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("oscPlayRange3", 1), "Osc3 Play Range", 1.0, 100.0, 10));
        
        
        //Osc 3 Modulating Oscillator Parameters
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("modOscFreq3", 1), "Osc3 PM Frequency", 1.0, 100, 45));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("modIndex3", 1), "Osc3 Mod Index", 0.0, 5.0, 0.0));
        
//====================================================================================================================================
        //Noise Parameters
        
        //Noise On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("noiseOnOff", 1), "Noise", juce::StringArray({"On", "Off" }), 1));
        
        //Noise Gain
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("noiseGain", 1), "Noise Gain", 0.0, 1.0, 0.5));
        
        //Noise Amplitude ADSR envelope
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("noiseAmpAttack", 1), "Noise Amp Attack", 0.0, 1.0, 0.1));
       
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("noiseAmpDecay", 1), "Noise Amp Decay", 0.0, 1.0, 0.1));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("noiseAmpSustain", 1), "Noise Amp Sustain", 0.0, 1.0, 1.0));
        
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("noiseAmpRelease", 1), "Noise Amp Release", 0.0, 1.0, 0.1));

//====================================================================================================================================
        //Kick Parameters
        
        //Kick On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("kickOnOff", 1), "Kick", juce::StringArray({"On", "Off" }), 1));
                
                
        //Kick Gain
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("kickGain", 1), "Kick Gain", 0.0, 1.0, 0.8));
    
        //Kick Frequency
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("kickFreq", 1), "Kick Freq", 0.0, 1000.0, 200));
                
        //Kick Frequency ADSR envelope

        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("kickFreqDecay", 1), "Kick Freq Decay", 0.0, 1.0, 0.1));
//====================================================================================================================================
        //Delay Parameters
        
        //Delay On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("delayOnOff", 1), "Delay", juce::StringArray({"On", "Off" }), 1));
        
//====================================================================================================================================
        //Reverb Parameters
        
        //Reverb On/Off
            layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("reverbOnOff", 1), "Reverb", juce::StringArray({"On", "Off" }), 1));
//====================================================================================================================================
        //Amplitude Modulation (AM) Parameters
        
        //AM On/Off
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("amOscOnOff", 1), "AM", juce::StringArray({"On", "Off" }), 1));
        
        //AM oscillator frequency
        layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("amOscFreq", 1), "AM Freq", 0.1, 10.0, 0.5));
        
//====================================================================================================================================
        //Low Pass Filter (LPF) Parameters
        
        layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("lowPassOnOff", 1), "LPF", juce::StringArray({"On", "Off" }), 1));
        //LPF frequency cutoff
         layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("lowPassCutOff", 1), "LPF Cutoff", 100, 3000, 300));
        
        //LPF Q
         layout.add ( std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("lowPassQ", 1), "LPF Q", 0.0, 10, 0.5));
        
//====================================================================================================================================
    //Sampler
        
    //Sample Choice
    layout.add ( std::make_unique<juce::AudioParameterChoice> (juce::ParameterID("sampleChoice", 1), "Sampler", juce::StringArray({"No Samples","Metal Dink", "Wood Knock", "Bubble Bloop"}), 0));
        

        
//====================================================================================================================================
        return layout;
    }

    
    //variables
    
    //Synthesiser
    juce::Synthesiser synth;
    
    //how many voices
    int voiceCount = 8;
    
    
    //Sampler
    SFXSampler sampler;
    std::atomic<float>* sampleChoiceParam;
    

    //Reverb
    juce::Reverb reverb;
    std::atomic<float>* reverbOnOffParam;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AP_3AudioProcessor)
};
