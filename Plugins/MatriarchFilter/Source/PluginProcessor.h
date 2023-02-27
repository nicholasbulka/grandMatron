#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "Parameters.h"
#include "LowpassHighpassFilter.h"

//Inhereting from PluginHelpers::ProcessorBase, which is just inhereting from juce::AudioProcessor
//And adding some default implementations

class MatriarchFilterAudioProcessor : public PluginHelpers::ProcessorBase
{
public:
    MatriarchFilterAudioProcessor();

    void prepareToPlay(double, int) override;
    void processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer& midiMessages) override;

    bool hasEditor() const override;
    juce::AudioProcessorEditor* createEditor() override;
    juce::AudioProcessorValueTreeState& getAudioProcessorValueTreeState();
    LowpassHighpassFilter& getFilter();
private:
    juce::AudioProcessorValueTreeState mApvts { *this,
                                              nullptr,
                                              juce::Identifier("MatriarchFilter"),
                                              ParameterHelper::createParameterLayout()
    };
    std::atomic<float>* cutoffFrequencyParameter = nullptr;
    std::atomic<float>* highpassParameter = nullptr;
    LowpassHighpassFilter mFilter;
};
