#include "..\header\snake.h"

Snake::Snake()
{
   m_size = 0.0f;

   m_xVel = 0.0f;
   m_yVel = 0.0f;
   m_xPos = 0.0f;
   m_yPos = 0.0f;
}

Snake::Snake(float xPos, float yPos, float xVel, float yVel)
{
   m_size = 0.0f;

   m_xPos = xPos;
   m_yPos = yPos;
   m_xVel = xVel;
   m_yVel = yVel;
}

Snake::~Snake()
{

}

void
Snake::Update()
{

}

void
Snake::Draw(RenderWindow& window)
{
   window.draw(m_sprite);
}

bool
Snake::checkWallCollition()
{
   return false;
}

bool
Snake::checkBodyCollition(Snake body)
{
   return false;
}

void
Snake::setXpos(float x)
{
   m_xPos = x;
}

void
Snake::setYpos(float y)
{
   m_yPos = y;
}

void
Snake::setXvel(float xVel)
{
   m_xVel = xVel;
}

void
Snake::setYvel(float yVel)
{
   m_yVel = yVel;
}

void
Snake::setPos(float x, float y)
{
   m_xPos = x;
   m_yPos = y;
}

void
Snake::setVel(float x, float y)
{
   m_xVel = x;
   m_yVel = y;
}

float
Snake::getXpos()
{
   return m_xPos;
}

float
Snake::getYpos()
{
   return m_yPos;
}

float
Snake::getXvel()
{
   return m_xVel;
}

float
Snake::getYvel()
{
   return m_yVel;
}

float
Snake::getRadius()
{
   return m_size;
}

Texture*
Snake::getTexture()
{
   return &m_texture;
}

float
Snake::getLengthFromPrev(Snake body)
{
   float deltaX = body.getXpos() - getXpos();
   float deltay = body.getYpos() - getYpos();

   float absLength = powf(deltaX, 2.0f) + powf(deltay, 2.0f);

   return absLength;
}

float
Snake::getTotalRadiusFromPrev(Snake body)
{
   float radiusTot = powf(getRadius() + body.getRadius(), 2.0f);

   return radiusTot;
}
