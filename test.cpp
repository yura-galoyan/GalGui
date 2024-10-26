
#include <SFML/Graphics.hpp>

#include <GalGui/Label.hpp>

#include <GalGui/VerticalLayout.hpp>
#include <GalGui/MainWindow.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/Menu.hpp>

#include <GalGui/Gui.hpp>
#include <GalGui/EditLine.hpp>
#include <GalGui/Button.hpp>
#include <GalGui/SystemDialog.hpp>

int main()
{
    sf::RenderWindow window{sf::VideoMode{1280,720},"Gui test"};

    GalGui::Gui gui;

    sf::Event event;

    GalGui::Widget::Menu* menu = new GalGui::Widget::Menu;
    menu->setGlobalPosition(sf::Vector2f(0,0));
    menu->setInitialSize(sf::Vector2f(60,20));
    menu->setFont(gui.getDefaultFont());
    menu->setTitle("File");
    menu->append("Open");
    menu->append("Second");
    menu->append("Third");
    menu->getActionByName("Open").linkToClicked([](){ 
            GalGui::SystemDialog::messageBox( L"Test name", L"Test description", GalGui::SystemDialog::InfoDialog );
        });

    GalGui::Widget::Menu* menu1 = new GalGui::Widget::Menu;
    menu1->setGlobalPosition(sf::Vector2f(0,0));
    menu1->setInitialSize(sf::Vector2f(60,20));
    menu1->setFont(gui.getDefaultFont());
    menu1->setTitle("Info");
    menu1->append("Open");
    menu1->append("Second");
    menu1->append("Third");

    GalGui::Widget::MainWindow* mw = new GalGui::Widget::MainWindow;

    mw->addMenu(menu);
    mw->addMenu(menu1);
    gui.add(mw);

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            gui.handleEvents(window, event);
            
        }

        window.clear();

        window.draw(gui);

        window.display();
    }
}



// #include <SFML/Graphics.hpp>

// #include <SFML/Window/Keyboard.hpp>

// #include <utility>

// #include <iostream>

// struct LightVectors
// {
//     std::vector<sf::Vector2f> positions;
//     std::vector<float> rads;
//     std::vector<sf::Glsl::Vec3> colors;
// };

// int main()
// {
//     // Create a window
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Lighting");
//     sf::View view = window.getDefaultView();
//     // Load a texture and create a sprite
//     sf::Texture texture;
//     if (!texture.loadFromFile("npc1idle.png"))
//         return -1;

//     sf::Sprite sprite(texture);
//     sprite.setPosition(0,0);

//     // Load the shader
//     sf::Shader shader;
//     if (!shader.loadFromFile("light.frag", sf::Shader::Fragment))
//         return -1;

//     // Set initial light properties
//     sf::Vector2f lightPosition(400, 300);  // Light at the center of the screen
//     float lightRadius = 200.0f;
//     sf::Color lightColor(255, 255, 255);  // White light

//     bool light{true};

//     LightVectors lightVector;

//     lightVector.colors.push_back({ 1.0f, 1.0f, 1.0f });
//     lightVector.positions.push_back(sf::Vector2f(0.f,0.f));
//     lightVector.rads.push_back(200.f);


//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {

//             if (event.type == sf::Event::Closed)
//                 window.close();
//             if(event.type == sf::Event::KeyPressed)
//                 if(event.key.code == sf::Keyboard::Key::H)
//                     light = !light;
//             if(event.type == sf::Event::MouseButtonPressed)
//             {
//                 std::cout << "added color" << std::endl;
//                 lightVector.colors.push_back({1.0f, 1.0f, 1.0f});
//                 auto pos = sf::Vector2f(sf::Mouse::getPosition(window));
//                 pos.y = 600 - pos.y;
//                 lightVector.positions.push_back(pos);
//                 lightVector.rads.push_back(400.f);
//             }
//         }

//         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
//             view.move(-1,0);
//         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
//             view.move(0,-1);
//         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
//             view.move(0,1);
//         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//             view.move(1,0);
        
//         // Set shader uniforms
//         shader.setUniformArray("lightPositions",std::as_const(lightVector.positions).data(),lightVector.colors.size());
//         shader.setUniformArray("lightRadii", std::as_const(lightVector.rads).data(),lightVector.colors.size());
//         shader.setUniformArray("lightColors", std::as_const(lightVector.colors).data(),lightVector.colors.size());
//         shader.setUniform("lightCount", static_cast<int>(lightVector.colors.size()));

//         // Clear the window
//         window.clear();
//         window.setView(view);
//         if(light)
//             window.draw(sprite, &shader);
//         else
//             window.draw(sprite);

//         // Display the window
//         window.display();
//     }

//     return 0;
// }