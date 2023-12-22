cmake_minimum_required (VERSION 3.16..3.22)
project (juce_audio_app_example VERSION 0.0.1)

set (juce_dir "$ENV{HOME}/Documents/Code/JUCE/")
# set (juce_dir "C:/develop/juce_clap_host/libs/JUCE")
add_subdirectory (${juce_dir} "${PROJECT_BINARY_DIR}/juce")

option (JUCE_BUILD_EXTRAS "Build JUCE Extras" OFF)
option (JUCE_BUILD_EXAMPLES "Build JUCE Examples" OFF)

set (SOURCE AppLaunch.cpp MainComponent.cpp)
set (JUCE_GENERATE_JUCE_HEADER 1)

juce_add_gui_app ( ${PROJECT_NAME}
    PRODUCT_NAME "Audio App Example"
    VERSION ${PROJECT_VERSION}
    COMPANY_NAME dev.juce.apps
)
add_compile_definitions (
    JUCE_DISABLE_JUCE_VERSION_PRINTING=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:JUCE_VERSION>"
)

if (JUCE_GENERATE_JUCE_HEADER)
    juce_generate_juce_header (${PROJECT_NAME})
endif()

target_sources ( ${PROJECT_NAME} PRIVATE ${SOURCE})
target_link_libraries ( ${PROJECT_NAME}
PRIVATE
    juce::juce_audio_utils
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)