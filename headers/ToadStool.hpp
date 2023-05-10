#pragma once
#include "Plant.hpp"

class ToadStool : public Plant {
protected:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& boost::serialization::base_object<Plant>(*this);
    }
public:
    ToadStool();
    ToadStool(Position pos);
    ToadStool(ToadStool const& toadStool);
    ~ToadStool();
    void interact(Organism* initiator) override;
    Organism* createOffspring(Position pos) override;
};