# tool-arduino-data-sampler

Simple buffered data sampling Arduino tool useful for sampling at high frequencies (up to the limits of the microcontroller)

## Problem:
Logging data directly to SPI or I2C devices (such as SD card) is quite slow and a bottleneck due to write speed limits

## Solution:
Storing data directly to SRAM with a fixed size buffer is the fastest way to save data sampled at high frequencies, this library provides an easy way to do it.

The main drawback is that we have a limited buffer size restricted to the SRAM capabilities of the microcontroller.

## Example: Sampling at 2kHz with Arduino

Plotted using [Plotly Chart Studio](https://chart-studio.plotly.com/create/#/)

<img src="https://github.com/Rafdal/tool-arduino-data-sampler/blob/main/imagen.png" alt="Sampled data plot"/>

```c++

#include <Arduino.h>

#include <DataSampler.h>

#define MAX_SAMPLES	900			// Sample list size
#define SAMPLES_PER_SEC	2000	// Sampling frequency in Hertz

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
	delay(100);

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

## Output:

```
Starting sampler in 1 sec
Running sampler...
Sampling took 0.450 seconds
With a total of 900 samples, averaging 0.500ms of time between samples

87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
88
88
88
87
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
89
89
89
89
91
93
95
97
98
100
102
103
104
105
107
108
109
110
111
112
113
114
116
117
118
119
120
121
122
124
125
126
127
128
129
130
131
132
132
133
134
134
135
135
136
136
136
132
128
125
122
120
118
116
114
113
111
110
109
107
106
105
104
103
102
101
100
99
99
98
97
97
96
96
95
95
94
94
94
93
93
93
92
92
92
92
91
91
91
91
91
91
90
90
90
90
90
90
90
90
89
89
89
89
89
89
89
89
89
89
89
89
89
89
89
89
89
88
89
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
88
87
88
88
88
88
88
87
88
87
87
87
87
87
87
87
87
87
87
87
87
87
87
88
88
88
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
88
87
88
87
87
88
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87
87

```
