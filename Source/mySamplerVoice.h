/*
  ==============================================================================

    mySamplerVoice.h
    Created: 14 Apr 2025 11:03:40am
    Author:  Teen Kar Seng

  ==============================================================================
*/


#pragma once

class mySamplerVoice : public juce::SamplerVoice
{
    
    public:
    
    int getParamNumber ()
    {
        int choice = int (*sampleChoiceParam);
        return choice;
    }
    
    
    /// connect synthesiser voice parameters to the audio processor value tree state
        void connectParameters (juce::AudioProcessorValueTreeState& apvts)
    {
            sampleChoiceParam = apvts.getRawParameterValue ("sampleChoice");
            
        }
    
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                                  int startSample,
                                  int numSamples) override
    {
        
    }
    
    private:
    std::atomic<float>* sampleChoiceParam;
  
    
};
