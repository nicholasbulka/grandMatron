#pragma once
#include <vector>
#include <shared_plugin_helpers/shared_plugin_helpers.h>


class LowpassHighpassFilter
{
public:
  void setHighpass(bool highpass);
 void setCutoffFrequency(float cutoffFrequency);
  void setSamplingRate(float samplingRate);
 void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
  bool highpass;
 float cutoffFrequency;
  float samplingRate;
 std::vector<float> dnBuffer;
};
