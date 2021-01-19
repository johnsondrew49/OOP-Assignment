#include "Menu.h"

bool Menu::mouseOnText2()
{
    return  verdict;
}
bool Menu::mouseOnText()
{
    return  verdict2;
}

int Menu::whichMenu()
{
    return mnum;
}

void Menu::predraw2()
{
    if (mouseOnText())
    {

        // Get char pressed (unicode character) on the queue
        int key = GetKeyPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MAX))
            {
                name[letterCount] = (char)key;
                letterCount++;
            }

            key = GetKeyPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (letterCount > 0)
                mnum = 0;

        }
    }

    if (mouseOnText()) framesCounter++;
    else framesCounter = 0;
}

void Menu::predraw()
{
    if (CheckCollisionPointRec(GetMousePosition(), newGame)) verdict = true;
    else verdict = false;
    if (verdict) framesCounter++;
    else framesCounter = 0;
}

void Menu::drawmenu()
{
    ClearBackground(BLACK);
    DrawText("SNAKE V1.0", 360, 50, 20, LIGHTGRAY);
    DrawTexture(texture, texture.width / 2, texture.height / 10, WHITE);
    if (mouseOnText2()) {
        DrawText(": NEW GAME", 430, 350, 20, RED);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            mnum = 2;
        }
    }
    else  DrawText(": NEW GAME", 430, 350, 20, WHITE);

    DrawText(": CONTINUE", 430, 370, 20, LIGHTGRAY);
    DrawText(": HIGH SCORES", 430, 390, 20, LIGHTGRAY);
    DrawText(": EXIT", 430, 410, 20, LIGHTGRAY);
}

void Menu::drawmenu2()
{
    ClearBackground(BLACK);
    DrawText("SNAKE V1.0", 360, 50, 20, LIGHTGRAY);
    DrawRectangleRec(entername, LIGHTGRAY);
    if (mouseOnText()) DrawRectangleLines(entername.x, entername.y, entername.width, entername.height, BLACK);
    else DrawRectangleLines(entername.x, entername.y, entername.width, entername.height, DARKGRAY);

    DrawText(name, entername.x + 5, entername.y + 8, 40, BLACK);

    if (mouseOnText())
    {
        if (letterCount < MAX)
        {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", entername.x + 8 + MeasureText(name, 40), entername.y + 12, 40, BLACK);
        }
        else DrawText("Max characters used... Try backspace", 260, 350, 20, GRAY);
    }

    DrawText("INPUT NAME AND PRESS ENTER", 260, 250, 20, LIGHTGRAY);
}

