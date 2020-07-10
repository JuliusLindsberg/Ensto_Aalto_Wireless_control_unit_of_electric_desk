#ifndef ENCODER_ANALYZER
#define ENCODER_ANALYZER

#define SAMPLE_BUFFER_SIZE 20
#define SAMPLE_RESOLUTION 10
//SAMPLE_GAP_MILLISECONDS 0 basically means "do it ASAP"
#define SAMPLE_GAP_MILLISECONDS 0
#define INPUT_CHANNEL 0
#define OVERSAMPLING 0
#define CALIBRATE 0

class EncoderAnalyzer
{
    int inputChannel = INPUT_CHANNEL;
    public:
    EncoderAnalyzer();
    short* getSample();
    void debugPrintSample(short* sample);
};


#endif