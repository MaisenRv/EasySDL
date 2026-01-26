#pragma once
#include "./interface/IDrawable.hpp"
#include "./interface/IInitializable.hpp"
#include "./interface/IWindow.hpp"

#include <vector>

namespace EasySDL{
    class Scene{
        private:
        std::vector<std::reference_wrapper<IDrawable>> _sceneObjects;

        public:
        Scene() = default;
        void addObject(IDrawable& sceneObjects){
            this->_sceneObjects.push_back(sceneObjects);
        }

        void drawScene(IWindow *w){
            for(auto &object: this->_sceneObjects){
                object.get().draw(w);
            }
        }

        void clearScene(){
            this->_sceneObjects.clear();
        }
    };
}