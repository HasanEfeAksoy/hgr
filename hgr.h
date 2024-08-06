#ifndef _HGR_H_
#define _HGR_H_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _CMATH_
#include <cmath>
#endif

#ifndef _ARRAY_
#include <array>
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
    


    void drawWindow(int width, int height, const char* title, int r, int g, int b, void (*updateFunc)());
    void clearWindow();
    void drawPixel(int x, int y, int r, int g, int b);
    void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
    void drawRect(int x, int y, int width, int height, int r, int g, int b);
    void drawCircle(int x, int y, int radius, bool fill, int r, int g, int b);
    void drawPolygon(int points[][2], int pointCount, int r, int g, int b);
    
    
    
    
    //
    // hgr some definitions start

    
    float mapRange(float value, float a, float b, float c, float d) {
        value = (value - a) / (b - a);
        return c + value * (d - c);
    }

    float distance(float x1, float y1, float x2, float y2) {
        return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    }
    // need null seed
    float randFloat(float min, float max) {
        float scale = rand() / (float) RAND_MAX;
        return min + scale * (max - min);
    }


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
        vec3(const vec2& other, float z) : x(other.x), y(other.y), z(z) {}
        vec3(float x, const vec2& other) : x(x), y(other.x), z(other.y) {}
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


    // hgr some defibitions end
    //






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

    void drawWindow(int width, int height, const char* title, int r, int g, int b, void (*updateFunc)()) {

        userUpdateFunc  = updateFunc;
        
        DeleteObject(brush);
        brush = CreateSolidBrush(RGB(r, g, b));
        
        memDC = CreateCompatibleDC(NULL);
        memBitmap = CreateCompatibleBitmap(GetDC(hwnd), width, height);
        SelectObject(memDC, memBitmap);

        hInst = GetModuleHandle(NULL); // Uygulama örneğini al

        // Pencere sınıfı adı (ANSI)
        const char* CLASS_NAME = "MyWindowClassName";

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
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            NULL,
            NULL,
            hInst,
            NULL
        );

        ShowWindow(hwnd, SW_SHOWDEFAULT);

        WIDTH = width;
        HEIGHT = height;

        // Bellek DC oluştur
        memDC = CreateCompatibleDC(NULL);
        memBitmap = CreateCompatibleBitmap(GetDC(hwnd), width, height);
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

    void clearWindow() {
        RECT rect = {0, 0, WIDTH, HEIGHT};
        // FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        FillRect(memDC, &rect, brush);
    }

    void drawPixel(int x, int y, int r, int g, int b) {
        SetPixel(memDC, x, y, RGB(r, g, b));
    }

    void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b) {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            drawPixel(x1, y1, r, g, b);
            if (x1 == x2 && y1 == y2) break;
            int err2 = err * 2;
            if (err2 > -dy) { 
                err -= dy;
                x1 += sx;
            }
            if (err2 < dx) { 
                err += dx;
                y1 += sy;
            }
        }
    }

    void drawRect(int x, int y, int width, int height, bool fill, int r, int g, int b) {
        if (fill) {
            for (int i = 0; i <= width; i++) {
                for (int j = 0; j <= height; j++) {
                    drawPixel(i + x, j + y, r, g, b);
                }
            }
        }
        else {
            drawLine(x, y, x + width, y, r, g, b);
            drawLine(x + width, y, x + width, y + height, r, g, b);
            drawLine(x + width, y + height, x, y + height, r, g, b);
            drawLine(x, y + height, x, y, r, g, b);
        }
    }

    void drawCircle(int x, int y, int radius, bool fill, int r, int g, int b) {
        int currentX = radius;
        int currentY = 0;
        int decisionOver2 = 1 - currentX;

        while (currentX >= currentY) {
            drawPixel(x + currentX, y + currentY, r, g, b);
            drawPixel(x + currentY, y + currentX, r, g, b);
            drawPixel(x - currentX, y + currentY, r, g, b);
            drawPixel(x - currentY, y + currentX, r, g, b);
            drawPixel(x + currentX, y - currentY, r, g, b);
            drawPixel(x + currentY, y - currentX, r, g, b);
            drawPixel(x - currentX, y - currentY, r, g, b);
            drawPixel(x - currentY, y - currentX, r, g, b);

            currentY++;

            if (decisionOver2 <= 0) {
                decisionOver2 += 2 * currentY + 1;
            } else {
                currentX--;
                decisionOver2 += 2 * (currentY - currentX) + 1;
            }
        }

        if (fill) {
            for (int yFill = 0; yFill <= radius; yFill++) {
                int xFill = static_cast<int>(sqrt(radius * radius - yFill * yFill));
                drawLine(x - xFill, y + yFill, x + xFill, y + yFill, r, g, b);
                drawLine(x - xFill, y - yFill, x + xFill, y - yFill, r, g, b);
            }
        }
    }

    void drawPolygon(int points[][2], int pointCount, int r, int g, int b) {
        if (pointCount < 2) return;

        for (int i = 0; i < pointCount; ++i) {
            drawLine(points[i][0], points[i][1], points[(i + 1) % pointCount][0], points[(i + 1) % pointCount][1], r, g, b);
        }
    }
};




#endif