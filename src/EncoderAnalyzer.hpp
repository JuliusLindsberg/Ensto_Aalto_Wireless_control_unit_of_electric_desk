#ifndef ENCODER_ANALYZER
#define ENCODER_ANALYZER

//WARNING: OBJECT ABSTRACTION IN THIS CLASS IS CURRENTLY BROKEN! DON'T MAKE MULTIPLE OBJECTS OF THIS CLASS.
//maintenance required.
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
    bool upDown;
    
    //int inputChannel = INPUT_CHANNEL;
    
    // levelAnalyzer checks where the sample is in the expected signal.
    // 0 is the valley, 1 is middle and 2 the peak.
    // we only need positions 0 and 1 but position 2 is still here if we want
    // to know the direction from the signal at some later time.
    int analyzeLevel(short sample);
    
    // Keeps track of the position by updating encoderStep.
    void analyzeStep(short sample);
    //gets a single sample from the adc
    short getSample();
    public:
    EncoderAnalyzer();
    //WARNING: CURRENTLY THIS FUNCTION IS BLOCKING AND HAS TO BE EXECUTED REPEATEDLY FOR CORRECT READINGS
    int updateAndGetDeskPosition();
};


#endif
