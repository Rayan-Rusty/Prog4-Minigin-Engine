#pragma once
#include <typeindex>

namespace dae
{
    class GameObject;
    class Component
    {
    public:
        explicit Component(GameObject* owner);
        virtual ~Component() = default;

        virtual void Update(float deltaTime);
        virtual void Render() const;

        //this is way I dont have to dynamic cast in GetComponent in GameObject
        //using type_index bc you cant compare two type_info
        GameObject* GetOwner() const { return m_owner; }

        virtual std::type_index GetType() const = 0;
        //TODO rule of five
    private:
        GameObject* m_owner{nullptr};
    };

}
