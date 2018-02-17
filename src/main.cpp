#include "fmt/format.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "json.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int func() { return 0; }

// Main tests that every library works!
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), fmt::format("Title{}", 4));

    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    nlohmann::json hello;
    hello["Main"] = 42;

    std::cout << hello;

    while (window.isOpen()) {
	    sf::Event event;
	    while (window.pollEvent(event)) {
		    ImGui::SFML::ProcessEvent(event);
		    if (event.type == sf::Event::Closed) {
			    window.close();
			}
		}

	    ImGui::SFML::Update(window, sf::Time(sf::seconds(1.f / 60.f)));

	    ImGui::Begin("Window Title");
	    ImGui::Button("HELLO I WORK");
	    ImGui::End();

	    window.clear();
	    window.draw(shape);
	    ImGui::SFML::Render(window);
	    window.display();
	}

    ImGui::SFML::Shutdown();

    return 0;
}
