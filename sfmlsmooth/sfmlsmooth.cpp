#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "ScaleAnimation.h"
#include "PositionAnimation.h"
#include "RotationAnimation.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "animation showcase", sf::Style::Default, settings);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    sf::RectangleShape r1;
    r1.setPosition(200, 200);
    r1.setSize(sf::Vector2f(20,20));

    sf::Font font;
    font.loadFromFile("DejaVuSans-Bold.ttf");
    sf::Text t1;
    t1.setFont(font);
    t1.setPosition(100, 100);
    t1.setString("farts, etc");
    t1.setScale(1, 1);

    Animation* scale = new ScaleAnimation(&r1, AnimationType::LINEAR, { 1.5,1.5 }, 100);
    Animation* pos = new PositionAnimation(&r1, AnimationType::LINEAR, { 300,200 }, 100);
    Animation* rot = new RotationAnimation(&r1, AnimationType::LINEAR, 360, 100);

    std::vector<Animation*> animations;
    animations.push_back(pos);
    animations.push_back(scale);
    animations.push_back(rot);

    bool hasBeenPress = 0;

    const char* items[] = { "position", "scale", "rotation"};
    int item_current = 0;

    int steps = 100;
    /*float f0 = 0.001f;
    ImGui::InputFloat("input float", &f0, 0.01f, 1.0f, "%.3f");*/
    int posX = t1.getPosition().x;
    int posY = t1.getPosition().y;

    float scaleX = 1;
    float scaleY = 1;

    float rotation = 360.0f;

    std::string buttonText = "start animation";

    while (window.isOpen())
    {
        window.setFramerateLimit(100);

        if (hasBeenPress) {
            for (Animation* a : animations) {
                a->iterate();
            }
            if (animations[0]->isFinished()) {
                hasBeenPress = 0;
                buttonText = "start animation";
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("animation gui");
            ImGui::Text("mouse x: %d y: %d", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            ImGui::Text("animation type:");
            ImGui::ListBox("", &item_current, items, IM_ARRAYSIZE(items), 3);
            if (item_current == 0) {
                ImGui::InputInt("x pos", &posX, 1, 100);
                ImGui::InputInt("y pos", &posY, 1, 100);
                ImGui::InputInt("steps", &steps, 1, 100);
            }
            else if (item_current == 1) {
                ImGui::InputFloat("x scale", &scaleX, 1, 100);
                ImGui::InputFloat("y scale", &scaleY, 1, 100);
                ImGui::InputInt("steps", &steps, 1, 100);
            }
            else if (item_current == 2) {
                ImGui::InputFloat("rotation", &rotation, 1, 100);
                ImGui::InputInt("steps", &steps, 1, 100);
            }
            if (ImGui::Button(buttonText.c_str())) {
                if (hasBeenPress) {
                    buttonText = "start animation";
                }
                else {
                    buttonText = "stop animation";
                }
                hasBeenPress = !hasBeenPress;
                animations[0] = new PositionAnimation(&r1, AnimationType::LINEAR, sf::Vector2f(posX,posY), steps);
                animations[1] = new ScaleAnimation(&r1, AnimationType::LINEAR, {scaleX, scaleY}, steps);
                animations[2] = new RotationAnimation(&r1, AnimationType::LINEAR, rotation, steps);
            }
        ImGui::End();

        ImGui::Begin("transform info");
            ImGui::Text("pos x: %f y: %f", r1.getPosition().x, r1.getPosition().y);
            ImGui::Text("scale x: %f y: %f", r1.getScale().x, r1.getScale().y);
            ImGui::Text("rot: %f", r1.getRotation());
        ImGui::End();

        window.clear(sf::Color::Black);
        window.draw(r1);
        ImGui::SFML::Render(window);
        //window.draw(r1);
        window.display();
    }

    for (Animation* a : animations) {
        delete a;
    }
    ImGui::SFML::Shutdown();

    return 0;
}