// NOTE: This sample is not stable.
#include <windows.h>
#include <windowsx.h>
#include <vfw.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "vfw32.lib")

HWND camhwnd;
CAPSTATUS status;

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    camhwnd = capCreateCaptureWindow("camera window", WS_CHILD | WS_VISIBLE, 0, 0, 320, 200, hwnd, 999);
    capDriverConnect(camhwnd, 0);
    capDlgVideoFormat(camhwnd);
    capDlgVideoSource(camhwnd);
    capDlgVideoCompression(camhwnd);
    capPreviewScale(camhwnd, TRUE);
    capPreviewRate(camhwnd, 66);
    capPreview(camhwnd, TRUE);

    WAVEFORMATEX wfx;
    ZeroMemory(&wfx, sizeof(wfx));
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.cbSize = 0;

    wfx.nChannels = 1;
    wfx.nSamplesPerSec = 11025;
    wfx.wBitsPerSample = 8;

    wfx.nBlockAlign = wfx.wBitsPerSample * wfx.nChannels / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    BOOL b = capSetAudioFormat(camhwnd, &wfx, sizeof(wfx));
    printf("%d\n", b);

    capGetStatus(camhwnd, &status, sizeof(status));
    printf("%d, %d\n", status.uiImageWidth, status.uiImageHeight);
    return TRUE;
}

TCHAR sz[MAX_PATH];
INT i = 0;

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    case psh1:
        wsprintf(sz, "Movie-%u.avi", i);
        capFileSetCaptureFile(camhwnd, sz);
        capCaptureSequence(camhwnd);
        break;
    case psh2:
        wsprintf(sz, "Movie-%u.avi", i);
        capFileSaveAs(camhwnd, sz);
        ++i;
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(100), NULL, DialogProc);
    return 0;
}
