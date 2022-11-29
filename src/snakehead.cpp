#include "..\header\snakehead.h"

SnakeHead::SnakeHead()
:Snake()
{
   m_texture.loadFromFile("Resources\\Textures\\greenMarble.png");
   m_sprite.setTexture(m_texture);

   m_size = m_sprite.getTexture()->getSize().x * 0.5f;
   m_sprite.setOrigin(m_size, m_size);
}

SnakeHead::SnakeHead(float xPos, float yPos, float xVel, float yVel)
:Snake(xPos, yPos, xVel, yVel)
{
   m_texture.loadFromFile("Resources\\Textures\\greenMarble.png");
   m_sprite.setTexture(m_texture);

   m_size = m_sprite.getTexture()->getSize().x * 0.5f;
   m_sprite.setOrigin(m_size, m_size);
}

SnakeHead::SnakeHead(SnakeHead* head)
:Snake(head->getXpos(), head->getYpos(), head->getXvel(), head->getYvel())
{
   this->m_texture = *head->getTexture();
   this->m_sprite.setTexture(this->m_texture);

   this->m_size = this->m_sprite.getTexture()->getSize().x * 0.5f;
   this->m_sprite.setOrigin(this->m_size, this->m_size);
}

SnakeHead::~SnakeHead()
{

}

void
SnakeHead::Update()
{

}

void
SnakeHead::Draw(RenderWindow& window)
{
   m_sprite.setPosition(round(getXpos()), round(getYpos()));

   window.draw(m_sprite);
}
