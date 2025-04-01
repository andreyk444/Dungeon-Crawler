#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <Dungeon/Dungeon.h>

#ifndef TRAMP_C___VIEW_H
#define TRAMP_C___VIEW_H


using namespace Tramp;
class ViewEnemies;
class DungeonView;


class ViewItem: public  sf::Drawable, public sf::Transformable{
public:
    void updateEquipment(std::shared_ptr<IItem> ptr) {
        auto regular = std::dynamic_pointer_cast<RegularEquipment>(ptr);


        if (regular) {
            if (!(regular ->isVisible())){
                m_sprite.setPosition(sf::Vector2f(-1000, -1000));

            }

            m_sprite.setPosition(sf::Vector2f(regular->getCoordinates().first * m_tileSize.x,
                                              ((regular->getCoordinates().second) + 0.3) * m_tileSize.y));
        }
    }

    void update(ViewItem viewItem){
        m_tileSize = viewItem.m_tileSize;
        m_sprite = viewItem.m_sprite;
        m_texture = viewItem.m_texture;
    }

    void updateEquipment() {
        m_sprite.setPosition(sf::Vector2f(-1,-1));

    }

    bool load(const std::string& tileset, sf::Vector2u tileSize, std::shared_ptr<IItem> ptr) {
        id_ = ptr ->getName();
        m_tileSize = tileSize;
        if (!m_texture.loadFromFile(tileset))
            return false;

        m_sprite.setTexture(m_texture);
        m_sprite.setScale(2, 2);

        auto regular = std::dynamic_pointer_cast<RegularEquipment>(ptr);

        if (regular) {
                 m_sprite.setPosition(sf::Vector2f(sf::Vector2f(regular->getCoordinates().first * m_tileSize.x,
                                          (regular->getCoordinates().second + 0.3) * m_tileSize.y))) ;
        }
        return true;
    }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(m_sprite, states);

    }

    std::string id_;
    sf::Vector2u m_tileSize;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    friend class ViewItems;
};

class ViewItems: public sf::Drawable, public sf::Transformable{

public:
    void updateItems(const std::vector<std::shared_ptr<IItem>> items){
        for (const auto & item : items) {
            size_t j = 0;
            while (items_[j].id_ != item->getName())
                ++j;

            if (item->isVisible()){
                items_[j].m_sprite.setPosition(sf::Vector2f((item->getCoordinates().first ) * m_tileSize.x,
                                                            (item->getCoordinates().second +0.15f) * m_tileSize.y));
            }
            else{
                items_[j].m_sprite.setPosition(sf::Vector2f(-100.f, -100.f));
            }
        }
    }

    void updateItems() {
        for (auto &item: items_){
            item.m_sprite.setPosition(sf::Vector2f(-100.f, -100.f));
        }
    }

    bool load(sf::Vector2u tileSize, const std::vector<ViewItem> items){
        m_tileSize = tileSize;

        items_= items;

        return true;
    }

    size_t getCountItems(){return items_.size();}

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        states.transform *= getTransform();


        for (const auto & item : items_)

            target.draw(item.m_sprite, states);

    }
    sf::Vector2u m_tileSize;
    std::vector<ViewItem> items_;

    friend class DungeonView;

};

class ViewCharacter: public sf::Drawable, public sf::Transformable{

public:
    void updateCharacter(Character &character){
        m_sprite.setPosition(sf::Vector2f(character.getCoordinates().first * m_tileSize.x, character.getCoordinates().second * m_tileSize.y));

        float healthPercentage = static_cast<float>(character.getHealth()) / static_cast<float>(character.getMaxHealth());
        health_.setSize(sf::Vector2f(200.f * healthPercentage, 40.f));


        float defencePercentage = static_cast<float>(character.getDefence());
        defence_.setSize(sf::Vector2f(10.f * defencePercentage, 40.f));

        //Equipment
        for (size_t i = 0; i < EQUIPMENT_TYPE_SIZE; ++i){
            auto ptr = character.getEquipment(static_cast<EquipmentType>(i));
            if (ptr){
                m_equipment[i].updateEquipment(ptr);
            }
            else{
                m_equipment[i].updateEquipment();

            }

        }

       // health_.setPosition(sf::Vector2f(character.getCoordinates().first * m_tileSize.x,( static_cast<float>(character.getCoordinates().second) - 0.5) * m_tileSize.y) );

    }

