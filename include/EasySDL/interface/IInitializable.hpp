#pragma once

namespace EasySDL{
    class IInitializable{
        public:
            virtual ~IInitializable() = default;

            virtual void setup() final {
                if(this->_restriction()) return;
                this->_onSetup();
            }

        protected:
            IInitializable() = default;

            virtual void _onSetup(){}
            virtual bool _restriction(){return false;}
    };
}