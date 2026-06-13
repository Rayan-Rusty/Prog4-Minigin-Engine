#ifndef MINIGIN_GAMELAYERS_H
#define MINIGIN_GAMELAYERS_H
namespace DigDug
{

    enum class GameTag { None = 0, Player, Enemy, Tilemap, Pump , TilemapComponent, UI , Spawner };
    enum class Layer{  Background = 0, Foreground = 1 , UI = 3};
}
#endif //MINIGIN_GAMELAYERS_H