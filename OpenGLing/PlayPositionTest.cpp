#include "PlayPositionTest.h"

void PlayPositionTest::run(){

    m_net_thread = std::thread([this](){
        run_internal();
    });
}

void PlayPositionTest::setPlayer(const Player* _player) {
    m_player = _player;
}

struct Data {
    int x = 0;
    int y = 0;
    int z = 0;

    int r_x = 0;
    int r_y = 0;
    int r_z = 0;
};


void PlayPositionTest::run_internal(){

    Data d;
    sf::Clock clock;
    sf::Time time;
    //sf::Packet packet;

    is_running = true;

    // Init Sockets
    SOCKET sock;
    WSADATA wsa;
    struct sockaddr_in addr;
    int slen;


    slen = sizeof(addr) ;

    //Initialise winsock
    long rc = WSAStartup(MAKEWORD(2,2),&wsa);
    if (rc != 0)
    {
        std::cout << "Failed. Error Code : " << WSAGetLastError();
    }

    // Socket
    if((sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        std::cout << "Could not create socket : " << WSAGetLastError();
    }

    // Address
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");;
    addr.sin_port = htons( 1337 );

    while(is_running){

        if(m_player == nullptr){
            return;
        }

        // Get Position
        d.x = m_player->position.x;
        d.y = m_player->position.y;
        d.z = m_player->position.z;
        // Get Rotation
        d.r_x = m_player->rotation.x;
        d.r_y = m_player->rotation.y;
        d.r_z = m_player->rotation.z;

        // Preparing data
        // packet << d.x << d.y << d.z << d.r_x << d.r_y << d.r_z;
        std::array<int, 6> buffer = {d.x, d.y, d.z, d.r_x, d.r_y, d.r_z};

        std::cout << "Trying to send data\n";

        // Send data
        if (sendto(sock, (char*)buffer.data(), 6 * sizeof(int), 0, (struct sockaddr*) &addr, slen) == SOCKET_ERROR)
        {
            std::cout << "sendto() failed with error code : " << WSAGetLastError();
        }

        std::cout << "Data sent!\n";

        // FPS Limiting
        time = clock.restart();
        if(time.asMicroseconds() < tick_time){
            sf::sleep(sf::microseconds(tick_time - time.asMicroseconds()));
        }
    }
}
