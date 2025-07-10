/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AP_3AudioProcessor::AP_3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
apvts (*this, nullptr, "ParamTree", createParameterLayout() )
{
   ///initialise sampler
    sampler.init();
    
   ///initialise synthesiser
    synth.addSound (new SynthSound);
    
    for (int i = 0; i<voiceCount; i++)
    {
        synth.addVoice (new SynthVoice);
        sampler.addVoice (new juce::SamplerVoice() );
    }
    
    ///connect the parameters for each voice
    for (int i = 0; i<voiceCount; i++)
    {
        SynthVoice* voice = dynamic_cast <SynthVoice*>(synth.getVoice(i));
        voice -> connectParameters (apvts);
        
    }
    
}
AP_3AudioProcessor::~AP_3AudioProcessor()
{
}

//==============================================================================
void AP_3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ///set sample rate for instruments
    synth.setCurrentPlaybackSampleRate(sampleRate);
    sampler.setCurrentPlaybackSampleRate (sampleRate);
    
    ///connect parameters to apvts
    sampleChoiceParam = apvts.getRawParameterValue ("sampleChoice");
    reverbOnOffParam = apvts.getRawParameterValue("reverbOnOff");
    
    ///set up reverb
    juce::Reverb::Parameters reverbParams;
    reverbParams.dryLevel = 0.5f ;
    reverbParams.wetLevel = 0.5f;
    reverbParams.roomSize = 0.7f;
    
    reverb.setParameters(reverbParams);
    
    reverb.reset();
    
}

void AP_3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    /// send midi data and audio buffer to synth for processing
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    /// send midi data and audio buffer to sampler for processing
   sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    /// connect to sample choice parameter within loop
    sampler.setChoice(*sampleChoiceParam);
    
    ///re-initialise sampler per loop to see check if choice has been changed
    sampler.choiceLoop();
    
    ///set up reverb in loop
    int durationInSamples = buffer.getNumSamples();
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);
    
    ///connect to reverb on/off parameter within loop
    int reverbOnOff = int(*reverbOnOffParam);
    
    ///when reverb on/off param is on, reverb is applied
    if (reverbOnOff == 0)
    {
        reverb.processStereo(left, right, durationInSamples);
    }
    
}

//==============================================================================

const juce::String AP_3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AP_3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AP_3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AP_3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AP_3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AP_3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AP_3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void AP_3AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AP_3AudioProcessor::getProgramName (int index)
{
    return {};
}

void AP_3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void AP_3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AP_3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


bool AP_3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AP_3AudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void AP_3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // this code goes in getStateInformation()
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void AP_3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // this code goes in setStateInformation()
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (apvts.state.getType()))
        {
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AP_3AudioProcessor();
}
