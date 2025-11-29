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
        command = "/kill @e";
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
                Sleep(2000);
                PlaySound(Audio.c_str(), NULL, SND_SYNC | SND_FILENAME);

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
        int z = 0;
        if (inps == NULL)
        {
            inps = (INPUT *)malloc((sizeof(INPUT) + 1) * command.size() * 2);
            memset(inps, 0x0, ((sizeof(INPUT) + 1) * command.size() * 2));
        }

        // It seems we have to enter each input seperately.
        for (i = 0; i < command.size(); i++)
        {
            z = i * 2;
            inps[z].type = INPUT_KEYBOARD;
            inps[z].ki.wVk = VkKeyScanA(command.at(i));

            inps[z + 1].type = INPUT_KEYBOARD;
            inps[z + 1].ki.wVk = VkKeyScanA(command.at(i));
            inps[z + 1].ki.dwFlags = KEYEVENTF_KEYUP;
        }
        z = i * 2;
        inps[z].type = INPUT_KEYBOARD;
        inps[z].ki.wVk = VK_RETURN;
        inps[z + 1].type = INPUT_KEYBOARD;
        inps[z + 1].ki.wVk = VK_RETURN;
        inps[z + 1].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(command.size() * 2 + 2, inps, sizeof(INPUT));
    }
};

int main()
{
    cntrl *prog = new cntrl();

    prog->loop();

    return 0;
}