#pragma once
#include <vector>

// AI Generated 3D text model for login "SPA0202"
inline std::vector<float> generateLoginModel() {
    std::vector<float> data;

    // Helper function to draw a 2D rectangle (2 triangles) in 3D space
    auto addQuad = [&](float x, float y, float w, float h, float r, float g, float b) {
        float q[] = {
            x, y, 0.0f,       r, g, b,
            x + w, y, 0.0f,     r, g, b,
            x, y + h, 0.0f,     r, g, b,
            x, y + h, 0.0f,     r, g, b,
            x + w, y, 0.0f,     r, g, b,
            x + w, y + h, 0.0f,   r, g, b
        };
        data.insert(data.end(), q, q + 36);
        };

    // Letter S (Red)
    float x = -2.35f; float r = 1.0f, g = 0.0f, b = 0.0f;
    addQuad(x, 0.8f, 0.5f, 0.2f, r, g, b); // Top
    addQuad(x, 0.4f, 0.5f, 0.2f, r, g, b); // Mid
    addQuad(x, 0.0f, 0.5f, 0.2f, r, g, b); // Bot
    addQuad(x, 0.6f, 0.2f, 0.2f, r, g, b); // Top-Left
    addQuad(x + 0.3f, 0.2f, 0.2f, 0.2f, r, g, b); // Bot-Right

    // Letter P (Orange)
    x = -1.65f; r = 1.0f; g = 0.5f; b = 0.0f;
    addQuad(x, 0.0f, 0.2f, 1.0f, r, g, b); // Left
    addQuad(x + 0.2f, 0.8f, 0.3f, 0.2f, r, g, b); // Top
    addQuad(x + 0.2f, 0.4f, 0.3f, 0.2f, r, g, b); // Mid
    addQuad(x + 0.3f, 0.6f, 0.2f, 0.2f, r, g, b); // Right

    // Letter A (Yellow)
    x = -0.95f; r = 1.0f; g = 1.0f; b = 0.0f;
    addQuad(x, 0.0f, 0.2f, 1.0f, r, g, b); // Left
    addQuad(x + 0.3f, 0.0f, 0.2f, 1.0f, r, g, b); // Right
    addQuad(x + 0.2f, 0.8f, 0.1f, 0.2f, r, g, b); // Top
    addQuad(x + 0.2f, 0.4f, 0.1f, 0.2f, r, g, b); // Mid

    // Number 0 (Green)
    x = -0.25f; r = 0.0f; g = 1.0f; b = 0.0f;
    addQuad(x, 0.0f, 0.2f, 1.0f, r, g, b); // Left
    addQuad(x + 0.3f, 0.0f, 0.2f, 1.0f, r, g, b); // Right
    addQuad(x + 0.2f, 0.8f, 0.1f, 0.2f, r, g, b); // Top
    addQuad(x + 0.2f, 0.0f, 0.1f, 0.2f, r, g, b); // Bot

    // Number 2 (Cyan)
    x = 0.45f; r = 0.0f; g = 1.0f; b = 1.0f;
    addQuad(x, 0.8f, 0.5f, 0.2f, r, g, b); // Top
    addQuad(x, 0.4f, 0.5f, 0.2f, r, g, b); // Mid
    addQuad(x, 0.0f, 0.5f, 0.2f, r, g, b); // Bot
    addQuad(x + 0.3f, 0.6f, 0.2f, 0.2f, r, g, b); // Top-Right
    addQuad(x, 0.2f, 0.2f, 0.2f, r, g, b); // Bot-Left

    // Number 0 (Blue)
    x = 1.15f; r = 0.0f; g = 0.0f; b = 1.0f;
    addQuad(x, 0.0f, 0.2f, 1.0f, r, g, b); // Left
    addQuad(x + 0.3f, 0.0f, 0.2f, 1.0f, r, g, b); // Right
    addQuad(x + 0.2f, 0.8f, 0.1f, 0.2f, r, g, b); // Top
    addQuad(x + 0.2f, 0.0f, 0.1f, 0.2f, r, g, b); // Bot

    // Number 2 (Magenta)
    x = 1.85f; r = 1.0f; g = 0.0f; b = 1.0f;
    addQuad(x, 0.8f, 0.5f, 0.2f, r, g, b); // Top
    addQuad(x, 0.4f, 0.5f, 0.2f, r, g, b); // Mid
    addQuad(x, 0.0f, 0.5f, 0.2f, r, g, b); // Bot
    addQuad(x + 0.3f, 0.6f, 0.2f, 0.2f, r, g, b); // Top-Right
    addQuad(x, 0.2f, 0.2f, 0.2f, r, g, b); // Bot-Left

    return data;
}