#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr int numParams = 10000;
constexpr bool useEditor = true;

MatriarchFilterAudioProcessor::MatriarchFilterAudioProcessor()
{
    cutoffFrequencyParameter =
        mApvts.getRawParameterValue("cutoff_frequency");
    highpassParameter = mApvts.getRawParameterValue("highpass");
}

void MatriarchFilterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mFilter.setSamplingRate(static_cast<float>(sampleRate));
}

void MatriarchFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const auto cutoffFrequency = cutoffFrequencyParameter->load();
    const auto highpass = *highpassParameter < 0.5f ? false : true;
    mFilter.setCutoffFrequency(cutoffFrequency);
    mFilter.setHighpass(highpass);
    mFilter.processBlock(buffer, midiMessages);
}
juce::AudioProcessorEditor* MatriarchFilterAudioProcessor::createEditor()
{

    return new MatriarchFilterAudioProcessorEditor(*this);

}

bool MatriarchFilterAudioProcessor::hasEditor() const
{
    return useEditor;
}

juce::AudioProcessorValueTreeState& MatriarchFilterAudioProcessor::getAudioProcessorValueTreeState()
{
    return mApvts;
}

LowpassHighpassFilter& MatriarchFilterAudioProcessor::getFilter()
{
    return mFilter;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MatriarchFilterAudioProcessor();
}

