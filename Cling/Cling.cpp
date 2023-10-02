#include "Cling.h"


Cling::App app;
void Cling::CLingApp()
{
    sf::RenderWindow window{ sf::VideoMode(1080, 700), "Cling" };
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    auto fancyFont = io.Fonts->AddFontFromFileTTF(
        "./Data/Font/Montserrat-Regular.ttf", 20);
    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "No luck\n";
    }
    app.Init();
    ImGui::Helper::DarkMode();

    sf::Clock deltaClock{};
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());



        ImGui::PushFont(fancyFont);
        ImGui::DockSpaceOverViewport();
        app.Run();
        ImGui::PopFont();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
