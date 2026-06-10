//
// Created by omen on 19/03/2026.
//

#ifndef MINIGIN_IOBSERVER_H
#define MINIGIN_IOBSERVER_H

namespace dae
{
    class GameActor;
    class IObserver
    {
    public:
        virtual ~IObserver() = default;

        enum class Event
        {
            ActorDied,
            ActorFell,
            ActorHit,
            PointsScored,
            ItemCollected,
            Collision,
            LevelCompleted,
            TileDestroyed,
            EnemyKilled

        };

        virtual void Notify(Event event, GameActor* actor) = 0;
        virtual void OnSubjectDestroy() {}
    private:
    };
}



#endif //MINIGIN_IOBSERVER_H