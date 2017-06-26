#pragma once
#include <memory>
#include <vector>
#include <queue>

namespace TimeSimulator
{
class Command;
using CommandPtr = std::shared_ptr<Command>;
using CommandVtr = std::vector<CommandPtr>;
using CommandQueue = std::queue<CommandPtr>;
using CommandVtrPtr = std::shared_ptr<CommandVtr>;
using ComandQueuePtr = std::shared_ptr<CommandQueue>;

class Machine;
using MachinePtr = std::shared_ptr<Machine>;
using MachineVtr = std::vector<MachinePtr>;
using MachineVtrPtr = std::shared_ptr<MachineVtr>;

class CommandManager;
using CommandManagerPtr = std::shared_ptr<CommandManager>;

class MachineManager;
using MachineManagerPtr = std::shared_ptr<MachineManager>;

class TimeEngine;
using TimeEnginePtr = std::shared_ptr<TimeEngine>;


class CommandTerminationTimeEngine;
using CommandTerminationTimeEnginePtr = std::shared_ptr<CommandTerminationTimeEngine>;
using ResultVector = std::vector<std::pair<unsigned, unsigned>>;

class Task;
using TaskPtr = std::shared_ptr<Task>;
using TaskVtr = std::vector<TaskPtr>;
using TaskVtrPtr = std::shared_ptr<TaskVtr>;

enum class TaskState {New, Waiting, InProgress, Complited, Leaved, Stopped};

}
