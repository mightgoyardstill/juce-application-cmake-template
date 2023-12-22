#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    mainComponent.reset (new LambdaComponent
    (
        [&] (juce::Component& c, juce::Graphics& g)
        {
            g.fillAll (findColour (juce::ResizableWindow::backgroundColourId).darker (0.5f));
            g.setColour (juce::Colours::white);
            g.drawRect (c.getLocalBounds(), 1);
        }
    ));

    mainComponent->onMouseDown = [this] (const juce::MouseEvent& event)
    {
        if (event.mods.isRightButtonDown())
            showQuitMenu().showMenuAsync (juce::PopupMenu::Options().withMousePosition());   
        else
        {
            auto size = juce::Random::getSystemRandom().nextInt (100) + 10;
            auto colour = std::make_shared<juce::Colour>(juce::Colours::white);
            auto position = event.getPosition();
            int  timerFrequency {juce::Random::getSystemRandom().nextInt (2000) + 10};

            auto component = createTimerComponent
            (
                timerFrequency, [colour] (juce::Component& c, juce::Graphics& g) 
                {
                    g.setColour (colour->withAlpha (c.isMouseOver() ? 1.0f : 0.4f));
                    g.drawEllipse (c.getLocalBounds().toFloat().reduced (2), 3.0f);
                    g.drawFittedText ("Hello World!", c.getLocalBounds(), juce::Justification::centred, 1);
                    g.drawRect (c.getLocalBounds(), 1);
                },
                [colour] (juce::Component& c, juce::Timer&)
                {                    
                    *colour = juce::Colour::fromRGB
                    (
                        juce::uint8(juce::Random::getSystemRandom().nextInt(255)),
                        juce::uint8(juce::Random::getSystemRandom().nextInt(255)),
                        juce::uint8(juce::Random::getSystemRandom().nextInt(255))
                    );

                    c.repaint();
                }
            );

            component->onMouseDown = [this, c = component.get()] (const juce::MouseEvent& e) 
            { 
                if (e.mods.isRightButtonDown())
                    showComponentMenu(*c).showMenuAsync (juce::PopupMenu::Options().withMousePosition());

                // maybe start and stop timer control? should TimerComponent just be a separate class?
            };



            component->setBufferedToImage (true);
            component->setRepaintsOnMouseActivity (true);
            component->setSize (size, size);
            component->setCentrePosition (position);
            component->setComponentID (juce::String(components.size()));


            components.add (std::move(component));
            mainComponent->addAndMakeVisible (components.getLast());
        }
    };

    addAndMakeVisible (mainComponent.get());
    setTopLeftPosition (0, 0);
    setSize (400, 500);
}

void MainComponent::resized()
{
    mainComponent->setBounds (getLocalBounds());

    // resize all the components to scale to the new size of the main component
    // for (auto& component : components)
    //     component->setBounds (component->getBounds().withSizeKeepingCentre (getWidth(), getHeight()));
}