    bool load(const std::string& tileset,  sf::Vector2u tileSize,  Character& character)
    {
        m_tileSize = tileSize;
        if (!m_texture.loadFromFile(tileset))
            return false;

        if (!health_texture_.loadFromFile("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Character/heart.png"))
            return false;

        health_sprite_.setTexture(health_texture_);
        health_sprite_.setPosition(sf::Vector2f(m_tileSize.x * 0, m_tileSize.y * 7 ));
        health_sprite_.setScale(3, 3);

        if (!defence_texture_.loadFromFile("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Character/defence.png"))
            return false;

        defence_sprite.setTexture(defence_texture_);
        defence_sprite.setPosition(sf::Vector2f(m_tileSize.x * 0, m_tileSize.y * 8 ));
        defence_sprite.setScale(1, 1);

        health_.setFillColor(sf::Color::Green);
        health_.setSize(sf::Vector2f(200.f, 40.f));
        health_.setPosition(sf::Vector2f(m_tileSize.x * 0, m_tileSize.y * 7 ));



        defence_.setFillColor(sf::Color::Blue);
        defence_.setSize(sf::Vector2f(0.f, 40.f));
        defence_.setPosition(sf::Vector2f(m_tileSize.x * 0, m_tileSize.y * 8 ));
        

        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(sf::Vector2f(character.getCoordinates().first * tileSize.x, character.getCoordinates().second * tileSize.y));
        m_sprite.setScale(2,2);


        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();


        // draw the vertex array
        target.draw(m_sprite, states);
        target.draw(health_, states);
        target.draw(defence_, states);
        for (size_t i = 0; i < EQUIPMENT_TYPE_SIZE; ++i){
            target.draw(m_equipment[i], states);


        }
        target.draw(health_sprite_, states);
        target.draw(defence_sprite, states);

    }
    sf::RectangleShape health_;
    sf::RectangleShape defence_;

    sf::Sprite health_sprite_;
    sf::Texture health_texture_;

    sf::Sprite defence_sprite;
    sf::Texture defence_texture_;

    sf::Vector2u m_tileSize;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    std::array<ViewItem, EQUIPMENT_TYPE_SIZE> m_equipment;

    friend class ViewLevel;
};

class ViewEnemy: public sf::Drawable, public sf::Transformable{

public:
    void updateEnemy(Enemy &enemy){
        m_sprite.setPosition(sf::Vector2f(enemy.getCoordinates().first * m_tileSize.x, enemy.getCoordinates().second * m_tileSize.y));
    }

    bool load(const std::string& tileset, sf::Vector2u tileSize, Enemy& enemy)
    {
        id_ = enemy.getName();

        m_tileSize = tileSize;
        if (!m_texture.loadFromFile(tileset))
            return false;

        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(sf::Vector2f(enemy.getCoordinates().first * tileSize.x, enemy.getCoordinates().second * tileSize.y));
        m_sprite.setScale(2,2);//delete

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();


        // draw the vertex array
        target.draw(m_sprite, states);

    }
    std::string id_;
    sf::Vector2u m_tileSize;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    friend class ViewLevel;
    friend ViewEnemies;
};

class ViewEnemies: public sf::Drawable, public sf::Transformable{

public:
    void updateEnemies(std::vector<Enemy> &enemies){
        for (size_t i= 0;i < enemies.size(); i++) {
            if (enemies_[i].id_ != enemies[i].getName()) {
                enemies_.erase(enemies_.begin() + i);
            }

            enemies_[i].m_sprite.setPosition(sf::Vector2f(enemies[i].getCoordinates().first * m_tileSize.x,
                                                          enemies[i].getCoordinates().second * m_tileSize.y));
        }
        if (enemies_.size() > enemies.size())
            enemies_.erase(enemies_.begin() + enemies_.size() - 1);


    }

    bool load(sf::Vector2u tileSize, const std::vector<ViewEnemy> &enemies)
    {
        m_tileSize = tileSize;

        enemies_= enemies;

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        states.transform *= getTransform();


        for (const auto & enemie : enemies_)
            target.draw(enemie.m_sprite, states);

    }
    sf::Vector2u m_tileSize;
    std::vector<ViewEnemy> enemies_;
    friend class ViewLevel;
};

