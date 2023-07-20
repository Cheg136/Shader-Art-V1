#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"WindowClass";
    const wchar_t WINDOW_TITLE[] = L"Window";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    
    HWND hwnd = CreateWindowEx(NULL, CLASS_NAME, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,      
    CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
    NULL, NULL, NULL, NULL         
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) 
    {
    case WM_PAINT: 
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        int width = clientRect.right - clientRect.left;
        int height = clientRect.bottom - clientRect.top;

        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width / 2; x++) {
                int red = (x + y) % 256;
                int green = (x * y) % 256;
                int blue = (x ^ y) % 256;

                SetPixel(hdc, x, y, RGB(red, green, blue));
                SetPixel(hdc, width - x - 1, y, RGB(red, green, blue));
            }
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY: 
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
