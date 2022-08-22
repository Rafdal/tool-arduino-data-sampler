#include "DataSampler.h"

template<typename T>
void DataSampler<T>::runSampler()
{
    sampleCount = 0;

    runActivationGate(); // (If set)

    sampleStart_ms = millis();

    if(samplerCallback != NULL)
    {
        T value = 0;
        while (sampleCount < sampleSize)
        {
            unsigned long us = micros();
            if(us - lastSample_us >= samplingPeriod_us)
            {
                samplerCallback(value); // read sample

                sampleList[sampleCount] = value; // save sample

                lastSample_us = us;
                sampleCount++;
            }
        }
    }
    unsigned long samplingTime_ms = millis() - sampleStart_ms;

    Serial.print(F("Sampling took "));
    Serial.print(samplingTime_ms/1000.0f, 3);
    Serial.println(F(" seconds"));
    Serial.print(F("With a total of "));
    Serial.print(sampleCount);
    Serial.print(F(" samples, averaging "));
    Serial.print(((float)samplingTime_ms) / (sampleCount - gateSize), 2);
    Serial.println(F("ms of time between samples"));
}


template<typename T>
void DataSampler<T>::setActivationGate(unsigned int gateSize, T absVariation)
{
    if(gateSize < sampleSize)
    {
        this->gateSize = gateSize;
        activationGatePreBuffer = new T[gateSize];
        gateMaxVariation = abs(absVariation);
        gatePos = 0;
    }
}


template<typename T>
void DataSampler<T>::runActivationGate()
{
    if(activationGatePreBuffer != NULL && samplerCallback != NULL)
    {
        Serial.println(F("Running activation gate..."));

        sampleCount = 0;
        bool firstRun = true;
        T currentValue = 0;
        T firstValue = 0;
        while ((abs(currentValue - firstValue)) <= (gateMaxVariation) || firstRun)
        {
            unsigned long us = micros();
            if(us - lastSample_us >= samplingPeriod_us)
            {
                samplerCallback(currentValue); // read sample value

                activationGatePreBuffer[gatePos++] = currentValue; // save sample value
                
                lastSample_us = us;
                if(gatePos == gateSize) // Roll circular buffer
                {
                    gatePos = 0;
                    if(firstRun)
                    {
                        firstValue = currentValue;
                        firstRun = false;
                    }
                }
            }
        }

        // Store gate buffer data
        for (unsigned int i = gatePos; i < gateSize; i++)
            sampleList[sampleCount++] = activationGatePreBuffer[i];

        for (unsigned int i = 0; i < gatePos; i++)
            sampleList[sampleCount++] = activationGatePreBuffer[i];            
    }
}


template class DataSampler<float>;
template class DataSampler<double>;
template class DataSampler<int>;
template class DataSampler<int8_t>;
template class DataSampler<uint8_t>;