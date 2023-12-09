// // EndScreen.cpp
// #include "EndScreen.hpp"
// #include "util.hpp"

// EndScreen::EndScreen(SDL_Renderer* renderer) {
//     // Load the end screen image
//     endScreenTexture = loadTexture(renderer, "path/to/end_screen_image.png");

//     // Set the position and size of the end screen
//     endScreenRect = {0, 0, 1000, 600}; // Adjust the size as needed
// }

// EndScreen::~EndScreen() {
//     // Free the loaded texture
//     SDL_DestroyTexture(endScreenTexture);
// }

// void EndScreen::render() {
//     // Render the end screen
//     SDL_RenderCopy(renderer, endScreenTexture, nullptr, &endScreenRect);
// }
