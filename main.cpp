#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using std::cout;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { RIGHT, LEFT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {
    VideoMode vm(1600, 900);

    RenderWindow window(vm, "Timber");
    View view(FloatRect(0,0, 1920, 1080));
    window.setView(view);
    Texture textureBackground;

    if(!textureBackground.loadFromFile("../graphics/background.png")) {
        cout << "Could not image";
        return 0;
    }

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture textureTree;
    textureTree.loadFromFile("../graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, -180);

    Texture textureBee;
    textureBee.loadFromFile("../graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud;
    textureCloud.loadFromFile("../graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    Clock clock;

    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;

    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - (timeBarStartWidth / 2), 980);

    Time gameTotal;
    float remainingTime = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / remainingTime;

    bool paused = true;

    int score = 0;
    Text messageText;
    Text scoreText;
    Font font;
    font.loadFromFile("../fonts/KOMIKAP_.ttf");

    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    Texture textureBranch;
    textureBranch.loadFromFile("../graphics/branch.png");
    for (auto & branch : branches) {
        branch.setTexture(textureBranch);
        branch.setPosition(-2000, -2000);
        branch.setOrigin(220, 20);
    }

    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);

    while(window.isOpen()) {
        if(Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            remainingTime = 6;
        }
        if(!paused) {
            Time dt = clock.restart();
            remainingTime -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * remainingTime, timeBarHeight));

            if(remainingTime < 0.0f) {
                paused = true;
                messageText.setString("Out of time!! Press Start to restart");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            if(!beeActive) {
                srand((int) time(0));
                beeSpeed = (rand() % 200) + 200;

                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);

                beeActive = true;
            } else {
                spriteBee.setPosition(
                        spriteBee.getPosition().x -
                        (beeSpeed * dt.asSeconds()),
                        spriteBee.getPosition().y);
                if (spriteBee.getPosition().x < -100)
                {
                    beeActive = false;
                }
            }
            if (!cloud1Active)
            {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                cloud1Active = true;
            } else {
                spriteCloud1.setPosition(
                        spriteCloud1.getPosition().x +
                        (cloud1Speed * dt.asSeconds()),
                        spriteCloud1.getPosition().y);
                if (spriteCloud1.getPosition().x  > 1920)
                {
                    cloud1Active = false;
                }
            }
            if (!cloud2Active )
            {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);
                cloud2Active = true;
            } else {
                spriteCloud2.setPosition(
                        spriteCloud2.getPosition().x +
                        (cloud2Speed * dt.asSeconds()),
                        spriteCloud2.getPosition().y);
                if (spriteCloud2.getPosition().x  > 1920)
                {
                    cloud2Active = false;
                }
            }
            if (!cloud3Active)
            {
                srand((int)time(0) * 30);
                cloud3Speed= (rand() % 200);
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;
            } else {
                spriteCloud3.setPosition(
                        spriteCloud3.getPosition().x +
                        (cloud3Speed * dt.asSeconds()),
                        spriteCloud3.getPosition().y);
                if (spriteCloud3.getPosition().x  > 1920)
                {
                    cloud3Active = false;
                }
            }
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
            for (int i = 0; i < NUM_BRANCHES; i++) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                } else if (branchPositions[i] == side::RIGHT) {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                } else {
                    branches[i].setPosition(3000, height);
                }
            }
        }
        window.clear();


        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        for (auto & branch: branches) {
            window.draw(branch);
        }

        window.draw(spriteTree);

        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);
        if(paused) {
            window.draw(messageText);
        }
        window.display();
    }
    return 0;
}

void updateBranches(int seed) {
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }
    srand(time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}
