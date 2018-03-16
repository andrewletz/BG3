#include <iostream>
#include <vector>
#include "unit.hpp"
#include "collider.hpp"
#include "healthbar.hpp"

Unit::Unit(sf::Texture* texture, sf::Vector2f pos, Enums::Teams team, Attributes attributes) : healthBar(attributes.max_hp), attackTime(0.f)
{
    // set original position
    this->originalPos = pos;

    // setup priorityStack
    this->actionStack.push(MARCH);
    
    // setup member vars
    this->attributes = attributes;
    this->hp = attributes.max_hp;
    this->team = team;
    this->origViewV = attributes.visionRadius;
    
    // setup body rectangle
    this->body.setTexture(texture);
    if (team == Enums::RIGHT) {
        if (attributes.max_hp != 500) {
            this->body.scale(-1.f, 1.f); 
        }
    }
    
    sf::Vector2f sizeVec;
    const sf::IntRect texRect = body.getTextureRect();
    sizeVec.x = texRect.width * attributes.bodyScale;
    sizeVec.y = texRect.height * attributes.bodyScale;
   
    this->body.setSize(sizeVec);   
    this->body.setOrigin(sizeVec / 2.0f);
    this->body.setPosition(originalPos);

    // setup vision circle
    this->vision.setRadius(attributes.visionRadius);
    this->vision.setOrigin(attributes.visionRadius, attributes.visionRadius);
    this->vision.setPosition(originalPos);

    // setup range circle
    this->range.setRadius(attributes.attackRadius);
    this->range.setOrigin(attributes.attackRadius, attributes.attackRadius);
    this->range.setPosition(originalPos);

    // color
    sf::Color rColor(0, 255, 0);
    rColor.a = 100;
    sf::Color vColor(0, 0, 255);
    vColor.a = 50;
    this->range.setFillColor(sf::Color::Transparent);
    this->vision.setFillColor(sf::Color::Transparent);
}

bool Unit::isLiving()
{
    if (actionStack.top() == DYING) return false;
    return true;
}

bool Unit::hasTarget()
{
    if (target != nullptr) return true;
    return false;
}

bool Unit::targetInRange()
{
    if (!hasTarget()) return false;
    Collider targetCollider = target->getCollider();
    return getCollider().checkRangeCollision(targetCollider);
}

std::string ActionAs[5] = { "DYING", "MARCH", "MOVE", "ATTACK", "PAUSE" };

bool Unit::step(const float dt)
{
    this->attackTime += dt;
    Action topAct = this->actionStack.top();
    //std::cout << "stack len = " << actionStack.size() << std::endl;
    // check if unit is not paused
    if (topAct != PAUSE)
    {
        //std::cout << "unit action = " << ActionAs[topAct] << std::endl;
        // check if unit should be dying
        if (this->hp < 1)
        {
            // make dying if not already dying, this only triggers once
            if (topAct != DYING) {
                this->actionStack.push( DYING );
                return true;
            }
        }
        
        // priorityStack logic
        if (!this->actionStack.empty())
        {
            switch (topAct)
            {
                // move forward`
                case MARCH:
                {
                    if (team == Enums::LEFT)
                    {
                        body.move(dt * attributes.moveSpeed, 0);
                        if (this->body.getPosition().x > 1200) {
                            globalViewR();
                        } else {
                            originalViewR();
                        }
                    } else if (team == Enums::RIGHT)
                    {
                        body.move(dt * -attributes.moveSpeed, 0);
                        if (this->body.getPosition().x < 200) {
                            globalViewR();
                        } else {
                            originalViewR();
                        }
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
                            body.move(dt * (attributes.moveSpeed / 80) * dir);
                        }
                    }
                    else
                    {
                        // catch lack of target
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
                            if (this->attackTime > this->attributes.attackSpeed) {
                                attack(target);
                                this->attackTime = 0.f;
                            }
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
                        // catch lack of target
                        actionStack.pop();
                    }
                    break;
                }
                case DYING:
                {
                    //std::cout << "a unit is dead" << std::endl;
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

    return false;
}

void Unit::draw(sf::RenderWindow &window)
{
    // draw shapes
    window.draw(body);
    window.draw(range);
    window.draw(vision);
    healthBar.draw(hp, body.getPosition(), window);
}

void Unit::reset()
{
    while (!this->actionStack.empty()) {
        this->actionStack.pop();
    }
    this->body.setPosition(originalPos);
    this->range.setPosition(originalPos);
    this->vision.setPosition(originalPos);
    originalViewR();
    this->target = nullptr;
    this->hp = this->attributes.max_hp;
    this->actionStack.push(MARCH);
}

bool Unit::advanceTarget()
{
    if (target != nullptr) {
        this->actionStack.push( MOVE );
        return true;
    }
    return false;
}

void Unit::globalViewR()
{
    this->vision.setRadius(1000);
}

void Unit::originalViewR()
{
    this->vision.setRadius(origViewV);
}
