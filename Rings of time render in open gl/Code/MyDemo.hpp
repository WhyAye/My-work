#pragma once

#include <tyga/ApplicationDelegate.hpp>
#include <tyga/GraphicsRendererProtocol.hpp>

class MyDemo : public tyga::ApplicationDelegate
{
private:

    virtual void
    applicationWindowWillInit(int& width,
                              int& height,
                              int& sample_count,
                              bool& windowed);

    virtual void
    applicationDidStart() override;

    virtual void
    applicationRunloopWillBegin() override;

    virtual void
    applicationRunloopDidEnd() override;

    virtual void
    applicationWillStop() override;

    virtual void
    applicationInputStateChanged(
        std::shared_ptr<tyga::InputStateProtocol> input_state) override;

private:

    std::shared_ptr<tyga::GraphicsRendererProtocol> renderer_;

};
