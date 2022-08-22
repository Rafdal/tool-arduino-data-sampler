#include "DataSampler.h"

template<typename T>
void DataSampler<T>::runSampler()
{
    sampleStart_ms = millis();
    unsigned int sampleCount = 0;

    if(samplerCallback != NULL)
    {
        T value = 0;
        while (sampleCount < sampleSize)
        {
            unsigned long ms = millis();
            if(ms - lastSample_ms >= samplingPeriod_ms)
            {
                samplerCallback(value); // read sample

                sampleList[sampleCount] = value; // save sample

                lastSample_ms = ms;
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
    Serial.print(((float)samplingTime_ms) / sampleCount, 1);
    Serial.println(F("ms of time between samples"));
}

template class DataSampler<float>;
template class DataSampler<double>;
template class DataSampler<int>;
template class DataSampler<int8_t>;
template class DataSampler<uint8_t>;