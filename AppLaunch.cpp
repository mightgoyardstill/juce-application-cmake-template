// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include "shared/ComponentWindow.h"
#include "MainComponent.h"

//==================================================================================
class AppLaunch   : public juce::JUCEApplication
{
    std::unique_ptr<ComponentWindow> window;

public:
    void initialise (const juce::String&) override
    {
        window.reset (new ComponentWindow (getApplicationName(), 
                                            new MainComponent()));

        window->onCloseButtonPressed = [&] { quit(); };
        window->setVisible (true);
    }

    void systemRequestedQuit() override    { quit(); }
    void shutdown() override               { window.reset(); }

    //==============================================================================
    bool moreThanOneInstanceAllowed() override                  { return false; }
    void anotherInstanceStarted (const juce::String&) override  {}

    //==============================================================================
    const juce::String getApplicationName() override
    {
        return JUCE_APPLICATION_NAME_STRING; 
    }

    const juce::String getApplicationVersion() override 
    {
        return JUCE_APPLICATION_VERSION_STRING; 
    }
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (AppLaunch)