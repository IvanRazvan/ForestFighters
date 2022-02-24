#include "Application.h"
#include "Graphics.h"
#include "SoundManager.h"
#include "Input.h"
#include "Scene.h"
#include "Simulation.h"
#include "MainMenu.h"

// This function pushes a scene on top of the stack.
void Application::PushScene()
{
    m_pushScene = false;
    m_scenes.push(m_sceneToPush);
    m_scenes.top()->Init();
    GetGraphics()->ResetScreen();
    m_sceneToPush = nullptr;
}

// This function pops the scene on top of the stack.
void Application::PopScene()
{
    m_popScene = false;
    if (!m_scenes.empty())
    {
        m_scenes.pop();
        GetGraphics()->ResetScreen();
    }
}

// This constructor initialises the application.
Application::Application()
{
    srand((unsigned int)time(NULL));

    m_graphics = std::make_shared <Graphics>(screenWidth, screenHeight, "A0001151 : HAPI Window");

    m_sound = std::make_shared <SoundManager>();
    m_sound->Load("click");
    m_sound->Load("shoot");
    m_sound->Load("hit");
    m_sound->Load("death");

    m_input = std::make_shared <Input>();

    m_globalClock = HAPI.GetTime();
    m_updateClock = HAPI.GetTime();
}

// This function flags a pending push for the next loop iteration.
void Application::RequestPushScene(std::shared_ptr <Scene> newScene)
{
    m_pushScene = true;
    m_sceneToPush = newScene;
}

// This function flags a pending pop for the next loop iteration.
void Application::RequestPopScene()
{
    m_popScene = true;
}

// This function holds the main loop.
void Application::Run()
{
    GetSound()->PlayLoop("BackgroundMusic", true);

    // We push the menu scene.
    RequestPushScene(std::make_shared <MainMenu>(this));
    
    // Main loop that continues until we call window.close()
    while (HAPI.Update())
    {
        // We process the pending push or pop.
        if (m_popScene)
            PopScene();
        if (m_pushScene)
            PushScene();

        m_globalClock = HAPI.GetTime();

        if (m_globalClock >= m_updateClock + updatedelay)
        {
            // We update and render the scene on top of the stack.
            m_scenes.top()->Update();     

            m_updateClock = HAPI.GetTime();
        }

        // We get the window to display its contents.
        m_scenes.top()->Render((m_globalClock - m_updateClock) / updatedelay);
    }
}

// This function returns the graphics system
Graphics* Application::GetGraphics() const
{
    return m_graphics.get();
}

// This function returns the sound system
SoundManager* Application::GetSound() const
{
    return m_sound.get();
}

// This function returns the input system
Input* Application::GetInput() const
{
    return m_input.get();
}
