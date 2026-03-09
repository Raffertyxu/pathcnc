#include <emscripten.h>

extern "C" {
    // 參數依序：切割總長度(cm), 材料類型, 加工方式, 實木工藝, 組裝, 烤漆, 封邊, 貼皮, 運送方式
    EMSCRIPTEN_KEEPALIVE
    float calculate(float cut_length_cm, int material_type, int machining_type, int craft_type, 
                    int post_assembly, int post_paint, int post_edge, int post_veneer, int shipping_type) {
        
        float total_price = 0.0f;

        // --- 1. 材料基本費 ---
        // 1: 木心板(阿郎師), 2: 實木紐松(熊肯作), 3: 沈木(熊肯作)
        if (material_type == 1) total_price += 600.0f;  
        else if (material_type == 2) total_price += 1500.0f; 
        else if (material_type == 3) total_price += 3000.0f; 

        // --- 2. 切割加工費 (以公分計價) ---
        // 1: 2D(切斷/切槽) 預設 5元/cm,  2: 2.5D(浮雕/文字) 預設 15元/cm
        float price_per_cm = (machining_type == 2) ? 15.0f : 5.0f;
        total_price += (cut_length_cm * price_per_cm);

        // --- 3. 加工工藝 (僅限實木材才計費) ---
        if (material_type == 2 || material_type == 3) {
            if (craft_type == 1) total_price += 800.0f;  // 指接榫
            else if (craft_type == 2) total_price += 1500.0f; // 鳩尾榫
        }

        // --- 4. 後處理 ---
        if (post_assembly == 1) total_price += 800.0f; // 組裝費
        if (post_paint == 1) total_price += 1200.0f;   // 烤漆費
        if (post_edge == 1) total_price += 300.0f;     // 封邊費
        if (post_veneer == 1) total_price += 600.0f;   // 貼皮費

        // --- 5. 運送 ---
        // 1: 配送(配合物流)
        if (shipping_type == 1) total_price += 1500.0f; // 基礎運費

        return total_price;
    }
}
