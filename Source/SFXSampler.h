/*
  ==============================================================================

    SFXSampler.h
    Created: 13 Apr 2025 1:40:38pm
    Author:  Teen Kar Seng

  ==============================================================================
*/
#include "mySamplerVoice.h"

#pragma once


class SFXSampler : public juce::Synthesiser
{
    public:
    
    /**
  Load samples into polyphonic sampler
     */
    
    void setChoice (int _choice)
    {
        sampleChoiceNumber = _choice;
    }
    
  
    //initialise in loop
    void choiceLoop ()
    {
        
        //Where is binary data?
        std::unique_ptr<juce::MemoryInputStream> inputStream;
        
        
        //No Sample
        if (sampleChoiceNumber == 0)
        {
            clearSounds();
        }
        
        //Metal SFX
        else if (sampleChoiceNumber == 1)
        {
            clearSounds();
            
            inputStream.reset (new juce::MemoryInputStream(BinaryData::Metal_Dink_wav, BinaryData::Metal_Dink_wavSize, false) );
            
            //create a reader for this wav file
            reader.reset(formatManager.createReaderFor(std::move (inputStream) ));
            
            //Which keys on the keyboard should trigger this sound file?
            juce::BigInteger range;
            range.setRange (0, 127, true);
            
            
            addSound (new juce::SamplerSound("MetalDink", *reader, range, 60, 0.01, 0.1, 4.0) );
        }
        
        //Wood SFX
        else if (sampleChoiceNumber == 2)
        {
            clearSounds();
            
            inputStream.reset (new juce::MemoryInputStream(BinaryData::Wood_Knock_wav, BinaryData::Wood_Knock_wavSize, false) );
            
            //create a reader for this wav file
            reader.reset(formatManager.createReaderFor(std::move (inputStream) ));
            
            //Which keys on the keyboard should trigger this sound file?
            juce::BigInteger range;
            range.setRange (0, 127, true);
            
            
            addSound (new juce::SamplerSound("WoodKnock", *reader, range, 60, 0.01, 0.1, 4.0) );
        }
        
        //Bubble SFX
        else if (sampleChoiceNumber == 3)
        {
            clearSounds();
            
            inputStream.reset (new juce::MemoryInputStream(BinaryData::Bubble_Bloop_wav, BinaryData::Bubble_Bloop_wavSize, false) );
            
            //create a reader for this wav file
            reader.reset(formatManager.createReaderFor(std::move (inputStream) ));
            
            //Which keys on the keyboard should trigger this sound file?
            juce::BigInteger range;
            range.setRange (0, 127, true);
            
            
            addSound (new juce::SamplerSound("BubbleBloop", *reader, range, 60, 0.01, 0.1, 4.0) );
        }
    }
    
    
    //initialise in constructor
    void init()
    {
        //prepare to load a .wav file
        formatManager.registerBasicFormats();
        
    }
    
    
    private:
    //Sampler
    juce::AudioFormatManager formatManager;
    std::unique_ptr <juce::AudioFormatReader> reader;
    
    
    
    //Choose which sampler
   int sampleChoiceNumber;
    
};
