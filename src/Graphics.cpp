#include "GamesEngineeringBase.h" 
#include "Graphics.h"
#include <algorithm>

void Graphics::DrawBox(GamesEngineeringBase::Window& window, int x, int y, int w, int h) {
    int W = window.getWidth();      
    int H = window.getHeight();

    auto put = [&](int px, int py) {
        if (px < 0 || py < 0 || px >= W || py >= H) return;
        window.draw(px, py, 255, 0, 144);                      
        };

    for (int i = 0; i < w; ++i) { 
        put(x + i, y); 
        put(x + i, y + h - 1); 
    }
    for (int j = 0; j < h; ++j) { 
        put(x, y + j); 
        put(x + w - 1, y + j); 
    }

}

void Graphics::DrawSubImg(GamesEngineeringBase::Window& window, GamesEngineeringBase::Image& image, int srcX, int srcY, int w, int h, int desX, int desY) {

    const int W = window.getWidth(), H = window.getHeight();

    
    // the tile is out of screen
    if (desX >= W || desY >= H || desX + w <= 0 || desY + h <= 0 ) return;

    // traverse pixels in screen
    const int iStart = std::max(0, -desX), iEnd = std::min(w, W - desX);
    const int jStart = std::max(0, -desY), jEnd = std::min(h, H - desY);

    for (int j = jStart; j < jEnd; j++) {
        int atlasY = srcY + j; //height
        for (int i= iStart; i < iEnd; i++) {
            int atlasX;
            atlasX = srcX + i; //width, start at top-left corner.

            unsigned char alpha = image.alphaAtUnchecked(atlasX, atlasY);
            if (alpha == 0) continue;  
            unsigned char* pixel = image.atUnchecked(atlasX, atlasY); 

            window.draw(desX + i, desY + j, pixel);
        }
    }
}

