#include "inventory.h"
#include "player.h"

SDL_Texture* inventoryTexture = NULL;
Inventory playerInventory= {0,10,0, 100, 0, 0};
SDL_FRect inventoryRect;


SDL_Texture* wheat_texture=NULL;
SDL_Texture* crops_texture=NULL;
SDL_Texture* milk_texture=NULL;
SDL_Texture* coin_texture=NULL;
SDL_Texture* bucket_texture=NULL;


SDL_Texture* wheat_text_texture = NULL;
SDL_Texture* crops_text_texture = NULL;
SDL_Texture* milk_text_texture = NULL;
SDL_Texture* coin_text_texture = NULL;
SDL_Texture* bucket_text_texture = NULL;


SDL_FRect wheat_texture_rect={840, 70, 50, 50};
SDL_FRect crops_texture_rect={840, 10, 50, 50};
SDL_FRect milk_texture_rect={840, 130, 50, 50};
SDL_FRect coin_texture_rect={840, 190, 50, 50};
SDL_FRect bucket_texture_rect={840, 250, 50, 50};


SDL_FRect wheat_text_rect;
SDL_FRect crops_text_rect;
SDL_FRect milk_text_rect;
SDL_FRect coin_text_rect;
SDL_FRect bucket_text_rect;

void init_inventory_textures(SDL_Renderer* renderer) {
    wheat_texture = IMG_LoadTexture(renderer, "./assets/Items/wheat.png");
    crops_texture = IMG_LoadTexture(renderer, "./assets/Items/crops.png");
    milk_texture = IMG_LoadTexture(renderer, "./assets/Items/milk.png");
    coin_texture = IMG_LoadTexture(renderer, "./assets/Items/coin.png");
    bucket_texture = IMG_LoadTexture(renderer, "./assets/Items/bucket.png");

    if (!wheat_texture || !crops_texture || !milk_texture || !coin_texture || !bucket_texture) {
        SDL_Log("Eroare la încarcarea imaginilor inventar: %s", SDL_GetError());
        return;
    }
}

void update_inventory_texture(SDL_Renderer* renderer, TTF_Font* font){
    //distrug texturile anterioare
    if (wheat_text_texture) SDL_DestroyTexture(wheat_text_texture);
    if (crops_text_texture) SDL_DestroyTexture(crops_text_texture);
    if (milk_text_texture) SDL_DestroyTexture(milk_text_texture);
    if (coin_text_texture) SDL_DestroyTexture(coin_text_texture);
    if (bucket_text_texture) SDL_DestroyTexture(bucket_text_texture);
    //le setam pe NULL
    
    wheat_text_texture = NULL;
    crops_text_texture = NULL;
    milk_text_texture = NULL;
    coin_text_texture = NULL;
    bucket_text_texture = NULL;
    //culoarea textului
    SDL_Color textColor = {255, 255, 255};
    //textul pentru inventar
    char wheatText[16], cropsText[16], milkText[16], coinText[16], bucketText[16];
    snprintf(wheatText, sizeof(wheatText), "%d", playerInventory.wheat);
    snprintf(cropsText, sizeof(cropsText), "%d", playerInventory.crops);
    snprintf(milkText, sizeof(milkText), "%d", playerInventory.milk);
    snprintf(coinText, sizeof(milkText), "%d", playerInventory.coins);
    snprintf(bucketText, sizeof(milkText), "%d/%d", playerInventory.bucket, bucket_limit);

    
    SDL_Surface* wheatSurface = TTF_RenderText_Solid(font, wheatText, strlen(wheatText), textColor);
    SDL_Surface* cropsSurface = TTF_RenderText_Solid(font, cropsText, strlen(cropsText), textColor);
    SDL_Surface* milkSurface  = TTF_RenderText_Solid(font, milkText, strlen(milkText),  textColor);
    SDL_Surface* coinSurface  = TTF_RenderText_Solid(font, coinText, strlen(coinText),  textColor);
    SDL_Surface* bucketSurface  = TTF_RenderText_Solid(font, bucketText, strlen(bucketText),  textColor);

    
    wheat_text_texture = SDL_CreateTextureFromSurface(renderer, wheatSurface);
    crops_text_texture = SDL_CreateTextureFromSurface(renderer, cropsSurface);
    milk_text_texture  = SDL_CreateTextureFromSurface(renderer, milkSurface);
    coin_text_texture  = SDL_CreateTextureFromSurface(renderer, coinSurface);
    bucket_text_texture  = SDL_CreateTextureFromSurface(renderer, bucketSurface);



    
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

    coin_text_rect.w = coinSurface->w;
    coin_text_rect.h = coinSurface->h;
    coin_text_rect.x = coin_texture_rect.x - coin_text_rect.w;
    coin_text_rect.y = coin_texture_rect.y + (coin_texture_rect.h - coinSurface->h) / 2;

    bucket_text_rect.w = bucketSurface->w;
    bucket_text_rect.h = bucketSurface->h;
    bucket_text_rect.x = bucket_texture_rect.x - bucket_text_rect.w;
    bucket_text_rect.y = bucket_texture_rect.y + (bucket_texture_rect.h - bucketSurface->h) / 2;

    SDL_DestroySurface(wheatSurface);
    SDL_DestroySurface(cropsSurface);
    SDL_DestroySurface(milkSurface);
    SDL_DestroySurface(coinSurface);
    SDL_DestroySurface(bucketSurface);

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
    if (wheat_texture && crops_texture && milk_texture && coin_texture) {
        SDL_RenderTexture(renderer, coin_texture, NULL, &coin_texture_rect);
        SDL_RenderTexture(renderer, wheat_texture, NULL, &wheat_texture_rect);
        SDL_RenderTexture(renderer, crops_texture, NULL, &crops_texture_rect);
        SDL_RenderTexture(renderer, milk_texture, NULL, &milk_texture_rect);
        SDL_RenderTexture(renderer, bucket_texture, NULL, &bucket_texture_rect);
    }
    if (wheat_text_texture && crops_text_texture && milk_text_texture && coin_text_texture) {
        SDL_RenderTexture(renderer, coin_text_texture, NULL, &coin_text_rect);
        SDL_RenderTexture(renderer, wheat_text_texture, NULL, &wheat_text_rect);
        SDL_RenderTexture(renderer, crops_text_texture, NULL, &crops_text_rect);
        SDL_RenderTexture(renderer, milk_text_texture, NULL, &milk_text_rect);
        SDL_RenderTexture(renderer, bucket_text_texture, NULL, &bucket_text_rect);
    }
}