class ViewLevel : public sf::Drawable, public sf::Transformable
{
public:


    bool load(const std::string& tileset, sf::Vector2u tileSize, Level& level)
    {
        size_t height = level.getPlayingField().rows();
        size_t width = level.getPlayingField().columns();
        
        tileSize_ = tileSize;
        if (!m_tileset.loadFromFile(tileset))
            return false;


        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(width * height * 6);




        for (size_t i = 0; i < height; ++i)
            for (size_t j = 0; j < width; ++j)
            {
                int tileNumber = level.getPlayingField()[i][j].getCellType();

                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                sf::Vertex* triangles = &m_vertices[(j + i * width) * 6];

                triangles[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
                triangles[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
                triangles[2].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
                triangles[5].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);

                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);


            }

        return true;
    }
    
    void update(Level &level){
        size_t height = level.getPlayingField().rows();
        size_t width = level.getPlayingField().columns();

        for (size_t i = 0; i < height; ++i)
            for (size_t j = 0; j < width; ++j)
            {
                int tileNumber = level.getPlayingField()[i][j].getCellType();


                int tu = tileNumber % (m_tileset.getSize().x / tileSize_.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize_.x);


                sf::Vertex* triangles = &m_vertices[(j + i * width) * 6];

                triangles[0].position = sf::Vector2f(j * tileSize_.x, i * tileSize_.y);
                triangles[1].position = sf::Vector2f((j + 1) * tileSize_.x, i * tileSize_.y);
                triangles[2].position = sf::Vector2f(j * tileSize_.x, (i + 1) * tileSize_.y);
                triangles[3].position = sf::Vector2f(j * tileSize_.x, (i + 1) * tileSize_.y);
                triangles[4].position = sf::Vector2f((j + 1) * tileSize_.x, i * tileSize_.y);
                triangles[5].position = sf::Vector2f((j + 1) * tileSize_.x, (i + 1) * tileSize_.y);


                triangles[0].texCoords = sf::Vector2f(tu * tileSize_.x, tv * tileSize_.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize_.x, tv * tileSize_.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize_.x, (tv + 1) * tileSize_.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize_.x, (tv + 1) * tileSize_.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize_.x, tv * tileSize_.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize_.x, (tv + 1) * tileSize_.y);


            }
    }
    
    void updateCharacter(ViewCharacter& vc){
        m_character = vc;   
    }

    void updateEnemies(ViewEnemies& viewEnemies){
        m_enemies = viewEnemies;
    }
    void updateItems(ViewItems& items){
        m_items = items;

    }

    bool is_enemies;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
        target.draw(m_character, states);


        if (is_enemies) {
            target.draw(m_enemies, states);
        }

        target.draw(m_items, states);


    }
    sf::Vector2u tileSize_;

    ViewEnemies m_enemies;
    ViewItems m_items;

    ViewCharacter m_character;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;


};

class DungeonView{
private:
    std::vector<std::shared_ptr<ViewEnemies>>& mV_enemies;
    std::vector<std::vector<Enemy>>& mM_enemies;

    ViewItems& mV_items_;
    std::vector<std::shared_ptr<IItem>>& mM_items_;



    sf::Vector2u tileSize_;

public:
    DungeonView(std::vector<std::shared_ptr<ViewEnemies>>& enemies,
                std::vector<std::vector<Enemy>>& M_enemies,
                ViewItems& mV_items,
                std::vector<std::shared_ptr<IItem>>& mM_items,

                sf::Vector2u tileSize):
                mV_enemies{enemies},mM_enemies{M_enemies},mV_items_{mV_items},mM_items_(mM_items), tileSize_(tileSize)
                {}

    [[nodiscard]] std::vector<std::shared_ptr<ViewEnemies>>& getVEnemies() {return mV_enemies;}
    [[nodiscard]] std::vector<std::vector<Enemy>>& getMEnemies() {return mM_enemies;}
    [[nodiscard]] ViewItems& getVItems() {return mV_items_;}
    [[nodiscard]] std::vector<std::shared_ptr<IItem>>& getMItems() {return mM_items_;}



};

#endif //TRAMP_C___VIEW_H
