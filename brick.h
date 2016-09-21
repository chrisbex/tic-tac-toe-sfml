class Brick
{
    public:
        Brick();
        Brick(sf::Vector2f x);
        void SetCoordinates(sf::Vector2f x);
        void draw(sf::RenderWindow &wind);
        sf::Vector2f GetCoordinates();
        void update();
        void SetState(int x) { state = x; };
        int GetState() { return state; };
    private:
        int state;
        bool isClicked;
        sf::Vector2f coords;
        sf::Texture BrickTex;
        sf::Sprite BrickSpr;
};

Brick::Brick()
{
    state = 0;
    coords = sf::Vector2f(0, 0);
    isClicked = false;
    BrickTex.loadFromFile(".\\bin\\Debug\\nope.png");
    BrickSpr.setTexture(BrickTex);
    BrickSpr.setPosition(coords);

}

Brick::Brick(sf::Vector2f x)
{
    state = 0;
    coords = x;
    isClicked = false;
}

void Brick::SetCoordinates(sf::Vector2f x)
{
    coords = x;
}

sf::Vector2f Brick::GetCoordinates()
{
    return coords;
}

void Brick::draw(sf::RenderWindow &wind)
{
    wind.draw(BrickSpr);
}

void Brick::update()
{
    BrickSpr.setPosition(coords);
    if (this->state > 2) this->state = 0;
    if (state == 0) BrickTex.loadFromFile(".\\bin\\Debug\\nope.png");
    if (state == 1) BrickTex.loadFromFile(".\\bin\\Debug\\cross.png");
    if (state == 2) BrickTex.loadFromFile(".\\bin\\Debug\\circle.png");
}


