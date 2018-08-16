#include "CTAGInstrumentComponent.h"


int CTAGInstrumentComponent::counter = 0;

CTAGInstrumentComponent::CTAGInstrumentComponent(JucesamplerAudioProcessor& p) : processor(p)
{
	attackSlider = new Slider("attackSlider");
	attackSlider->setSliderStyle(Slider::LinearVertical);
	attackSlider->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
	attackSlider->setBounds(40, 120, 40, 136);
	attackSlider->setRange(0.0f, 500.0f);
	attackSlider->setValue(0.0f);
	addAndMakeVisible(attackSlider);

	decaySlider = new Slider("decaySlider");
	decaySlider->setSliderStyle(Slider::LinearVertical);
	decaySlider->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
	decaySlider->setBounds(88, 120, 40, 136);
	decaySlider->setRange(0.0f, 1000.0f);
	decaySlider->setValue(0.0f);
	addAndMakeVisible(decaySlider);

	sustainSlider = new Slider("sustainSlider");
	sustainSlider->setSliderStyle(Slider::LinearVertical);
	sustainSlider->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
	sustainSlider->setBounds(136, 120, 40, 136);
	sustainSlider->setRange(0.0f, 1.0f);
	sustainSlider->setValue(1.0f);
	addAndMakeVisible(sustainSlider);

	releaseSlider = new Slider("releaseSlider");
	releaseSlider->setSliderStyle(Slider::LinearVertical);
	releaseSlider->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
	releaseSlider->setBounds(184, 120, 40, 136);
	releaseSlider->setRange(0.0f, 5000.0f);
	releaseSlider->setValue(1000.0f);
	addAndMakeVisible(releaseSlider);

	amplitudeEnvelopeLabel = new Label("amplitudeEnvelopeLabel", translate("Amplitude Envelope"));
	amplitudeEnvelopeLabel->setFont(Font(12.00f, Font::plain).withTypefaceStyle("Regular"));
	amplitudeEnvelopeLabel->setJustificationType(Justification::centredLeft);
	amplitudeEnvelopeLabel->setEditable(false, false, false);
	amplitudeEnvelopeLabel->setColour(TextEditor::textColourId, Colours::black);
	amplitudeEnvelopeLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	amplitudeEnvelopeLabel->setBounds(48, 88, 150, 24);
	addAndMakeVisible(amplitudeEnvelopeLabel);

	attackLabel = new Label("attackLabel", translate("Attack"));
	attackLabel->setFont(Font(12.00f, Font::plain).withTypefaceStyle("Regular"));
	attackLabel->setJustificationType(Justification::centredLeft);
	attackLabel->setEditable(false, false, false);
	attackLabel->setColour(TextEditor::textColourId, Colours::black);
	attackLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	attackLabel->setBounds(40, 256, 48, 24);
	addAndMakeVisible(attackLabel);

	decayLabel = new Label("decayLabel", translate("Decay"));
	decayLabel->setFont(Font(12.00f, Font::plain).withTypefaceStyle("Regular"));
	decayLabel->setJustificationType(Justification::centredLeft);
	decayLabel->setEditable(false, false, false);
	decayLabel->setColour(TextEditor::textColourId, Colours::black);
	decayLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	decayLabel->setBounds(88, 256, 48, 24);
	addAndMakeVisible(decayLabel);

	sustainLabel = new Label("sustainLabel", translate("Sustain"));
	sustainLabel->setFont(Font(12.00f, Font::plain).withTypefaceStyle("Regular"));
	sustainLabel->setJustificationType(Justification::centredLeft);
	sustainLabel->setEditable(false, false, false);
	sustainLabel->setColour(TextEditor::textColourId, Colours::black);
	sustainLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	sustainLabel->setBounds(136,256,48,24);
	addAndMakeVisible(sustainLabel);

	releaseLabel = new Label("releaseLabel", translate("Release"));
	releaseLabel->setFont(Font(12.00f, Font::plain).withTypefaceStyle("Regular"));
	releaseLabel->setJustificationType(Justification::centredLeft);
	releaseLabel->setEditable(false, false, false);
	releaseLabel->setColour(TextEditor::textColourId, Colours::black);
	releaseLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	releaseLabel->setBounds(184, 256, 48, 24);
	addAndMakeVisible(releaseLabel);

	filterToggle = new ToggleButton("filterToggler");
	filterToggle->setButtonText(translate("Filter"));
	filterToggle->setBounds(272, 128, 150, 24);
	filterToggle->addListener(this);
	addAndMakeVisible(filterToggle);

	distortionToggle = new ToggleButton("distortionToggle");
	distortionToggle->setButtonText(translate("Distortion"));
	distortionToggle->setBounds(368, 128, 150, 24);
	distortionToggle->addListener(this);
	addAndMakeVisible(distortionToggle);

	filterSlider = new Slider("filterSlider");
	filterSlider->setSliderStyle(Slider::Rotary);
	filterSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
	filterSlider->setRange(80.0f, 18000.0f, 0);
	filterSlider->setValue(18000.0f);
	filterSlider->setSkewFactor(0.199f);
	filterSlider->setBounds(280, 160, 64, 88);
	addAndMakeVisible(filterSlider);
	filterSlider->setVisible(false);

	distortionSlider = new Slider("distortionSlider");
	distortionSlider->setSliderStyle(Slider::Rotary);
	distortionSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
	distortionSlider->setRange(0.2f, 5.0f, 0);
	distortionSlider->setValue(0.2f);
	distortionSlider->setBounds(384, 160, 64, 88);
	addAndMakeVisible(distortionSlider);
	distortionSlider->setVisible(false);

	pitchLabel = new Label("pitchLabel" ,translate("Pitch"));
	pitchLabel->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	pitchLabel->setJustificationType(Justification::centred);
	pitchLabel->setEditable(false, false, false);
	pitchLabel->setColour(TextEditor::textColourId, Colours::black);
	pitchLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	pitchLabel->setBounds(468, 128, 72, 24);
	addAndMakeVisible(pitchLabel);

	pitchSlider = new Slider("pitchSlider");
	pitchSlider->setSliderStyle(Slider::IncDecButtons);
	pitchSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
	pitchSlider->setRange(-12, 12, 1);
	pitchSlider->setValue(0);
	pitchSlider->setBounds(488, 168, 80, 80);
	addAndMakeVisible(pitchSlider);

	setSize(600, 375);

	attackAmpAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("ampEnvAttack" + String(counter)), *attackSlider);
	decayAmpAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("ampEnvDecay" + String(counter)), *decaySlider);
	sustainAmpAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("ampEnvSustain" + String(counter)), *sustainSlider);
	releaseAmpAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("ampEnvRelease" + String(counter)), *releaseSlider);

	filterToggleAttach = new AudioProcessorValueTreeState::ButtonAttachment(processor.getValueTree(), String("Filter ON/OFF" + String(counter)), *filterToggle);
	distortionToggleAttach = new AudioProcessorValueTreeState::ButtonAttachment(processor.getValueTree(), String("Distortion ON/OFF" + String(counter)), *distortionToggle);

	filterCutoffAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("filterCutoff" + String(counter)), *filterSlider);
	distortionValueAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("distortionVal" + String(counter)), *distortionSlider);
	pitchValueAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTree(), String("pitchVal" + String(counter)), *pitchSlider);

	counter++;
}

