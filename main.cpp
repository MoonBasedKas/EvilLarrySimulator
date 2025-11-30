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
        command = "/kill @s";
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
                PlaySound(Audio.c_str(), NULL, SND_SYNC | SND_FILENAME); // Ignore this error, it works anyways.

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
            z = queue_input(z, command.at(i));
        }
        z = queue_input(z, VK_RETURN);
        SendInput(command.size() * 2 + 2, inps, sizeof(INPUT));
    }

    /**
     * @brief Queues the next input of text.
     *
     * @param location where to queue the input.
     * @param text what input to queue
     * @return int how many inputs have been queued
     */
    int queue_input(int location, char text)
    {
        int additions = 0;
        inps[location].type = INPUT_KEYBOARD;
        inps[location].ki.wVk = VkKeyScanA(text);

        additions++;

        inps[location + additions].type = INPUT_KEYBOARD;
        inps[location + additions].ki.wVk = VkKeyScan(text);
        inps[location + additions].ki.dwFlags = KEYEVENTF_KEYUP;
        additions++;

        return additions;
    }

    /**
     * @brief Queues the next special input of text
     *
     * @param location where to queue the input.
     * @param action what input to queue but number
     * @return int how many inputs have been queued.
     */
    int queue_input(int location, int action)
    {
        int additions = 0;
        inps[location].type = INPUT_KEYBOARD;
        inps[location].ki.wVk = action;
        additions++;

        inps[location + additions].type = INPUT_KEYBOARD;
        inps[location + additions].ki.wVk = action;
        inps[location + additions].ki.dwFlags = KEYEVENTF_KEYUP;
        additions++;

        return additions;
    }
};

int main()
{
    cntrl *prog = new cntrl();

    prog->loop();

    return 0;
}