#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "brick.h"

using namespace std;

enum
{
    NOTHING,
    CROSS,
    CIRCLE
};

sf::RenderWindow window(sf::VideoMode(450, 550, 32), "Cross & Circle v 0.01", sf::Style::Close);

sf::SoundBuffer soundbuffer;
sf::Sound sound;
sf::SoundBuffer soundbuffer2;
sf::Sound error;

int CheckWinner(Brick BrickMatrix[9])
{
    if (BrickMatrix[0].GetState() == 1 && BrickMatrix[1].GetState() == 1 && BrickMatrix[2].GetState() == 1) return 1;
    if (BrickMatrix[0].GetState() == 2 && BrickMatrix[1].GetState() == 2 && BrickMatrix[2].GetState() == 2) return 2;
    if (BrickMatrix[3].GetState() == 1 && BrickMatrix[4].GetState() == 1 && BrickMatrix[5].GetState() == 1) return 1;
    if (BrickMatrix[3].GetState() == 2 && BrickMatrix[4].GetState() == 2 && BrickMatrix[5].GetState() == 2) return 2;
    if (BrickMatrix[6].GetState() == 1 && BrickMatrix[7].GetState() == 1 && BrickMatrix[8].GetState() == 1) return 1;
    if (BrickMatrix[6].GetState() == 2 && BrickMatrix[7].GetState() == 2 && BrickMatrix[8].GetState() == 2) return 2;
    if (BrickMatrix[0].GetState() == 1 && BrickMatrix[3].GetState() == 1 && BrickMatrix[6].GetState() == 1) return 1;
    if (BrickMatrix[0].GetState() == 2 && BrickMatrix[3].GetState() == 2 && BrickMatrix[6].GetState() == 2) return 2;
    if (BrickMatrix[1].GetState() == 1 && BrickMatrix[4].GetState() == 1 && BrickMatrix[7].GetState() == 1) return 1;
    if (BrickMatrix[1].GetState() == 2 && BrickMatrix[4].GetState() == 2 && BrickMatrix[7].GetState() == 2) return 2;
    if (BrickMatrix[2].GetState() == 1 && BrickMatrix[5].GetState() == 1 && BrickMatrix[8].GetState() == 1) return 1;
    if (BrickMatrix[2].GetState() == 2 && BrickMatrix[5].GetState() == 2 && BrickMatrix[8].GetState() == 2) return 2;
    if (BrickMatrix[0].GetState() == 1 && BrickMatrix[4].GetState() == 1 && BrickMatrix[8].GetState() == 1) return 1;
    if (BrickMatrix[0].GetState() == 2 && BrickMatrix[4].GetState() == 2 && BrickMatrix[8].GetState() == 2) return 2;
    if (BrickMatrix[2].GetState() == 1 && BrickMatrix[4].GetState() == 1 && BrickMatrix[6].GetState() == 1) return 1;
    if (BrickMatrix[2].GetState() == 2 && BrickMatrix[4].GetState() == 2 && BrickMatrix[6].GetState() == 2) return 2;
    if (BrickMatrix[0].GetState() != 0 && BrickMatrix[1].GetState() != 0 && BrickMatrix[2].GetState() != 0 &&
        BrickMatrix[3].GetState() != 0 && BrickMatrix[4].GetState() != 0 && BrickMatrix[5].GetState() != 0 &&
        BrickMatrix[6].GetState() != 0 && BrickMatrix[7].GetState() != 0 && BrickMatrix[8].GetState() != 0)
            return 3; // zwraca remis
    else return 0;
}

void GameOver(sf::RenderWindow &wind, int who_won)
{
    sf::Font font;
    if (!font.loadFromFile(".\\bin\\Debug\\font.ttf")) cerr << "error loading font file!\n";

    sf::Text text;
    if (who_won == 1) text.setString("Cross Won!");
    else if (who_won == 2) text.setString("Circle Won!");
    else text.setString("no winner!");
    text.setPosition(50, 100);
    text.setCharacterSize(50);
    text.setColor(sf::Color::Blue);
    text.setFont(font);

    sf::Text text2;
    text2.setString("PRESS ANY KEY");
    text2.setCharacterSize(25);
    text2.setPosition(120, 330);
    text2.setColor(sf::Color::Red);
    text2.setFont(font);

    wind.clear(sf::Color::White);
    wind.draw(text);
    wind.draw(text2);
    wind.display();
}

