#include "..\header\snakebody.h"

SnakeBody::SnakeBody()
:Snake()
{
//   m_texture.loadFromFile("Resources\\Textures\\blueMarble.png");
//   m_sprite.setTexture(m_texture);

   m_size = m_sprite.getTexture()->getSize().x * 0.5f;
   m_sprite.setOrigin(m_size, m_size);

   m_useVelocity = false;
}

SnakeBody::SnakeBody(float xPos, float yPos, float xVel, float yVel, Texture& texture)
:Snake(xPos, yPos, xVel, yVel)
{
//   m_texture.loadFromFile("Resources\\Textures\\blueMarble.png");
   m_texture = texture;
   m_sprite.setTexture(texture);

   m_size = m_sprite.getTexture()->getSize().x * 0.5f;
   m_sprite.setOrigin(m_size, m_size);

   m_useVelocity = false;
}

SnakeBody::SnakeBody(SnakeBody* body)
:Snake(body->getXpos(), body->getYpos(), body->getXvel(), body->getYvel())
{
   this->m_texture = *body->getTexture();
   this->m_sprite.setTexture(this->m_texture);

   this->m_size = this->m_sprite.getTexture()->getSize().x * 0.5f;
   this->m_sprite.setOrigin(this->m_size, this->m_size);
   this->m_useVelocity = body->getUseVelocityVector();
}

SnakeBody::~SnakeBody()
{

}

void
SnakeBody::Update()
{

}

void
SnakeBody::Draw(RenderWindow& window)
{
   m_sprite.setPosition(round(getXpos()), round(getYpos()));

   window.draw(m_sprite);
}

void
SnakeBody::setUseVelocityVector(bool speedVector)
{
   m_useVelocity = speedVector;
}

bool
SnakeBody::getUseVelocityVector()
{
   return m_useVelocity;
}
