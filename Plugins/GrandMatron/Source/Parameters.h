#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
class ParameterHelper
{
public:
    ParameterHelper() = delete;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout layout;

        juce::ParameterID cutoffId = {"cutoff_frequency", 1};
        juce::ParameterID highPassId = {"highpass", 1};


        layout.add (std::make_unique<juce::AudioParameterFloat>(cutoffId, "Cutoff Frequency", juce::NormalisableRange{ 20.f, 20000.f, 0.1f, 0.2f, false }, 500.f));
        layout.add (std::make_unique<juce::AudioParameterBool>(highPassId, "Highpass", false));

        return layout;
    }
};