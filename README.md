# tool-arduino-data-sampler

Simple buffered data-sampling Arduino tool useful for sampling at high frequencies (up to microcontroller limits)

## Problem:
Data-logging directly to SPI or I2C devices (Like SD Card) is pretty slow and a bottleneck due to write speed limits

## Solution:
Storing data directly to SRAM with fixed-size buffers is the fastest way to save sampled data at high frequencies, this library provides an easy way to do that

## Example:

```c++

#include <Arduino.h>

#include <DataSampler.h>

#define MAX_SAMPLES	500		// Sample list size
#define SAMPLES_PER_SEC	500	// Sampling frequency in Hertz

DataSampler<uint8_t> sampler(MAX_SAMPLES, SAMPLES_PER_SEC);

void setup()
{
	Serial.begin(115200);

	// Set read sensor callback
	sampler.setSamplerCallback([](uint8_t& value){
		value = (uint8_t)(analogRead(A0) / 4);
	});

	Serial.println(F("Starting sampler in 1 sec"));
	delay(1000);

	Serial.println(F("Running sampler..."));

	sampler.runSampler(); // Read and save all samples

	// Print all samples:	
	Serial.println();
	for (size_t i = 0; i < sampler.size(); i++)
	{
		Serial.println(sampler.getSample(i));
	}
	Serial.println();
}

void loop()
{
}
```
