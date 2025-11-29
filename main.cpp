#include <Windows.h>
#include <winuser.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

class cntrl
{
public:
    cntrl()
    {
        Audio = "audio.wav";
        command = "test";
    }

    /**
     * @brief Begins the main loop of the program.
     *
     */
    void loop()
    {

        while (1)
        {
            if (rand() % chance == 0)
            { // TODO: Make this generate a random effect.
                // PlaySound(Audio.c_str(), NULL, SND_SYNC | SND_FILENAME);
                Sleep(500);
                activation();
                // break;
            }
        }
    }

private:
    int chance = 1;
    string Audio;
    string command; // Replace with a vector for a series of commands.
    INPUT *inps = NULL;

    /**
     * @brief Enters the programs input.
     *
     */
    void activation()
    {
        int i = 0;
        // Why malloc?
        if (inps == NULL)
            inps = (INPUT *)malloc((sizeof(INPUT) + 0) * command.size() * 2);
        for (; i < command.size(); i++) // This is dumb, but so is this program...
        {
            inps[i * 2].type = INPUT_KEYBOARD;
            inps[i * 2].ki.wVk = VkKeyScanA(command.at(i));

            inps[i * 2 + 1].type = INPUT_KEYBOARD;
            inps[i * 2 + 1].ki.wVk = VkKeyScanA(command.at(i));
            inps[i * 2 + 1].ki.dwFlags = KEYEVENTF_KEYUP;
        }
        // Enter the command.
        inps[i * 2].type = INPUT_KEYBOARD;
        inps[i * 2].ki.wVk = VK_RETURN;
        inps[i * 2 + 1].type = INPUT_KEYBOARD;
        inps[i * 2 + 1].ki.wVk = VK_RETURN;
        inps[i * 2 + 1].ki.dwFlags = KEYEVENTF_KEYUP;

        int x = SendInput((command.size() + 1) * 2, (LPINPUT)inps, sizeof(INPUT));

        cout << x << endl;
    }
};

int main()
{
    cntrl *prog = new cntrl();

    prog->loop();

    return 0;
}