#include "VirtualMachine.h"
#include "imgui/imgui.h"

namespace Vm {
uint32_t VirtualMachine::firstFreeThread()
{
    for (auto i = 0u; i < m_threads.size(); ++i) {
        const auto thread = &m_threads[i];

        if (thread->m_free) {
            return i;
        }
    }

    std::printf("No free threads remaining\n");
    std::abort();
}

bool VirtualMachine::isTriggerDefined(const uint32_t trigger) const
{
    for (auto i = 0u; i < m_numTriggers; ++i) {
        if (m_triggers[i] == trigger) {
            return true;
        }
    }

    return false;
}

void VirtualMachine::spawnThread(Instruction* entry)
{
    const auto threadId = firstFreeThread();
    const auto newThread = &m_threads[threadId];
    newThread->m_free = false;
    newThread->m_index = threadId;
    newThread->m_stopTrigger = 0;
    newThread->m_waitTrigger = 0;
    newThread->m_waitFrames = 0;
    newThread->m_context.m_currentInstruction = entry;
    newThread->m_context.m_stackBaseIndex = 0;
    newThread->m_context.m_stack.m_topIndex = -1;

    std::printf("Starting thread %d\n", newThread->m_index);
}

void VirtualMachine::notify(const uint32_t trigger)
{
    m_queuedTriggers[m_freeQueuedTriggerSlot] = trigger;
    ++m_freeQueuedTriggerSlot;
}

void VirtualMachine::frame()
{
    static unsigned char binary[]{ 0x07,0x06,0x00,0x00,0x00,0x00,0x0E,0x0E,0x0E,0x11,0x00,0x00,0x00,0x00,0x23,0x00,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x00,0x11,0x0A,0x00,0x00,0x00,0x19,0x23,0x01,0x00,0x00,0x00,0x24,0x01,0x00,0x00,0x00,0x22,0x23,0x02,0x00,0x00,0x00,0x24,0x02,0x00,0x00,0x00,0x03,0x0A,0x00,0x00,0x00,0x02,0x20,0x00,0x00,0x00,0x09,0x0A,0x00,0x00,0x00,0x0F,0x24,0x00,0x00,0x00,0x00,0x07,0x14,0x00,0x00,0x00,0x0D,0x23,0x00,0x00,0x00,0x00,0x02,0xC0,0xFF,0xFF,0xFF,0x0D,0x0D,0x0D,0x01,0x0E,0x0E,0x0E,0x24,0xFD,0xFF,0xFF,0xFF,0x11,0x01,0x00,0x00,0x00,0x15,0x23,0xFC,0xFF,0xFF,0xFF,0x02,0x05,0x00,0x00,0x00,0x0D,0x0D,0x0D,0x01,0x00};
 
    if (!m_initialized) {
        spawnThread(reinterpret_cast<Instruction*>(binary));

        m_initialized = true;
    }

    // Copy queued triggers for threads to use
    for (auto i = 0u; i < m_freeQueuedTriggerSlot; ++i) {
        m_triggers[i] = m_queuedTriggers[i];
    }
    m_numTriggers = m_freeQueuedTriggerSlot;
    m_freeQueuedTriggerSlot = 0;

    for (auto& thread : m_threads) {
        if (thread.m_free) {
            continue;
        }

        if (thread.m_stopTrigger != INVALID_TRIGGER) {
            if (isTriggerDefined(thread.m_stopTrigger)) {
                thread.m_free = true;
                std::printf("Stopping thread %d\n", thread.m_index);
                continue;
            }
        }

        if (thread.m_waitTrigger != INVALID_TRIGGER) {
            if (!isTriggerDefined(thread.m_waitTrigger)) {
                continue;
            }
        }

        if (thread.m_waitFrames > 1) {
            --thread.m_waitFrames;
            continue;
        }

        run(thread);
    }
}

void VirtualMachine::run(Thread& thread)
{
    while (true) {
        if (m_interupted) {
            return;
        }

        //m_interupted = true;

        const auto instruction = *thread.m_context.m_currentInstruction;
        thread.m_context.m_currentInstruction += 1;

        std::printf("%d -> %3hhu\n", thread.m_index, instruction);

        switch (instruction) {
        case Instruction::Abort: {
            thread.m_free = true;
            std::printf("Stopping thread %d\n", thread.m_index);
            return;
        }

        case Instruction::Return: {
            const auto stackIndex = thread.m_context.m_stack.pop();
            const auto returnTo = thread.m_context.m_stack.pop();

            thread.m_context.m_currentInstruction = reinterpret_cast<Instruction*>(returnTo.m_value.m_unsignedInteger);
            thread.m_context.m_stackBaseIndex = stackIndex.m_value.m_unsignedInteger;
            break;
        }

        case Instruction::Jump: {
            const auto offset = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += offset - 1;
            break;
        }

        case Instruction::JumpZero: {
            const auto offset = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);

            const auto value = thread.m_context.m_stack.pop();
            if (!value.m_value.m_boolean) {
                thread.m_context.m_currentInstruction += offset - 1;
            } else {
                thread.m_context.m_currentInstruction += 4;
            }
            break;
        }

        case Instruction::JumpNotZero: {
            const auto offset = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);

            const auto value = thread.m_context.m_stack.pop();
            if (value.m_value.m_boolean) {
                thread.m_context.m_currentInstruction += offset - 1;
            } else {
                thread.m_context.m_currentInstruction += 4;
            }
            break;
        }

        case Instruction::PushPosition: {
            break;
        }

        case Instruction::PushStackIndex: {
            break;
        }

        case Instruction::Call: {
            const auto offset = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);

            auto position = Value{};
            position.m_type = Type::Integer;
            position.m_value.m_unsignedInteger = reinterpret_cast<uint32_t>(thread.m_context.m_currentInstruction + 4);
            thread.m_context.m_stack.push(position);

            auto stackIndex = Value{};
            stackIndex.m_type = Type::Integer;
            stackIndex.m_value.m_unsignedInteger = thread.m_context.m_stackBaseIndex;
            thread.m_context.m_stack.push(stackIndex);

            thread.m_context.m_currentInstruction += offset - 1;
            thread.m_context.m_stackBaseIndex = thread.m_context.m_stack.m_topIndex + 1;
            break;
        }

