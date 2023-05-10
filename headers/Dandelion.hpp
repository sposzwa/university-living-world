#pragma once
#include "Plant.hpp"

class Dandelion : public Plant {
protected:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Plant>(*this);
    }

public:
    // Constructors & Destructor
    Dandelion();
    Dandelion(Position pos);
    Dandelion(Dandelion const& dandelion);
    ~Dandelion();

    // Overriden organism methods
    Organism* createOffspring(Position pos) override;
};
