#ifndef ENCODER_ANALYZER
#define ENCODER_ANALYZER

class EncoderAnalyzer
{
    int signalLevel;
    int encoderStep; // desk position is converted from this value
    
    // lastSample is the sample from the previous adc reading.
    short lastSample;
    short sample;

    // we know the direction of the encoder from the control signal (bluetooth or button).
    // 1 is up 0 is down.
    // for now it is 1.
    bool upDown = 1;
    
    //int inputChannel = INPUT_CHANNEL;
    
    // levelAnalyzer checks where the sample is in the expected signal.
    // 0 is the valley, 1 is middle and 2 the peak.
    // we only need positions 0 and 1 but position 2 is still here if we want
    // to know the direction from the signal at some later time.
    int levelAnalyzer(short sample);
    
    // Keeps track of the position by updating encoderStep.
    void analyze(short sample);
    
    public:
    EncoderAnalyzer();
    short getSample();
    void debugPrintSample(short sample);
};


#endif
