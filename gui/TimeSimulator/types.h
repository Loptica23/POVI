#pragma once
#include <memory>
#include <vector>

namespace TimeSimulator
{
class Command;
using CommandPtr = std::shared_ptr<Command>;
using CommandVtr = std::vector<CommandPtr>;
using CommandVtrPtr = std::shared_ptr<CommandVtr>;

class Machine;
using MachinePtr = std::shared_ptr<Machine>;
using MachineVtr = std::vector<MachinePtr>;
using MachineVtrPtr = std::shared_ptr<MachineVtr>;

class CommandTerminationTimeEngine;
using CommandTerminationTimeEnginePtr = std::shared_ptr<CommandTerminationTimeEngine>;
using ResultVector = std::vector<std::pair<unsigned, unsigned>>;

class Task;
using TaskPtr = std::shared_ptr<Task>;
using TaskVtr = std::vector<TaskPtr>;
using TaskVtrPtr = std::shared_ptr<TaskVtr>;
}
