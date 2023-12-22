#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

//==============================================================================
struct LambdaComponent  : public juce::Component
{
    LambdaComponent() = default;

    LambdaComponent (std::function<void(juce::Component&, juce::Graphics&)> p,
                     std::function<void(juce::Component&)> r = nullptr)
        : onPaint (std::move (p)), onResized (std::move (r))
    {}

    std::function<void(juce::Component&, juce::Graphics&)>  onPaint;
    std::function<void(juce::Component&)>                   onResized;

    std::function<void(const juce::MouseEvent&)>            onMouseMove;
    std::function<void(const juce::MouseEvent&)>            onMouseEnter;
    std::function<void(const juce::MouseEvent&)>            onMouseExit;
    std::function<void(const juce::MouseEvent&)>            onMouseDown;
    std::function<void(const juce::MouseEvent&)>            onMouseDrag;
    std::function<void(const juce::MouseEvent&)>            onMouseUp;
    std::function<void(const juce::MouseEvent&)>            onMouseDoubleClick;
    std::function<void(const juce::MouseEvent&,
                       const juce::MouseWheelDetails&)>     onMouseWheelMove;
    std::function<void(const juce::MouseEvent&, float)>     onMouseMagnify;

    //==============================================================================
    void paint (juce::Graphics& g) override  { if (onPaint)   onPaint (*this, g); }
    void resized() override                  { if (onResized) onResized(*this); }

    void mouseMove  (const juce::MouseEvent& event) override  { if (onMouseMove) onMouseMove (event); }
    void mouseEnter (const juce::MouseEvent& event) override  { if (onMouseEnter) onMouseEnter (event); }
    void mouseExit  (const juce::MouseEvent& event) override  { if (onMouseExit) onMouseExit (event); }
    void mouseDown  (const juce::MouseEvent& event) override  { if (onMouseDown) onMouseDown (event); }
    void mouseDrag  (const juce::MouseEvent& event) override  { if (onMouseDrag) onMouseDrag (event); }
    void mouseUp    (const juce::MouseEvent& event) override  { if (onMouseUp) onMouseUp (event); }

    void mouseDoubleClick (const juce::MouseEvent& event) override  
    {
        if (onMouseDoubleClick) 
            onMouseDoubleClick (event);
    }

    void mouseWheelMove (const juce::MouseEvent& event,
                         const juce::MouseWheelDetails& wheel) override
    {
        if (onMouseWheelMove) 
            onMouseWheelMove (event, wheel); 
    }

    void mouseMagnify (const juce::MouseEvent& event, 
                       float scaleFactor) override
    {
        if (onMouseMagnify) 
            onMouseMagnify (event, scaleFactor);
    }
};


struct LambdaTimer  : public juce::Timer
{
    LambdaTimer() = default;

    LambdaTimer (std::function<void()> callback)
        : callbackFunction (std::move (callback))
    {}

    ~LambdaTimer() override { stopTimer(); }

    LambdaTimer& setCallback (std::function<void()> callback)
    {
        callbackFunction = std::move (callback);
        return *this;
    }

    void timerCallback() override
    {
        if (callbackFunction)
            callbackFunction();
    }
    
    std::function<void()> callbackFunction;
};