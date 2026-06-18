#pragma once

#include <vector>

#include <EasySDL/interface/IDrawable.hpp>
#include <EasySDL/interface/IInitializable.hpp>
#include <EasySDL/interface/IWindow.hpp>
#include <EasySDL/render/Renderer2D.hpp>

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

            void render(render::Renderer2D& renderer,IWindow *w){
                for(auto &object: this->_sceneObjects){
                    object.get().render(renderer,w);
                }
            }

            void clearScene(){ this->_sceneObjects.clear(); }
    };
}