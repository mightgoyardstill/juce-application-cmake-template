#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>
#include "shared/LambdaComponent.h"

//==============================================================================
class MainComponent   : public juce::Component
{
    std::unique_ptr<LambdaComponent>    mainComponent;
    juce::OwnedArray<LambdaComponent>   components;

public:
    MainComponent();
    void resized() override;
    
private:
    juce::PopupMenu showQuitMenu() const
    {        
        juce::PopupMenu menu;
        menu.addItem (juce::PopupMenu::Item("Quit").setAction ([&] 
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit(); }
        ));

        return menu;
    }

    juce::PopupMenu showComponentMenu(LambdaComponent& c) const
    {        
        juce::PopupMenu menu;
        menu.addItem (juce::PopupMenu::Item("Random size").setAction ([&]
        { 
            auto size = juce::Random::getSystemRandom().nextInt (100) + 10;
            c.setBounds(c.getBounds().withSizeKeepingCentre (size, size));
        }));

        return menu;
    }

    std::unique_ptr<LambdaComponent> createTimerComponent (int timerFrequency, 
        std::function<void(juce::Component&, juce::Graphics&)> paintFunction, 
        std::function<void(juce::Component&, juce::Timer&)> timerFunction = nullptr)
    {
        auto local = std::make_unique<LambdaComponent> ();
        auto timer = std::make_shared<LambdaTimer> ();

        timer->setCallback 
        (
            [t = timer.get(), c = local.get(), 
             callback = std::move(timerFunction)] () mutable
            {
                if (callback) 
                    callback(*c, *t);
            }
        );

        if (timerFrequency > 0)
            timer->startTimer(timerFrequency);

        local->onPaint = [timer = std::move (timer), 
                          callback = std::move(paintFunction)]
                          (juce::Component& c, juce::Graphics& g) 
                          {
                              callback(c, g);
                          };
        return local;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};