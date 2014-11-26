#include "Entity.h"

void Entity::bindSprite( CCSprite* sprite ) {
    this->sprite = sprite;
    addChild(sprite);
}