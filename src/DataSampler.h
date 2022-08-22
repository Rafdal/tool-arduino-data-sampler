/**
 * @file DataSampler.h
 * @author Rafdal (rdalzotto@itba.edu.ar)
 * @brief Data sampler tool
 * @version 0.1
 * @date 2022-08-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DATA_SAMPLER_H
#define DATA_SAMPLER_H

#include <Arduino.h>

template <typename T>
class DataSampler
{
public:

    /**
     * @brief Construct a new Data Sampler object
     * 
     * @param maxSamples amount of samples to be read
     * @param samplesPerSec sample rate (Frequency) [Hertz]
     */
    DataSampler(unsigned int maxSamples, unsigned int samplesPerSec)
    {
        sampleSize = maxSamples;
        sampleList = new T[sampleSize];
        samplingPeriod_ms = 1000UL / samplesPerSec; // milliseconds
    }
    ~DataSampler()
    {
        delete[] sampleList;
    }

    /**
     * @brief Set the callback function to read values
     * 
     * @param callback function that receives a value reference to write and save samples
     */
    inline void setSamplerCallback(void (*callback)(T& value))
    {
        samplerCallback = callback;
    }

    /**
     * @brief Read and save all samples, executing the sampler callback function
     * 
     */
    void runSampler();
    
    // Get the max amount of samples of the sample window
    inline unsigned int size()
    {
        return sampleSize;
    }

    // Get the value of the n-th sample
    inline T getSample(unsigned int n)
    {
        return sampleList[n];
    }

private:
    T* sampleList = NULL;
    unsigned int sampleSize = 0;

    unsigned int samplingPeriod_ms = 0;
    unsigned long lastSample_ms = 0;


    unsigned long sampleStart_ms = 0;

    void (*samplerCallback)(T&) = NULL;
};

#endif