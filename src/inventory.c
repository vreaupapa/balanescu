#include "inventory.h"

SDL_Texture* inventoryTexture = NULL;
Inventory playerInventory= {0,10,0};
SDL_FRect inventoryRect;


SDL_Texture* wheat_texture=NULL;
SDL_Texture* crops_texture=NULL;
SDL_Texture* milk_texture=NULL;


SDL_Texture* wheat_text_texture = NULL;
SDL_Texture* crops_text_texture = NULL;
SDL_Texture* milk_text_texture = NULL;


SDL_FRect wheat_texture_rect={840, 70, 50, 50};
SDL_FRect crops_texture_rect={840, 10, 50, 50};
SDL_FRect milk_texture_rect={840, 130, 50, 50};


SDL_FRect wheat_text_rect;
SDL_FRect crops_text_rect;
SDL_FRect milk_text_rect;

void init_inventory_textures(SDL_Renderer* renderer) {
    wheat_texture = IMG_LoadTexture(renderer, "./assets/Items/wheat.png");
    crops_texture = IMG_LoadTexture(renderer, "./assets/Items/crops.png");
    milk_texture = IMG_LoadTexture(renderer, "./assets/Items/milk.png");

    if (!wheat_texture || !crops_texture || !milk_texture) {
        SDL_Log("Eroare la încarcarea imaginilor inventar: %s", SDL_GetError());
        return;
    }
}

void update_inventory_texture(SDL_Renderer* renderer, TTF_Font* font){
    //distrug texturile anterioare
    if (wheat_text_texture) SDL_DestroyTexture(wheat_text_texture);
    if (crops_text_texture) SDL_DestroyTexture(crops_text_texture);
    if (milk_text_texture) SDL_DestroyTexture(milk_text_texture);
    //le setam pe NULL
    
    wheat_text_texture = NULL;
    crops_text_texture = NULL;
    milk_text_texture = NULL;
    //culoarea textului
    SDL_Color textColor = {255, 255, 255};
    //textul pentru inventar
    char wheatText[16], cropsText[16], milkText[16];
    snprintf(wheatText, sizeof(wheatText), "%d", playerInventory.wheat);
    snprintf(cropsText, sizeof(cropsText), "%d", playerInventory.crops);
    snprintf(milkText, sizeof(milkText), "%d", playerInventory.milk);

    
    SDL_Surface* wheatSurface = TTF_RenderText_Solid(font, wheatText, strlen(wheatText), textColor);
    SDL_Surface* cropsSurface = TTF_RenderText_Solid(font, cropsText, strlen(cropsText), textColor);
    SDL_Surface* milkSurface  = TTF_RenderText_Solid(font, milkText, strlen(milkText),  textColor);

    
    wheat_text_texture = SDL_CreateTextureFromSurface(renderer, wheatSurface);
    crops_text_texture = SDL_CreateTextureFromSurface(renderer, cropsSurface);
    milk_text_texture  = SDL_CreateTextureFromSurface(renderer, milkSurface);



    
    // Poziționează textele lângă imagini
    wheat_text_rect.w = wheatSurface->w;
    wheat_text_rect.h = wheatSurface->h;
    wheat_text_rect.x = wheat_texture_rect.x - wheat_text_rect.w;
    wheat_text_rect.y = wheat_texture_rect.y + (wheat_texture_rect.h - wheatSurface->h) / 2;

    crops_text_rect.w = cropsSurface->w;
    crops_text_rect.h = cropsSurface->h;
    crops_text_rect.x = crops_texture_rect.x  - crops_text_rect.w;
    crops_text_rect.y = crops_texture_rect.y + (crops_texture_rect.h - cropsSurface->h) / 2;

    milk_text_rect.w = milkSurface->w;
    milk_text_rect.h = milkSurface->h;
    milk_text_rect.x = milk_texture_rect.x - milk_text_rect.w;
    milk_text_rect.y = milk_texture_rect.y + (milk_texture_rect.h - milkSurface->h) / 2;

    SDL_DestroySurface(wheatSurface);
    SDL_DestroySurface(cropsSurface);
    SDL_DestroySurface(milkSurface);

    // Setează poziția textului în colțul din dreapta sus
    // inventoryRect.x = 900 - textSurface->w - 20; // Margine de 20px
    // inventoryRect.y = 20; // Sus
    // inventoryRect.w = textSurface->w;
    // inventoryRect.h = textSurface->h;
    // wheat_texture_rect.x =  inventoryRect.x+50;
    // milk_texture_rect.x =  inventoryRect.x-25;
    // if(playerInventory.wheat<10)
    //     crops_texture_rect.x = inventoryRect.x + 90;
    // if(playerInventory.wheat>=10 && playerInventory.wheat<100)
    //     crops_texture_rect.x = inventoryRect.x + 117;
    // if(playerInventory.wheat>=100)
    //     crops_texture_rect.x = inventoryRect.x + 145;

    // SDL_DestroySurface(textSurface);
}

void render_inventory(SDL_Renderer*  renderer)
{
    if (wheat_texture && crops_texture && milk_texture) {
        SDL_RenderTexture(renderer, wheat_texture, NULL, &wheat_texture_rect);
        SDL_RenderTexture(renderer, crops_texture, NULL, &crops_texture_rect);
        SDL_RenderTexture(renderer, milk_texture, NULL, &milk_texture_rect);
    }
    if (wheat_text_texture && crops_text_texture && milk_text_texture) {
        SDL_RenderTexture(renderer, wheat_text_texture, NULL, &wheat_text_rect);
        SDL_RenderTexture(renderer, crops_text_texture, NULL, &crops_text_rect);
        SDL_RenderTexture(renderer, milk_text_texture, NULL, &milk_text_rect);
    }
}