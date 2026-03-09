#include <emscripten.h>

extern "C" {
    // 保持名稱為 calculate，這樣你不用改 GitHub Actions 腳本
    // 這次我們傳入三個參數：數量(quantity)、單件材料費(material_cost)、單件預估工時(process_hours)
    EMSCRIPTEN_KEEPALIVE
    float calculate(float quantity, float material_cost, float process_hours) {
        
        // --- 廠內預設參數 ---
        float hourly_rate = 850.0f; // 假設每小時加工機台費率 850 元
        float setup_fee = 1500.0f;  // 基本開機/校模準備費 1500 元
        
        // 1. 單件加工費 = 工時 * 費率
        float unit_labor_cost = process_hours * hourly_rate;
        
        // 2. 單件總成本 = 材料費 + 加工費
        float unit_cost = material_cost + unit_labor_cost;
        
        // 3. 判斷開機費：如果數量達到 50 件以上，吸收開機費 (免收)
        if (quantity >= 50.0f) {
            setup_fee = 0.0f;
        }
        
        // 計算初步總價
        float total_quote = (unit_cost * quantity) + setup_fee;
        
        // 4. 階梯式大宗折扣邏輯
        if (quantity >= 500.0f) {
            total_quote *= 0.90f; // 500件以上打 9 折
        } else if (quantity >= 100.0f) {
            total_quote *= 0.95f; // 100件以上打 95 折
        }
        
        return total_quote;
    }
}
