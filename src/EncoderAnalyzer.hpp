#ifndef ENCODER_ANALYZER
#define ENCODER_ANALYZER

class EncoderAnalyzer
{
    //int inputChannel = INPUT_CHANNEL;
    public:
    EncoderAnalyzer();
    short* getSample();
    void debugPrintSample(short* sample);
};


#endif