#include "Roulette.hpp"

//private - getters

float Roulette::getRotateNeedleCallsForARevolution() const
{
    return (360/speed);
}

float Roulette::getQuadraticDecreasingSpeed()
{
  float translatedLeft(clock.getElapsedTime().asSeconds()-rotatingLength.asSeconds());
  return translatedLeft*translatedLeft*speed;
}

//private - methods
void Roulette::rotateNeedle(float times)
{
    rotateNeedleManually(times, speed);
}

void Roulette::rotateNeedleManually(float times, float speed)
{
    needleSprite.rotate(times*speed);
}

void Roulette::reset()
{
    clock.restart();
    lastTick = sf::seconds(0.0);
}

//constructors
Roulette::Roulette(sf::Texture* texture, unsigned int choiceNumber,
  sf::IntRect const& rouletteRect, unsigned int rouletteBaseAngle,
  sf::IntRect const& needleRect, unsigned int needleBaseAngle):
  texture(texture),
  rouletteBaseAngle(rouletteBaseAngle), needleBaseAngle(needleBaseAngle),
  isLaunch(false),
  choiceNumber(choiceNumber)

{
  rouletteSprite.setTexture(*texture);
  needleSprite.setTexture(*texture);

  rouletteSprite.setTextureRect(rouletteRect);
  needleSprite.setTextureRect(needleRect);

  //On place le point d'origine au centre.
  rouletteSprite.setOrigin(rouletteSprite.getGlobalBounds().width/2,
    rouletteSprite.getGlobalBounds().height/2);
  needleSprite.setOrigin(needleSprite.getGlobalBounds().width/2,
    needleSprite.getGlobalBounds().height/2);

  lastTick = sf::seconds(0.0);
  ticksLength = sf::seconds(0.05);

  speed = 1;
  quadraticSpeedEnabled = true;
}

//getters
sf::Vector2f Roulette::getPosition() const
{
  return rouletteSprite.getPosition();
}

unsigned int Roulette::getSpeed() const
{
  return speed;
}

sf::Time Roulette::getTimeForARevolution() const
{
  return getRotateNeedleCallsForARevolution()*ticksLength;
}

//setters
void Roulette::setPosition(sf::Vector2f position)
{
  rouletteSprite.setPosition(position);
  needleSprite.setPosition(position);
}

void Roulette::setSpeed(unsigned int speed)
{
  this->speed=speed;
}

//methods

void Roulette::centerInRect(sf::FloatRect const& rect)
{
  sf::Vector2f newPos(rect.width/2+rect.left, rect.height/2+rect.top);
  rouletteSprite.setPosition(newPos);
  needleSprite.setPosition(newPos);
}

bool Roulette::launch()
{
  if(isLaunch) return false;
  reset();
  rotatingLength = sf::seconds(0.0);
  isLaunch = true;
  return true;
}
#include <iostream>
void Roulette::stop()
{
  if(!isLaunch) return;
  isLaunch = false;
  //TODO surligner la zone où s'est arrêtée l'aiguille.
}

bool Roulette::launchAndStopIn(sf::Time time)
{
  if(isLaunch) return false;
  reset();
  rotatingLength = time;
  isLaunch = true;

  return true;
}

//fullRevolution --> number of fullRevolution wanted.
bool Roulette::launchAndStopRandomly(unsigned int fullRevolution)
{
  if(isLaunch) return false;
  quadraticSpeedEnabled = false;
  float revolutionTime(getTimeForARevolution().asSeconds());
  float lastRevPercentage((rand()%360)/360.0);
  float necessarySeconds(revolutionTime*fullRevolution+revolutionTime*lastRevPercentage);
  int randomStart;

  randomStart=rand()%(speed%361)-rand()%(speed%361); //To avoid side effect of speed (can block on certain values)

  rotateNeedleManually(randomStart, 1);
  launchAndStopIn(sf::seconds(necessarySeconds)); // revolutionTime*fullRevolution+revolutionTime*rand()%360)

  //TODO animation d'arrivée qui montre la partie sélectionnée de la roue

  return true;
}

bool Roulette::launchAndStopRandomlyQuadratic()
{
  if(isLaunch) return false;
  quadraticSpeedEnabled = true;

  launchAndStopIn(sf::seconds(rand()%5+3));

  return true;
}

void Roulette::update()
{
  if(!isLaunch) return;
  if(rotatingLength!=sf::seconds(0.0) &&
  clock.getElapsedTime()>rotatingLength){
    stop();
  }
  else{
    sf::Time tick(clock.getElapsedTime());
    float elapsedTicks((tick-lastTick)/ticksLength);
    if(lastTick+ticksLength<tick){
      lastTick = tick;
      if(quadraticSpeedEnabled)
        rotateNeedleManually(elapsedTicks, getQuadraticDecreasingSpeed());
      else
        rotateNeedle(elapsedTicks);
    }
  }
}

void Roulette::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // on applique la transformation
  //states.transform *= getTransform();

  // on applique la texture du tileset
  states.texture = texture;

  // et on dessine enfin les sprites.
  target.draw(rouletteSprite, states);
  target.draw(needleSprite, states);
}
