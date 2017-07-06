#include <iostream>
#include "Roulette.hpp"

int main()
{
  srand(time(0));
  sf::RenderWindow rw;
  unsigned int width(800), height(600);
  rw.create(sf::VideoMode(width, height), "TwisterRoulette", sf::Style::Close);
  rw.setFramerateLimit(60);
  sf::Texture texture; texture.setSmooth(true);
  if(!texture.loadFromFile("roulette1.png")){
    std::cerr << "Failed to load roulette1.png" << std::endl;
    return EXIT_FAILURE;
  }
  Roulette roulette1(&texture, 4,
    sf::IntRect(0, 0, 378, 378), 0,
    sf::IntRect(378, 0, 378,378), 0);
  roulette1.setSpeed(1);
  roulette1.centerInRect(sf::FloatRect(0,0,width/2,height));
  Roulette roulette2(&texture, 4,
    sf::IntRect(756, 0, 378, 378), 0,
    sf::IntRect(1134, 0, 378,378), 0);
  roulette2.setSpeed(1);
  roulette2.centerInRect(sf::FloatRect(width/2,0,width/2,height));
  while (rw.isOpen())
  {/*
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
          roulette.launch();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
          roulette.stop();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
          roulette.launchAndStopIn(sf::seconds(2.0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
          roulette.launchAndStopRandomly(5);
        }*/
        // on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
        sf::Event event;
        while (rw.pollEvent(event))
        {

            switch(event.type){
            case sf::Event::Closed:
                rw.close();
                break;


            case sf::Event::KeyPressed:
              switch(event.key.code){
                case sf::Keyboard::Left:
                  //roulette1.launch();
                  roulette1.launchAndStopIn(sf::seconds(6.0));
                  break;
                case sf::Keyboard::Right:
                  //roulette1.stop();
                  roulette2.launchAndStopIn(sf::seconds(6.0));
                  break;
                case sf::Keyboard::Up:
                  roulette1.launchAndStopRandomlyQuadratic();
                  roulette2.launchAndStopRandomlyQuadratic();
                  break;
                case sf::Keyboard::Down:
                  roulette1.launchAndStopRandomly(1);
                  roulette2.launchAndStopRandomly(1);
                  break;
              }

            break;
            }
        }

        roulette1.update();
        roulette2.update();
        rw.draw(roulette1);
        rw.draw(roulette2);
        rw.display();
        rw.clear();
    }

    return 0;
}