CTAGInstrumentComponent::~CTAGInstrumentComponent()
{
	
	attackAmpAttach = nullptr;
	decayAmpAttach = nullptr;
	sustainAmpAttach = nullptr;
	releaseAmpAttach = nullptr;
	filterToggleAttach = nullptr;
	distortionToggleAttach = nullptr;
	filterCutoffAttach = nullptr;
	distortionValueAttach = nullptr;
	pitchValueAttach = nullptr;

	pitchSlider = nullptr;
	distortionSlider = nullptr;
	filterSlider = nullptr;
	distortionToggle = nullptr;
	filterToggle = nullptr;
	releaseLabel = nullptr;
	sustainLabel = nullptr;
	decayLabel = nullptr;
	attackLabel = nullptr;
	amplitudeEnvelopeLabel = nullptr;
	releaseSlider = nullptr;
	sustainSlider = nullptr;
	decaySlider = nullptr;
	attackSlider = nullptr;
	counter--;
}

void CTAGInstrumentComponent::paint(Graphics& g)
{
	g.fillAll(Colour(0xff323e44));
}

void CTAGInstrumentComponent::resized()
{
	
}

void CTAGInstrumentComponent::buttonClicked(Button* buttonThatWasClicked)
{
	if(buttonThatWasClicked == filterToggle)
	{
		if (filterToggle->getToggleState())
			filterSlider->setVisible(true);
		if (!filterToggle->getToggleState())
			filterSlider->setVisible(false);
	}
	else if (buttonThatWasClicked == distortionToggle)
	{
		if (distortionToggle->getToggleState())
			distortionSlider->setVisible(true);
		if (!distortionToggle->getToggleState())
			distortionSlider->setVisible(false);
	}
}