        case Instruction::Stop: {
            const auto stringReference = *reinterpret_cast<uint32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            thread.m_stopTrigger = stringReference;
            break;
        }

        case Instruction::Wait: {
            const auto duration = *reinterpret_cast<uint32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            thread.m_waitFrames = duration;
            return;
        }

        case Instruction::WaitUntil: {
            const auto stringReference = *reinterpret_cast<uint32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            thread.m_waitTrigger = stringReference;
            return;
        }

        case Instruction::Notify: {
            const auto stringReference = *reinterpret_cast<uint32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            notify(stringReference);
            break;
        }

        case Instruction::Thread: {
            spawnThread(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 10;
            break;
        }

        case Instruction::Pop: {
            thread.m_context.m_stack.pop();
            break;
        }

        case Instruction::ConstantNull: {
            auto value = Value{};
            value.m_type = Type::Null;
            thread.m_context.m_stack.push(value);
            break;
        }

        case Instruction::ConstantVoid: {
            auto value = Value{};
            value.m_type = Type::Void;
            thread.m_context.m_stack.push(value);
            break;
        }

        case Instruction::ConstantBoolean: {
            const auto booleanValue = *reinterpret_cast<uint8_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 1;

            auto value = Value{};
            value.m_type = Type::Boolean;
            value.m_value.m_boolean = booleanValue;
            thread.m_context.m_stack.push(value);
            break;
        }

        case Instruction::ConstantInteger: {
            const auto integerValue = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            auto value = Value{};
            value.m_type = Type::Integer;
            value.m_value.m_integer = integerValue;
            thread.m_context.m_stack.push(value);
            break;
        }

        case Instruction::ConstantFloat: {
            const auto floatValue = *reinterpret_cast<float*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            auto value = Value{};
            value.m_type = Type::Float;
            value.m_value.m_float = floatValue;
            thread.m_context.m_stack.push(value);
            break;
        }

        case Instruction::ConstantString: {
            const auto stringValue = *reinterpret_cast<uint32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            auto value = Value{};
            value.m_type = Type::String;
            value.m_value.m_stringReference = stringValue;
            thread.m_context.m_stack.push(value);
            break;
        }

        case Instruction::Test: {
            std::printf("Thread %d -> hello\n", thread.m_index);
            break;
        }

        case Instruction::Add: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.add(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Subtract: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.subtract(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Multiply: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.multiply(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Divide: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.divide(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Less: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.less(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::LessEqual: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.lessEqual(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Greater: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.greater(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::GreaterEqual: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.greaterEqual(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Equal: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.equal(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::NotEqual: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.notEqual(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::And: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.and_(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Or: {
            const auto second = thread.m_context.m_stack.pop();
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.or_(second);
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Negate: {
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.negate();
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Not: {
            const auto first = thread.m_context.m_stack.pop();
            const auto result = first.not_();
            thread.m_context.m_stack.push(result);
            break;
        }

        case Instruction::Set: {
            const auto stackOffset = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            const auto value = thread.m_context.m_stack.pop();
            thread.m_context.m_stack.set(value, thread.m_context.m_stackBaseIndex + stackOffset);
            break;
        }

        case Instruction::Get: {
            const auto stackOffset = *reinterpret_cast<int32_t*>(thread.m_context.m_currentInstruction);
            thread.m_context.m_currentInstruction += 4;

            const auto value = thread.m_context.m_stack.get(thread.m_context.m_stackBaseIndex + stackOffset);
            thread.m_context.m_stack.push(value);
            break;
        }

        default:
            std::printf("Unknown instruction %hhu\n", instruction);
            std::abort();
        }
    }
}

void VirtualMachine::draw()
{
    ImGui::Begin("Virtual Machine", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("Step")) {
        m_interupted = false;
    }

    for (auto& thread : m_threads) {
        if (thread.m_free) {
            continue;
        }

        thread.draw();

        ImGui::Separator();
    }

    ImGui::End();
}
}
