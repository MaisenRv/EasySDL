#pragma once
#include "./interface/IDrawable.hpp"
#include "./interface/IInitializable.hpp"
#include "./interface/IWindow.hpp"
#include "./render/Renderer2D.hpp"

#include <vector>

namespace EasySDL{
    class Scene{
        private:
            std::vector<std::reference_wrapper<IDrawable>> _sceneObjects;

        public:
            Scene() = default;
            void addObject(IDrawable& sceneObject){
                this->_sceneObjects.push_back(sceneObject);
                if (auto init = dynamic_cast<IInitializable*>(&sceneObject)) {
                    init->setup();
                }
            }

            void render(Renderer2D& renderer,IWindow *w){
                for(auto &object: this->_sceneObjects){
                    object.get().render(renderer,w);
                }
            }

            void clearScene(){
                this->_sceneObjects.clear();
            }
    };
}