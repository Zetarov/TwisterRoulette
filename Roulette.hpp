#ifndef ROULETTE_HPP
#define ROULETTE_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Roulette : public sf::Drawable{
protected:
  sf::Texture* texture;

  sf::IntRect rouletteRect;
  sf::Sprite rouletteSprite;
  const unsigned int rouletteBaseAngle; //orientation de base de l'angle en degré par rapport au cercle trigo.

  sf::IntRect needleRect;
  sf::Sprite needleSprite;
  const unsigned int needleBaseAngle; //orientation de base de l'angle en degré par rapport au cercle trigo.

  sf::Clock clock;
  sf::Time rotatingLength;
  sf::Time lastTick;
  sf::Time ticksLength;

  bool isLaunch;
  bool quadraticSpeedEnabled;

  const unsigned int choiceNumber;

  //getters
  float getRotateNeedleCallsForARevolution() const;
  float getQuadraticDecreasingSpeed();

  //methods
  void rotateNeedle(float times);
  void rotateNeedleManually(float times, float speed);
  void reset();

  unsigned int speed;



public:
  //constructors
  Roulette(sf::Texture* texture, unsigned int choiceNumber,
    sf::IntRect const& rouletteRect, unsigned int rouletteBaseAngle,
    sf::IntRect const& needleRect, unsigned int needleBaseAngle);

  //getters
  sf::Vector2f getPosition() const;
  unsigned int getSpeed() const;
  sf::Time getTimeForARevolution() const;

  //setters
  void setPosition(sf::Vector2f);
  void setSpeed(unsigned int speed);

  //methods
  void centerInRect(sf::FloatRect const& rect);
  bool launch();
  void stop();
  bool launchAndStopIn(sf::Time time);
  bool launchAndStopRandomly(unsigned int fullRevolutionNumber);
  bool launchAndStopRandomlyQuadratic();
  void update();

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
