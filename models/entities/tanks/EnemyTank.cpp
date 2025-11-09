#include "../../../headers/entities/tanks/EnemyTank.h"

#include <random>

EnemyTank::EnemyTank(const int health, const int damage, floatPair position, const float rotation)
    : ITank(health, damage, std::move(position), rotation)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution randomState(0, static_cast<int>(EnemyState::COUNT) - 1);

    m_state = static_cast<EnemyState>(randomState(gen));
}

bool EnemyTank::isFacingPlayer(const std::unique_ptr<ITank> &playerTank, const float tolerance) {
    const auto [enemyX, enemyY] = this->getPosition();
    const auto [playerX, playerY] = playerTank->getPosition();

    const float x = playerX - enemyX;
    const float y = playerY - enemyY;

    float radians = this->getRotation() * M_PI / 180.0f;
    float facingX = std::cos(radians);
    float facingY = std::sin(radians);

    float distance = std::sqrt(x * x + y * y);
    if (distance < 0.001f) return true;

    float directionX = x / distance;
    float directionY = y / distance;

    float dotProduct = facingX * directionX + facingY * directionY;

    float aimPrecision = std::cos(tolerance * M_PI / 180.0f);

    return dotProduct >= aimPrecision;
}

void EnemyTank::rotateToPlayer(const std::unique_ptr<ITank>& playerTank, const float rotationValue) {
    if (!isFacingPlayer(playerTank, 6.0f)) {
        floatPair enemyPos = this->getPosition();
        floatPair playerPos = playerTank->getPosition();

        float x = playerPos.first - enemyPos.first;
        float y = playerPos.second - enemyPos.second;

        float radians = this->getRotation() * M_PI / 180.0f;
        float facingX = std::cos(radians);
        float facingY = std::sin(radians);

        float cross = facingX * y - facingY * x;

        if (cross > 0) {
            this->rotate(rotationValue);
        } else {
            this->rotate(-rotationValue);
        }
    }
}

void EnemyTank::update(const std::unique_ptr<ITank> &player, const float deltaTime) {
    this->rotateToPlayer(player, ROTATION_SPEED * deltaTime);

    if (isFacingPlayer(player, 6.0f)) {
        auto projectile = this->shoot();
    }
}

bool EnemyTank::takeDamage(const int damage) {
    const int newHealth = this->getHealth() - damage;

    if (newHealth < 0) {
        return false;
    }

    this->setHealth(newHealth);
    return true;
}