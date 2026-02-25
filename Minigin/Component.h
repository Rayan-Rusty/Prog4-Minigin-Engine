#pragma once
#include <typeindex>

namespace dae
{
    class GameObject;
    class Component
    {
    public:

        virtual ~Component() = default;

        virtual void Update(float deltaTime);
        virtual void Render() const;

        //this is way I dont have to dynamic cast in GetComponent in GameObject
        //using type_index bc you cant compare two type_info
        GameObject* GetOwner() const { return m_owner; }

        virtual std::type_index GetType() const = 0;
        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;
    protected:
        explicit Component(GameObject* owner);
    private:
        GameObject* m_owner{nullptr};
    };

}
