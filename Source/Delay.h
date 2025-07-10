/*
  ==============================================================================

    Delay.h
    Created: 6 Mar 2025 4:16:04pm
    Author:  Teen Kar Seng
 
 
 
 ==============================================================================
*/

// #include <
#pragma once

#include <vector>

class Delay
{
  
public:

    
    /// pass in delay time (in samples)
    void setDelayTimeInSamples(float newDelay)
    {
        delayTimeInSamples = newDelay;
        
        // constrain delay time to size of delay line
        if (delayTimeInSamples >= size)
            delayTimeInSamples = size-1;
        
        // set readPos relative to delay time
        readPos = writePos - delayTimeInSamples;
        
        // wrap readpos in case it is negative
        if (readPos < 0)
            readPos += size;
    }
    
    /// set the MAXIMUM size
    void setSize(int newSize)
    {
        size = newSize;
        buffer.resize(size);
    }
    
    
    /// read a sample from the delay line and increment the read head
    float readSample()
    {
        
        float output = linearInterpolation();
        
        // increment read head
        readPos ++;
        
        // wrap read head
        if (readPos >= size)
            readPos -= size;

        return output;
    }
    
    void setFeedbackGain (float _fb)
    {
        feedbackGain = _fb;
        if (feedbackGain > 1)
        {
            feedbackGain = 1;
        }
    }
    
    /**
     interpolate linearly between two points in the delay line
     
     @return output - interpolated value
     */
    float linearInterpolation()
    {
        // readPos = 2.5
        int lowerPos = floor(readPos); // 2
        int higherPos = lowerPos + 1;  // 3
        
        // wrap just in case we've gone over the end of the vector
        higherPos %= size;
        
        float lowerVal = buffer[lowerPos]; // buffer[2]
        float higherVal = buffer[higherPos]; // buffer[3]
        
        float frac = readPos - lowerPos;  // 0.5
        
        float output = (1 - frac) * lowerVal  +  frac * higherVal;
        
        return output;
    }
    
    /// write a sample and increment the write head
    void writeSample(float inputSample)
    {
        buffer[writePos] = inputSample;
        
        // increment write head
        writePos ++;
        
        // wrap write head
        writePos %= size;
    }
    
    
    /**
     Process a single sample
     
     Stores the input sample, returning the delayed sample
     */
    float process(float inputSample)
    {
        
        // get value at read head
        float output = readSample();
        

        // store incoming sample
        float feedbackSample = output * feedbackGain;
        writeSample (inputSample + feedbackSample);
        
        
        float wet = output * dryWet;
        float dry = inputSample * (1 - dryWet);
        
        return wet + dry;
    }
    
    void resetPos()
    {
        
        
    }
    
private:
    
    // member variables
    float delayTimeInSamples;
    
    std::vector<float> buffer;  // delay data
    int size;   // how big is the buffer in samples
    
    float readPos = 0; // where are we up to in our buffer
    int writePos = 0;
    
    
    float dryWet = 0.5;           // 0-1 0=dry, 1=wet
    float feedbackGain = 0.75;
   
    
    
};
