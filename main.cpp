#include <emscripten.h>

extern "C" {
    // 這是一個簡單的 CNC 倍率計算測試
    EMSCRIPTEN_KEEPALIVE
    float calculate(float input) {
        // 假設你的邏輯是將長度乘以 1.55 倍
        return input * 1.55f; 
    }
}
