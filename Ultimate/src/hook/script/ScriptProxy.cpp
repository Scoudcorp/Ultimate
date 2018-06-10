#include "ScriptProxy.h"
#include "hook/DetourManager.h"
#include "ultimate/Ultimate.h"
#include <intrin.h>
#include <memory>

#pragma intrinsic(_ReturnAddress)

ScriptProxy::ScriptProxy()
    : m_initialized{ false }
    , m_index{ 1025 }
    , m_original{ nullptr }
{
}

ScriptProxy::~ScriptProxy()
{
    reset();
}

void ScriptProxy::initialize(const uint32_t index)
{
    m_index = index;

    if (!m_hooks.empty()) {
        m_initialized = true;

        m_original = Script::g_interalFunctions[index];

	    Script::g_interalFunctions[index] = interceptor;

        std::printf("ScriptProxy -> registered hook %d @ %p\n", m_index, m_original);
    }
}

void ScriptProxy::reset()
{
	if (m_index <= 1024) {
		Script::g_interalFunctions[m_index] = m_original;
	}

    m_initialized = false;
}

bool ScriptProxy::doesOriginalAddressMatch(const uint32_t address) const
{
    return address == getOriginalAddress();
}

uint32_t ScriptProxy::getOriginalAddress() const
{
    return reinterpret_cast<uint32_t>(m_original);
}

void ScriptProxy::runHooks(const scr_entref_t entref)
{
    if (!m_initialized) {
        std::printf("ScriptProxy -> attempted to run %d while not intialized!\n", m_index);
        return;
    }

    auto shouldReturn = true;

    for (auto& hook : m_hooks) {
        shouldReturn &= hook(entref);
    }

    if (shouldReturn) {
        m_original(entref);
    }
}

void ScriptProxy::installHook(const uint32_t index)
{
    initialize(index);
}

void ScriptProxy::registerHook(const ScriptInternalFunction hook)
{
    m_hooks.push_back(hook);
}

void __declspec(naked) ScriptProxy::interceptor(scr_entref_t entref)
{
    uint32_t eaxIndex;
    uint32_t ediIndex;
    uint32_t finalIndex;
    uint32_t returnAddress;

    __asm {
		push ebp
		mov ebp, esp
		sub esp, __LOCAL_SIZE

		mov eaxIndex, eax
		mov ediIndex, edi
    }

    returnAddress = reinterpret_cast<uint32_t>(_ReturnAddress());

    if (returnAddress == 0x582894) {
        finalIndex = eaxIndex;
    } else if (returnAddress == 0x582B8A) {
        finalIndex = ediIndex;
    } else {
        finalIndex = 1025;
    }

    if (finalIndex >= 1025) {
        std::printf("ScriptProxy -> FATAL: could not decide register for returnAddress %p\n", _ReturnAddress());
    }

    g_detours.m_scriptManager.runHooks(finalIndex, entref);

    __asm {
		mov esp, ebp
		pop ebp
		ret
    }
}
