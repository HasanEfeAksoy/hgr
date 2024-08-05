#ifndef _HGR_H_
#define _HGR_H_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _CMATH_
#include <cmath>
#endif

#ifndef _WINDOWS_
#include <windows.h>
#endif



#define PI 3.14159265


namespace hgr {
    // Global değişkenler
    HINSTANCE hInst;
    HWND hwnd;

    HDC memDC;
    HBITMAP memBitmap;
    
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));


    // ~60 FPS ile çalışır. değiştirmek isterseniz SetTimer fonksiyonunda millisecond değerini değiştirebilirsiniz. (FPS = 1000/millisecond)
    
    // kullanılabilir
    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    bool mouseLeft = false;
    bool mouseRight = false;
    bool keyPressed = false;
    int keyCode = 0;
    // kullanılabilir


    void (*userUpdateFunc)() = nullptr;
    




    //
    // hgr some definitions start



    struct vec2 {
        float x, y;

        vec2() : x(0), y(0) {}
        vec2(const vec2& other) : x(other.x), y(other.y) {}
        vec2(float n) : x(n), y(n) {}
        vec2(float x, float y) : x(x), y(y) {}

        
        vec2& operator=(const vec2& other) {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
            }
            return *this;
        }

        vec2 operator+(const vec2& other) const {
            return vec2(this->x + other.x, this->y + other.y);
        }

        vec2 operator-(const vec2& other) const {
            return vec2(this->x - other.x, this->y - other.y);
        }

        vec2 operator*(float scalar) const {
            return vec2(this->x * scalar, this->y * scalar);
        }

        vec2 operator/(float scalar) const {
            return vec2(this->x / scalar, this->y / scalar);
        }

        vec2& operator+=(const vec2& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        vec2& operator-=(const vec2& other) {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        vec2& operator*=(float scalar) {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        vec2& operator/=(float scalar) {
            this->x /= scalar;
            this->y /= scalar;
            return *this;
        }

        float length() const {
            return std::sqrt(this->x * this->x + this->y * this->y);
        }

        vec2 normalize() const {
            float len = this->length();
            return len > 0 ? vec2(this->x / len, this->y / len) : vec2();
        }

        float dot(const vec2& other) const {
            return this->x * other.x + this->y * other.y;
        }
    };

    struct vec3 {
        float x, y, z;

        vec3() : x(0), y(0), z(0) {}
        vec3(const vec3& other) : x(other.x), y(other.y), z(other.z) {}
        vec3(float n) : x(n), y(n), z(n) {}
        vec3(float x, float y, float z) : x(x), y(y), z(z) {}


        vec2 xy() const {
            return vec2(this->x, this->y);
        }

        vec2 xz() const {
            return vec2(this->x, this->z);
        }

        vec2 yz() const {
            return vec2(this->y, this->z);
        }


        vec3& operator=(const vec3& other) {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
            }
            return *this;
        }
        
        vec3 operator+(const vec3 &other) const {
            return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        vec3 operator-(const vec3 &other) const {
            return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
        }

        vec3 operator*(float scalar) const {
            return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
        }

        vec3 operator/(float scalar) const {
            return vec3(this->x / scalar, this->y / scalar, this->z / scalar);
        }

        vec3& operator+=(const vec3& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        vec3& operator-=(const vec3& other) {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        vec3& operator*=(float scalar) {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        vec3& operator/=(float scalar) {
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            return *this;
        }

        float length() const {
            return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        vec3 normalize() const {
            float len = this->length();
            return len > 0 ? vec3(this->x / len, this->y / len, this->z / len) : vec3();
        }

        float dot(const vec3& other) const {
            return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
        }

        vec3 cross(const vec3& other) const {
            return vec3(
                this->y * other.z - this->z * other.y,
                this->z * other.x - this->x * other.z,
                this->x * other.y - this->y * other.x
            );
        }
    };


    float mapRange(float value, float a, float b, float c, float d) {
        value = (value - a) / (b - a);
        return c + value * (d - c);
    }

    // hgr some defibitions end
    //




    void clearWindow();
    void drawWindow(const vec2& size, const char* title, const vec3& color, void (*updateFunc)());
    void drawPixel(const vec2& position, const vec3& color);




    // Pencere prosedürü
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
            case WM_DESTROY:
                if (memBitmap) {
                    DeleteObject(memBitmap);
                }
                if (memDC) {
                    DeleteDC(memDC);
                }
                PostQuitMessage(0);
                return 0;
            // case WM_LBUTTONDOWN: {
            //     // Tıklanan pikselin rengini kontrol et
            //     int x = LOWORD(lParam);
            //     int y = HIWORD(lParam);

            //     HDC hdc = GetDC(hwnd);
            //     COLORREF color = GetPixel(hdc, x, y);
            //     ReleaseDC(hwnd, hdc);

            //     // Renk bilgisini konsola yazdır
            //     printf("Koordinatlar: (%d, %d) - Renk: #%02X%02X%02X\n", x, y,
            //         GetRValue(color), GetGValue(color), GetBValue(color));
            //     return 0;
            // }
            case WM_LBUTTONDOWN: {
                mouseLeft = true; // Sol tıklama
                return 0;
            }
            case WM_LBUTTONUP: {
                mouseLeft = false; // Sol tıklama bırakıldı
                return 0;
            }
            case WM_RBUTTONDOWN: {
                mouseRight = true; // Sağ tıklama
                return 0;
            }
            case WM_RBUTTONUP: {
                mouseRight = false; // Sağ tıklama bırakıldı
                return 0;
            }
            case WM_MOUSEMOVE: {
                // Fare pozisyonunu al
                mouseX = LOWORD(lParam);
                mouseY = HIWORD(lParam);
                return 0;
            }
            case WM_KEYDOWN: {
                keyPressed = true; // Tuş basılı
                keyCode = wParam; // Son basılan tuşun kodunu sakla

                // EĞER BÖYLE BİR KOMBİNASYON İSTERSENİZ BURAYA KENDİNİZ EKLEYİNİZ
                // if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && keyPressed == 'A') {
                //     printf("CTRL + A tuş kombinasyonu basıldı.\n");
                // }

                return 0;
            }
            case WM_KEYUP: {
                keyPressed = false; // Tuş bırakıldı
                keyCode = 0; // Değeri null yap

                return 0;
            }
            case WM_SIZE: {
                // Pencere boyutu değiştiğinde bellek DC'yi yeniden oluştur
                WIDTH = LOWORD(lParam);
                HEIGHT = HIWORD(lParam);
                
                if (memDC) {
                    DeleteObject(memBitmap);
                    DeleteDC(memDC);
                }

                memDC = CreateCompatibleDC(NULL);
                memBitmap = CreateCompatibleBitmap(GetDC(hwnd), WIDTH, HEIGHT);
                SelectObject(memDC, memBitmap);
                clearWindow();
                return 0;
            }
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                
                // Bellek DC'den pencereye resmi kopyala
                BitBlt(hdc, 0, 0, WIDTH, HEIGHT, memDC, 0, 0, SRCCOPY);

                EndPaint(hwnd, &ps);
                return 0;
            }
            case WM_TIMER: {
                if (userUpdateFunc) {
                    clearWindow();
                    userUpdateFunc();
                    InvalidateRect(hwnd, NULL, FALSE); // ÖNEMLİ! : tamamen silip tekrar çizmek için true, eskileri barındırıp güncellemek için false. kullanıcının yapacağı işe bağlı.
                }
                return 0;
            }

        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    





    // hgr

    void drawWindow(const vec2& size, const char* title, const vec3& color, void (*updateFunc)()) {

        userUpdateFunc  = updateFunc;
        
        DeleteObject(brush);
        brush = CreateSolidBrush(RGB(color.x, color.y, color.z));
        
        memDC = CreateCompatibleDC(NULL);
        memBitmap = CreateCompatibleBitmap(GetDC(hwnd), size.x, size.y);
        SelectObject(memDC, memBitmap);

        hInst = GetModuleHandle(NULL); // Uygulama örneğini al

        // Pencere sınıfı adı (ANSI)
        const char* CLASS_NAME = "MyWindow";

        // Pencere sınıfını tanımla
        WNDCLASSA wc = {};
        wc.lpfnWndProc = WindowProc; // Pencere prosedürü
        wc.hInstance = hInst;         // Uygulama örneği
        wc.lpszClassName = CLASS_NAME; // Sınıf adı
        wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Fare imleci
        wc.hbrBackground = brush; /*(HBRUSH)(COLOR_WINDOW + 1);*/       // Arka plan rengi
        wc.style = CS_HREDRAW | CS_VREDRAW; // Yeniden çizim stili

        RegisterClassA(&wc); // Pencere sınıfını kaydet (ANSI)


        // Pencere oluştur
        hwnd = CreateWindowExA( // ANSI versiyonu
            0,
            CLASS_NAME,
            title, // Pencere başlığı (ANSI)
            // WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y,
            NULL,
            NULL,
            hInst,
            NULL
        );

        ShowWindow(hwnd, SW_SHOWDEFAULT);

        WIDTH = size.x;
        HEIGHT = size.y;

        // Bellek DC oluştur
        memDC = CreateCompatibleDC(NULL);
        memBitmap = CreateCompatibleBitmap(GetDC(hwnd), size.x, size.y);
        SelectObject(memDC, memBitmap);
        clearWindow();

        
        // ~60 FPS
        SetTimer(hwnd, 1, 16, NULL);

        // Mesaj döngüsü
        MSG msg = {};
        
        while (GetMessageW(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        KillTimer(hwnd, 1);
        if (memBitmap) {
            DeleteObject(memBitmap);
        }
        if (memDC) {
            DeleteDC(memDC);
        }
    }

    void drawPixel(const vec2& position, const vec3& color) {
        SetPixel(memDC, position.x, position.y, RGB(color.x, color.y, color.z));
    }

    void clearWindow() {
        RECT rect = {0, 0, WIDTH, HEIGHT};
        // FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        FillRect(memDC, &rect, brush);
    }


};




#endif