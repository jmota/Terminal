/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/
#pragma once

#include "..\inc\VtIoModes.hpp"
#include "..\renderer\vt\vtrenderer.hpp"
#include "VtInputThread.hpp"
#include "PtySignalInputThread.hpp"

class ConsoleArguments;

namespace Microsoft::Console::VirtualTerminal
{
    class VtIo
    {
    public:
        VtIo();

        HRESULT Initialize(_In_ const ConsoleArguments* const pArgs);

        bool IsUsingVt() const;

        HRESULT StartIfNeeded();

        static HRESULT ParseIoMode(_In_ const std::wstring& VtMode, _Out_ VtIoMode& ioMode);

        HRESULT SuppressResizeRepaint();
        HRESULT SetCursorPosition(_In_ const COORD coordCursor);

    private:
        bool _usingVt;
        bool _hasSignalThread;
        VtIoMode _IoMode;
        bool _lookingForCursorPosition;

        HRESULT _Initialize(_In_ const HANDLE InHandle, _In_ const HANDLE OutHandle, _In_ const std::wstring& VtMode);
        HRESULT _Initialize(_In_ const HANDLE InHandle, _In_ const HANDLE OutHandle, _In_ const std::wstring& VtMode, _In_opt_ HANDLE SignalHandle);
        HRESULT _Initialize(_In_ const std::wstring& InPipeName, _In_ const std::wstring& OutPipeName, _In_ const std::wstring& VtMode);
        HRESULT _Initialize(_In_ const std::wstring& InPipeName, _In_ const std::wstring& OutPipeName, _In_ const std::wstring& VtMode, _In_opt_ HANDLE SignalHandle);

        std::unique_ptr<Microsoft::Console::Render::VtEngine> _pVtRenderEngine;
        std::unique_ptr<Microsoft::Console::VtInputThread> _pVtInputThread;
        std::unique_ptr<Microsoft::Console::PtySignalInputThread> _pPtySignalInputThread;

    #ifdef UNIT_TESTING
        friend class VtIoTests;
    #endif
    };
}
