#pragma once

#include "properties.h"
#include <queue>
#include <memory>

namespace esphome {
namespace danfoss_eco {

using namespace std;

enum class CommandType {
    READ,
    WRITE
};

struct Command {
    Command(CommandType t, shared_ptr<DeviceProperty> const &p) : type(t), property(p) {}

    CommandType type; // 0 - read, 1 - write
    shared_ptr<DeviceProperty> property;

    bool execute(esphome::ble_client::BLEClient *client) {
        if (this->type == CommandType::WRITE) {
            WritableProperty *wp = static_cast<WritableProperty *>(this->property.get());
            return wp->write_request(client);
        } else
            return this->property->read_request(client);
    }
};

class CommandQueue {
 public:
    void push(const Command &cmd) {
        queue_.push(cmd);
    }

    Command pop() {
        if (queue_.empty()) return Command(CommandType::READ, nullptr); // tyhjä komento
        Command cmd = queue_.front();
        queue_.pop();
        return cmd;
    }

    bool empty() const {
        return queue_.empty();
    }

    size_t size() const {
        return queue_.size();
    }

 private:
    std::queue<Command> queue_;
};

}  // namespace danfoss_eco
}  // namespace esphome
