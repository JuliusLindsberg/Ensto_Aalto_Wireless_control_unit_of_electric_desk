#include "EncoderAnalyzer.hpp"
#include "DebugPrinter.hpp"
#include "DebugBlinker.hpp"

#include <devicetree.h>
#include <drivers/adc.h>
#include <drivers/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hal/nrf_saadc.h"

#define ADC_NODE_LABEL DT_LABEL(DT_NODELABEL(adc))
#define SAMPLE_BUFFER_SIZE 2
#define SAMPLE_RESOLUTION 10
//SAMPLE_GAP_MILLISECONDS 0 basically means "do it ASAP"
#define SAMPLE_GAP_MILLISECONDS 0
#define INPUT_CHANNEL 1
#define OVERSAMPLING 0
#define CALIBRATE 1
#define EXTRA_SAMPLINGS 0

// Signal thresholds to compare the signal to (if its peak middle or valley)
// subject to change depending on the microcontroller used to test
#define THRESHOLD_LOW 610
#define THRESHOLD_HIGH 625

bool EA_initialized = false;
device* adcDevice;
short sampleBuffer[SAMPLE_BUFFER_SIZE] = {0};

static struct adc_channel_cfg adcChannelConfig = {
    .gain = ADC_GAIN_1_6,
    .reference = ADC_REF_INTERNAL,
    .acquisition_time = ADC_ACQ_TIME_DEFAULT,
    //WARNING: these will be defined during runtime and changing them here doesn't change anything
    .channel_id = 0,
    .differential = 0,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
    .input_positive = NRF_SAADC_INPUT_AIN1,     //input negative only for differential signal
#endif
};

const struct adc_sequence_options SampleOptions = {
    .interval_us = 0,
    .callback = NULL,
    .extra_samplings = EXTRA_SAMPLINGS
};
const struct adc_sequence sampleSequence = {
.options = &SampleOptions,
.channels = BIT(INPUT_CHANNEL),
.buffer = sampleBuffer,
.buffer_size = SAMPLE_BUFFER_SIZE,
.resolution = SAMPLE_RESOLUTION,
.oversampling = OVERSAMPLING,
.calibrate = CALIBRATE
};

//constructor automatically initializes ADC. The interface of this class is channel spesific
//and the channel to be used will be given when an object is constructed. Valid channels are 0-7(?)

EncoderAnalyzer::EncoderAnalyzer()
{
    if(!EA_initialized)
    {
        adcDevice = device_get_binding("ADC_0");
        //inputChannel = INPUT_CHANNEL;
        if(!adcDevice)
        {
            declareException();
            return;
        }
        adcChannelConfig.channel_id = INPUT_CHANNEL;
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
        adcChannelConfig.input_positive = INPUT_CHANNEL+1;
#endif
        int ret = adc_channel_setup(adcDevice, &adcChannelConfig);
        if(ret != NULL)
        {
            declareException();
        }
        EA_initialized = true;
    }
}



//fills sampleBuffer with samples
short EncoderAnalyzer::getSample()
{
    //extra samples without multiple calls to adc_read probably requires a callback function to be setup (?)
    adc_read(adcDevice, &sampleSequence);
    return sampleBuffer[0];
}
void EncoderAnalyzer::debugPrintSample(short sample)
{
    /*for(unsigned i = 0; i < SAMPLE_BUFFER_SIZE; i++)
    {
        sprintf(it, "%d ", sample[i]);
        it = line + strlen(line);
        if(it >= line+600-2)
        {
            //lines get culled before 600 characters
            line[strlen(line)] = '\n';
            printer << line;
            memset(line, 0, 600);
            it = line;
            break;
        }
    }
    line[strlen(line)] = '\n';
    printer << line;*/
}

int EncoderAnalyzer::levelAnalyzer(short sample){
  if (sample >= THRESHOLD_LOW){
    if (sample >= THRESHOLD_HIGH){
      return 2;
    }
    else {
      return 1;
    }
  }
  else {
    return 0;
  }
}

void EncoderAnalyzer::analyze(short sample) {
  if (upDown){
    if ((signalLevel != 2) && (levelAnalyzer(sample) == 2)) {
      encoderStep++;
    }
  }
  else {
    if ((signalLevel == 2) && (levelAnalyzer(sample) != 2)) {
      encoderStep--;
    }
  }
  signalLevel = levelAnalyzer(sample);
}
