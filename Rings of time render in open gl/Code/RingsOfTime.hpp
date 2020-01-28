#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <vector>

class RingsOfTime : public tyga::ActorDelegate
{
public:

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    /*
     * Tutorial: These are the tyga actors necessary for the tutorial.
     *           You shouldn't need any further member variables until
     *           the more advanced tutorial activities.
     */

    std::shared_ptr<tyga::Actor> base_actor_;
    std::vector<std::shared_ptr<tyga::Actor>> stand_actors_;
    std::vector<std::shared_ptr<tyga::Actor>> outer_actors_;
    std::vector<std::shared_ptr<tyga::Actor>> middle_actors_;
    std::vector<std::shared_ptr<tyga::Actor>> inner_actors_;
};
