#ifndef PLAYPOSITIONTEST_H
#define PLAYPOSITIONTEST_H

#include <iostream>
#include <thread>

#include<winsock2.h>
#include <windows.h>

// #include <SFML/Network.hpp>
#include "../Player/Player.h"

class PlayPositionTest {
public:

    void run();
    void setPlayer(const Player* _player);

    bool is_running = false;
private:
    void run_internal();

    std::thread m_net_thread;

    const Player* m_player;
    const static long ticks_per_scond = 2;
    constexpr const static long tick_time = ((float)1 / (float)ticks_per_scond) * 1000000;
};

#endif // PLAYPOSITIONTEST_H
