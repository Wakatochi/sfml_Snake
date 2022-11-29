#include "..\header\pellets.h"

Pellets::Pellets()
{
   m_size = 7.5f;
   m_shape = CircleShape(m_size);
   m_shape.setFillColor(Color(255, 0, 0));

   m_value = 10;

   m_xPos = 0.0f;
   m_yPos = 0.0f;
}

Pellets::Pellets(Texture& texture)
{
   m_sprite.setTexture(texture);

   m_size = m_sprite.getTexture()->getSize().x * 0.5f;
   m_sprite.setOrigin(m_size, m_size);

   m_value = 10;

   m_xPos = 0.0f;
   m_yPos = 0.0f;
}

Pellets::~Pellets()
{

}

void
Pellets::Update()
{

}

void
Pellets::Draw(RenderWindow& window)
{
   m_shape.setPosition(m_xPos, m_yPos);
   window.draw(m_shape);
}

int
Pellets::getValue()
{
   return m_value;
}

float
Pellets::getRadius()
{
   return m_size;
}

float
Pellets::getXpos()
{
   return m_xPos;
}

float
Pellets::getYpos()
{
   return m_yPos;
}

void
Pellets::setPos(float x, float y)
{
   m_xPos = x;
   m_yPos = y;
}
