#include <iostream>
#include <vector>
#include "unit.hpp"
#include "collider.hpp"

Unit::Unit(sf::Texture texture, sf::Vector2f pos, Enums::Teams team, Attributes attributes)
{
    // set original position
    this->originalPos = pos;

    // setup priorityStack
    this->actionStack.push( PAUSE );
    
    // setup member vars
    this->attributes = attributes;
    this->hp = attributes.max_hp;
    this->team = team;

    /* TODO remove this temporary sizing
    sf::Vector2f sizeVec;
    sizeVec.x = 20.0f;
    sizeVec.y = 20.0f;
    
    */

    // setup body rectangle
    this->body.setTexture(&texture);
    
    sf::Vector2f sizeVec;
    const sf::IntRect texRect = body.getTextureRect();
    sizeVec.x = texRect.width;
    sizeVec.y = texRect.height;
   
    this->body.setSize(sizeVec);   
    this->body.setOrigin(sizeVec / 2.0f);
    this->body.setPosition(pos);

    // setup vision circle
    this->vision.setRadius(attributes.visionRadius);
    this->vision.setOrigin(attributes.visionRadius, attributes.visionRadius);
    this->vision.setPosition(pos);

    // setup range circle
    this->range.setRadius(attributes.attackRadius);
    this->range.setOrigin(attributes.attackRadius, attributes.attackRadius);
    this->range.setPosition(pos);

    // color
    sf::Color rColor(0, 255, 0);
    rColor.a = 100;
    sf::Color vColor(0, 0, 255);
    vColor.a = 50;
    this->body.setFillColor(sf::Color::Red);
    this->range.setFillColor(rColor);
    this->vision.setFillColor(vColor);
}

// TODO deprecate
bool Unit::shouldDie()
{
    if (actionStack.empty() == false)
        if (actionStack.top() == DYING)
            return true;
    return false;
}

bool Unit::isLiving()
{
    if (this->hp > 0) return true;
    return false;
}

bool Unit::hasTarget()
{
    if (target != nullptr)
    {
        return true;
    }
    return false;
}

bool Unit::targetInRange()
{
    if (!hasTarget()) return false;
    Collider targetCollider = target->getCollider();
    return getCollider().checkRangeCollision(targetCollider);
}

void Unit::step()
{
    Action topAct = actionStack.top();
    
    // check if unit is not paused
    if (topAct != PAUSE)
    {

        // check if unit should be dying
        if (!isLiving())
        {
            // make dying if not already dying
            if (topAct != DYING)
                actionStack.push( DYING );
        }
        else // unit is alive
        {
        // priorityStack logic
        if (!actionStack.empty())
        {
            switch (topAct)
            {
                // move forward`
                case MARCH:
                {
                    if (team == Enums::LEFT)
                    {
                        body.move(attributes.moveSpeed, 0);
                    } else if (team == Enums::RIGHT)
                    {
                        body.move(-attributes.moveSpeed, 0);
                    }
                    break;
                }
                // move towards another unit in vision
                case MOVE:
                {
                    if (isLiving() && hasTarget() && target->isLiving())
                    {
                        if (targetInRange())
                        {
                            actionStack.pop();
                            actionStack.push( ATTACK );
                        }
                        else
                        {
                            // movement towards target
                            sf::Vector2f dir = target->getPosition() - getPosition();
                            body.move((attributes.moveSpeed / 200) * dir);
                        }
                    }
                    else
                    {
                        // idk what im doing here lmao
                        target = nullptr;
                        actionStack.pop();
                    }
                    break;
                }
                case ATTACK:
                {
                    if (isLiving() && hasTarget())
                    {
                        if (target->isLiving())
                        {
                            attack(target);
                        }
                        else
                        {
                            // target is dying, stop targeting
                            target = nullptr;
                            actionStack.pop();
                        }
                    }
                    else
                    {
                        // idk what im doing here lmao
                        actionStack.pop();
                    }
                    break;
                }
                case DYING:
                {
                    // do nothing, maybe show a death animation?
                    break;
                }
            }
        } 
        else
        {
            std::cout << "THIS SHOULD NEVER TRIGGER" << std::endl;
        }
    }

    // update pos
    sf::Vector2f curPos = body.getPosition();
    range.setPosition(curPos);
    vision.setPosition(curPos);
    } 
}

void Unit::draw(sf::RenderWindow &window)
{
    // draw shapes
    window.draw(body);
    window.draw(range);
    window.draw(vision);
}

void Unit::start()
{
    if (actionStack.top() == PAUSE)
    {
        if (actionStack.top() != MARCH)
        {
            actionStack.push( MARCH );
        }
    }
}

void Unit::pause()
{
    actionStack.push( PAUSE );
}

void Unit::reset()
{
    while (actionStack.empty())
    {
        actionStack.pop();
    } 
    pause();
    body.setPosition(originalPos);
    range.setPosition(originalPos);
    vision.setPosition(originalPos);
}

bool Unit::advanceTarget()
{
    if (target != nullptr)
    {
        actionStack.push( MOVE );
        return true;
    }
    return false;
}
