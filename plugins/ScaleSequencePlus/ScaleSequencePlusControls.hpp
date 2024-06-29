#ifndef SCALESEQUENCE_PLUS_CONTROLS_HPP
#define SCALESEQUENCE_PLUS_CONTROLS_HPP

#include <array>

template <class T>
T limit (const T x, const T min, const T max)
{
    return (x < min ? min : (x > max ? max : x));
}

enum Parameters {
    kParameterMeasure =    0,
    kParameterMultiplier = 1,
    kParameterScaleGlide = 2,
    kParameterStep1      = 3,
    kParameterStep2      = 4,
    kParameterStep3      = 5,
    kParameterStep4      = 6,
    kParameterStep5      = 7,
    kParameterStep6      = 8,
    kParameterStep7      = 9,
    kParameterStep8      = 10,
    kParameterStep9      = 11,
    kParameterStep10     = 12,
    kParameterStep11     = 13,
    kParameterStep12     = 14,
    kParameterStep13     = 15,
    kParameterStep14     = 16,
    kParameterStep15     = 17,
    kParameterStep16     = 18,
    kParameterStep17     = 19,
    kParameterStep18     = 20,
    kParameterStep19     = 21,
    kParameterStep20     = 22,
    kParameterStep21     = 23,
    kParameterStep22     = 24,
    kParameterStep23     = 25,
    kParameterStep24     = 26,
    kParameterStep25     = 27,
    kParameterStep26     = 28,
    kParameterStep27     = 29,
    kParameterStep28     = 30,
    kParameterStep29     = 31,
    kParameterStep30     = 32,
    kParameterStep31     = 33,
    kParameterStep32     = 34,
    kParameterOffset     = 35,
    kParameterLoopPoint  = 36,
    kParameterCurrentStep = 37,
    kParameterCount      = 38
};

enum States {
    kStateFileSCL1 = 0,
    kStateFileSCL2 = 1,
    kStateFileSCL3 = 2,
    kStateFileSCL4 = 3,
    kStateFileSCL5 = 4,
    kStateFileSCL6 = 5,
    kStateFileSCL7 = 6,
    kStateFileSCL8 = 7,
    kStateFileKBM1 = 8,
    kStateFileKBM2 = 9,
    kStateFileKBM3 = 10,
    kStateFileKBM4 = 11,
    kStateFileKBM5 = 12,
    kStateFileKBM6 = 13,
    kStateFileKBM7 = 14,
    kStateFileKBM8 = 15,
    kStateCount    = 16
};

static const std::array<std::pair<float, float>, kParameterCount> controlLimits =
{{
    {0.0f, 2.0f},    //kParameterMeasure
	{1.0f, 12.0f},   //kParameterMultiplier,
	{1.0f, 100.0f}, //kParameterScaleGlide
    {1.0f, 8.0f},    //kParameterStep1,
    {1.0f, 8.0f},    //kParameterStep2,
    {1.0f, 8.0f},    //kParameterStep3,
    {1.0f, 8.0f},    //kParameterStep4,
    {1.0f, 8.0f},    //kParameterStep5,
    {1.0f, 8.0f},    //kParameterStep6,
    {1.0f, 8.0f},    //kParameterStep7,
    {1.0f, 8.0f},    //kParameterStep8,
    {1.0f, 8.0f},    //kParameterStep9,
    {1.0f, 8.0f},    //kParameterStep10,
    {1.0f, 8.0f},    //kParameterStep11,
    {1.0f, 8.0f},    //kParameterStep12,
    {1.0f, 8.0f},    //kParameterStep13,
    {1.0f, 8.0f},    //kParameterStep14,
    {1.0f, 8.0f},    //kParameterStep15,
    {1.0f, 8.0f},    //kParameterStep16,
    {1.0f, 8.0f},    //kParameterStep17,
    {1.0f, 8.0f},    //kParameterStep18,
    {1.0f, 8.0f},    //kParameterStep19,
    {1.0f, 8.0f},    //kParameterStep20,
    {1.0f, 8.0f},    //kParameterStep21,
    {1.0f, 8.0f},    //kParameterStep22,
    {1.0f, 8.0f},    //kParameterStep23,
    {1.0f, 8.0f},    //kParameterStep24,
    {1.0f, 8.0f},    //kParameterStep25,
    {1.0f, 8.0f},    //kParameterStep26,
    {1.0f, 8.0f},    //kParameterStep27,
    {1.0f, 8.0f},    //kParameterStep28,
    {1.0f, 8.0f},    //kParameterStep29,
    {1.0f, 8.0f},    //kParameterStep30,
    {1.0f, 8.0f},    //kParameterStep31,
    {1.0f, 8.0f},    //kParameterStep32,
    {-1.0f, 1.0f},   //kParameterOffset
    {2.0f, 32.0f},    //kParameterLoopPoint
    {0.0f, 1.0f}    //kParameterCurrentStep
}};

static const float ParameterDefaults[kParameterCount] = {
	0.0f, //kParameterMeasure
	1.0f, //kParameterMultiplier,
	1.0f, //kParameterScaleGlide
    1.0f, //kParameterStep1,
    1.0f, //kParameterStep2,
    1.0f, //kParameterStep3,
    1.0f, //kParameterStep4,
    1.0f, //kParameterStep5,
    1.0f, //kParameterStep6,
    1.0f, //kParameterStep7,
    1.0f, //kParameterStep8,
    1.0f, //kParameterStep9,
    1.0f, //kParameterStep10,
    1.0f, //kParameterStep11,
    1.0f, //kParameterStep12,
    1.0f, //kParameterStep13,
    1.0f, //kParameterStep14,
    1.0f, //kParameterStep15,
    1.0f, //kParameterStep16,
    1.0f, //kParameterStep17,
    1.0f, //kParameterStep18,
    1.0f, //kParameterStep19,
    1.0f, //kParameterStep20,
    1.0f, //kParameterStep21,
    1.0f, //kParameterStep22,
    1.0f, //kParameterStep23,
    1.0f, //kParameterStep24,
    1.0f, //kParameterStep25,
    1.0f, //kParameterStep26,
    1.0f, //kParameterStep27,
    1.0f, //kParameterStep28,
    1.0f, //kParameterStep29,
    1.0f, //kParameterStep30,
    1.0f, //kParameterStep31,
    1.0f, //kParameterStep32,
    0.0f, //kParameterOffset
    32.0f, //kParameterLoopPoint
    1.0f //kParameterCurrentStep (default not used)
	
};


#endif