void Draw_Whos_Turn_It_Is(sf::RenderWindow &wind, int turn)
{
    sf::Font font;
    font.loadFromFile(".\\bin\\Debug\\font.ttf");

    sf::Text text;
    text.setCharacterSize(35);
    text.setFont(font);
    text.setPosition(90, 475);
    text.setColor(sf::Color::Red);
    if (turn == CROSS) text.setString("CROSS'S TURN");
    else text.setString("CIRCLE'S TURN");
    wind.draw(text);
}

int main(void)
{
    window.setFramerateLimit(60.f);
    soundbuffer.loadFromFile(".\\bin\\Debug\\click.flac");
    sound.setBuffer(soundbuffer);
    soundbuffer2.loadFromFile(".\\bin\\Debug\\error.wav");
    error.setBuffer(soundbuffer2);

    int turn = CROSS;

    Brick BrickMatrix[9];
    BrickMatrix[0].SetCoordinates(sf::Vector2f(0, 0));
    BrickMatrix[1].SetCoordinates(sf::Vector2f(150, 0));
    BrickMatrix[2].SetCoordinates(sf::Vector2f(300, 0));
    BrickMatrix[3].SetCoordinates(sf::Vector2f(0, 150));
    BrickMatrix[4].SetCoordinates(sf::Vector2f(150, 150));
    BrickMatrix[5].SetCoordinates(sf::Vector2f(300, 150));
    BrickMatrix[6].SetCoordinates(sf::Vector2f(0, 300));
    BrickMatrix[7].SetCoordinates(sf::Vector2f(150, 300));
    BrickMatrix[8].SetCoordinates(sf::Vector2f(300, 300));

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                unsigned int MouseX = sf::Mouse::getPosition(window).x;
                unsigned int MouseY = sf::Mouse::getPosition(window).y;
                if (MouseX > 0 && MouseX < 150 && MouseY > 0 && MouseY < 150 && BrickMatrix[0].GetState() == 0)
                    BrickMatrix[0].SetState(turn);
                if (MouseX > 150 && MouseX < 300 && MouseY > 0 && MouseY < 150 && BrickMatrix[1].GetState() == 0)
                    BrickMatrix[1].SetState(turn);
                if (MouseX > 300 && MouseX < 450 && MouseY > 0 && MouseY < 150 && BrickMatrix[2].GetState() == 0)
                    BrickMatrix[2].SetState(turn);
                if (MouseX > 0 && MouseX < 150 && MouseY > 150 && MouseY < 300 && BrickMatrix[3].GetState() == 0)
                    BrickMatrix[3].SetState(turn);
                if (MouseX > 150 && MouseX < 300 && MouseY > 150 && MouseY < 300 && BrickMatrix[4].GetState() == 0)
                    BrickMatrix[4].SetState(turn);
                if (MouseX > 300 && MouseX < 450 && MouseY > 150 && MouseY < 300 && BrickMatrix[5].GetState() == 0)
                    BrickMatrix[5].SetState(turn);
                if (MouseX > 0 && MouseX < 150 && MouseY > 300 && MouseY < 450 && BrickMatrix[6].GetState() == 0)
                    BrickMatrix[6].SetState(turn);
                if (MouseX > 150 && MouseX < 300 && MouseY > 300 && MouseY < 450 && BrickMatrix[7].GetState() == 0)
                    BrickMatrix[7].SetState(turn);
                if (MouseX >300 && MouseX < 450 && MouseY > 300 && MouseY < 450 && BrickMatrix[8].GetState() == 0)
                    BrickMatrix[8].SetState(turn);
                sound.play();
                if (turn == CROSS) turn = CIRCLE;
                else turn = CROSS;
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < 9; i++)
        {
            BrickMatrix[i].update();
            BrickMatrix[i].draw(window);
        }
        int zmienna = CheckWinner(BrickMatrix);
        Draw_Whos_Turn_It_Is(window, turn);
        window.display();
        if (zmienna != 0)
        {
            GameOver(window, zmienna);
            error.play();
            while(1)
            {
                window.pollEvent(event);
                if (event.type == sf::Event::KeyPressed) break;
            }
            for (int i = 0; i < 9; i++) BrickMatrix[i].SetState(0);
            zmienna = 0;
        }
    }

    return 0;
}
