#include "PCH.h"
#include "ServiceLocator.h"
#include "SFMLResourcesProvider.h"
#include "ObjectManager.h"
#include "MenuItem.h"
#include "InputHandler.h"

int main()
{
    //Logic
    bool isRunning(true);

    SFMLResourcesProvider texProvider;
    ServiceLocator::RegisterServiceLocator(&texProvider);

    ObjectManager objManager;
    ServiceLocator::RegisterServiceLocator(&objManager);

    MenuItem sideMenu("UI\\uiSidePanelBackground.png",50,50);
    MenuItem::ElementsBox* box = sideMenu.AddElementsBox("ElementsPanel",40,30,sf::Vector2u(245,100),sf::Vector2u(50,50),10,"UI\\uiSidePanelButtonBackground.png"/*,"UI\\uiSidePanelButtonHighlight.png"*/);

    for (int i(0);i < 20;i++) {
        box->AddElement(MenuItem::ElementsBox::Button,MenuItem::ElementsBox::OpenMenu,"Test","MainFont.ttf",20,255,255,255);
    }

    ServiceLocator::GetObjectManager()->RegisterMenuItem("sideMenu",&sideMenu);

    //Fixed logic speed
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    sf::Time ups = sf::seconds(1.f/60.f);

    //Render
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);
    ServiceLocator::RegisterServiceLocator(&window);

    while (isRunning == true) {
        while (window.isOpen()) {
            //Logic
            while (accumulator > ups) {
                InputHandler::Update();

                if (InputHandler::GetButtonState(sf::Mouse::Right) == InputHandler::Pressed) {
                    box->AddElement(MenuItem::ElementsBox::Button,MenuItem::ElementsBox::OpenMenu,"UI\\uiIconBuilding.png");
                }

                ServiceLocator::GetResourcesProvider()->UpdateResources();
                ServiceLocator::GetObjectManager()->UpdateMenuItems();

                accumulator -= ups;
            }

            // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
            sf::Event event;
            while (window.pollEvent(event))
            {
                // fermeture de la fenêtre lorsque l'utilisateur le souhaite
                if (event.type == sf::Event::Closed) {
                    window.close();
                    isRunning = false;
                }
            }

            //Render
            window.clear(sf::Color::Black);

            // c'est ici qu'on dessine tout
            ServiceLocator::GetObjectManager()->DrawMenuItems();

            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();

            accumulator += clock.restart();
        }
    }

    return 0;
}
