#pragma once

class ISubject;
class IObserver{
    public:
        virtual ~IObserver() {};
        virtual void Update(ISubject* subject) = 0;
};