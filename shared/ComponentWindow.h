#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

//==============================================================================
struct ComponentWindow : public juce::DocumentWindow
{
    ComponentWindow (juce::String title, 
                     juce::Component* content, 
                     bool isResizeable = true, 
                     bool isNative = true)

        : juce::DocumentWindow (title, 
                                content->findColour (juce::ResizableWindow::backgroundColourId), 
                                juce::DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar (isNative);
        setContentOwned (content, true);
        setResizable (isResizeable, false);
    }

    void closeButtonPressed() override 
    {
        if (onCloseButtonPressed) onCloseButtonPressed();
    }

    std::function<void()> onCloseButtonPressed;
};